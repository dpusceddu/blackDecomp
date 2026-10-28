#!/usr/bin/env python3
"""Compile or assemble one Ninja input with its pinned local toolchain and write its depfile."""
import argparse
import json
import os
from pathlib import Path
import platform
import re
import shutil
import subprocess
import sys
import tempfile

sys.path[:0] = [str(Path(__file__).resolve().parents[1]), str(Path(__file__).resolve().parent)]
import assembler
import toolchain
from elfobj import normalize_object, restore_gprel, fit_included_sections, split_text_sections, undefine_dropped, trim_sections, unplaced_allocated_sections
from elfinfo import Elf
from splits import load_symbols
from units import dependencies


class CompilationFailure(SystemExit):
    """Keep the exit code and a useful per-unit fallback diagnostic together."""
    def __init__(self, code, reason):
        super().__init__(code)
        self.reason = reason

    def __str__(self):
        return self.reason


def environment():
    if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'AMD64'):
        raise SystemExit('The toolchain requires Linux x86-64; see README.md.')
    toolchain.require()
    base = toolchain.root()
    assembler.TOOLCHAINS = str(base)
    env = dict(os.environ, **toolchain.job_environment())
    env['PATH'] = env['BLACK_PATH_PREFIX'] + os.pathsep + env.get('PATH', '')
    return base, env


def compile_file(compiler, flags, source, output):
    base, env = environment()
    root = base / 'compilers' / compiler
    with tempfile.TemporaryDirectory(prefix='black-cc-') as temporary:
        env['TMPDIR'] = temporary
        env['WINEDEBUG'] = '-all'
        if (root / 'bin/ee-gcc.exe').is_file():
            backend = next(p for p in sorted((root / 'lib/gcc-lib/ee').iterdir()) if p.is_dir() and not p.name.startswith('.'))
            backend = assembler.short_path(backend)
            env['WIBO_PATH'] = backend
            prefix = [str(base / 'bin/wibo'), str(root / 'bin/ee-gcc.exe'), '-B' + backend + '/']
        else:
            prefix = [str(root / 'bin/ee-gcc'), '-B' + str(root / 'bin/ee-')]
        p = assembler.compile_with_assembler(prefix, flags, source, output, env, 300)
        if p.returncode or os.environ.get('BLACK_VERBOSE'):
            sys.stdout.write(p.stdout)
            sys.stderr.write(p.stderr)
        if p.returncode:
            raise CompilationFailure(p.returncode, '\n'.join((p.stderr or p.stdout).strip().splitlines()[-6:])
                                     or 'compiler/assembler exited %d' % p.returncode)
    path = Path(output)
    if path.suffix == '.o':
        path.write_bytes(restore_gprel(normalize_object(path.read_bytes())))


def generated_function_aliases(functions, defined):
    """Bind explicit address names for SN's randomly suffixed I/D wrappers.

    A unit must request _GLOBAL_$I$ADDRESS or _GLOBAL_$D$ADDRESS for its own
    function. Select exactly one defined function of that compiler role; ordinary
    symbols and units without this opt-in retain exact-name resolution.
    """
    aliases = {}
    for function in functions:
        for name in function.get('candidates', [function['symbol']]):
            match = re.fullmatch(r'_GLOBAL_\$([ID])\$([0-9A-F]{8})', name)
            if not match:
                continue
            if int(match[2], 16) != function['addr']:
                raise ValueError('generated wrapper address disagrees with %s' % name)
            if name in defined:
                continue
            prefix = '_GLOBAL_$%s$' % match[1]
            matches = [symbol['name'] for symbol in defined.values()
                       if symbol['type'] == 2 and symbol['name'].startswith(prefix)]
            if len(matches) != 1:
                raise ValueError('%s: expected one compiler-generated %s wrapper, found %d' %
                                 (name, match[1], len(matches)))
            aliases[name] = matches[0]
    return aliases


def finish_object(spec, output):
    """Normalize symbol visibility and discard only inputs without an original slot."""
    path = Path(output)
    raw = fit_included_sections(split_text_sections(path.read_bytes(), spec), spec)
    elf = Elf(raw)
    symbols = elf.symbols()
    defined = {s['name']: s for s in symbols if 0 < s['shndx'] < len(elf.sections)}
    resolved, keep, renames, externs = {}, set(), {}, {}
    unit = spec['unit']
    generated = generated_function_aliases(unit['functions'], defined)
    defined.update({name: defined[actual] for name, actual in generated.items()})
    for f in unit['functions']:
        name = next((n for n in f.get('candidates', [f['symbol']]) + ['func_%08X' % f['addr']] if n in defined), None)
        if name is None:
            raise SystemExit('%s: func_%08X: no definition in object' % (spec['src'], f['addr']))
        sym = defined[name]
        sec = elf.sections[sym['shndx']]['name']
        keep.add(sec)
        link_name = name if name.startswith('func_') else '%s$%X' % (name, f['addr'])
        actual_name = generated.get(name, name)
        if actual_name != link_name:
            renames[actual_name] = link_name
        resolved[str(f['addr'])] = dict(symbol=name, link_name=link_name, section=sec, size=sym['size'],
                                         value=sym['value'], status='asm' if '__nonmatching_func_%08X' % f['addr'] in defined else 'source')
    # Included assembly owns explicitly named constant sections. The compiler's
    # ordinary constant section replaces the already audited source-owned slots.
    keep.update(s['name'] for s in elf.sections if s['name'].startswith(('.rodata.', '.lit4.', '.gcc_except_table.')))
    slots_by_section = {sec: [(a,b) for a,b,addr in slots if resolved.get(str(addr), {}).get('status') == 'source']
                        for sec, slots in spec.get('slots', {}).items()}
    slots_by_section = {sec: slots for sec, slots in slots_by_section.items() if slots}
    keep.update(slots_by_section)
    keep.update(r['input'] for r in unit.get('data_ranges', []))
    trimmed = {}
    for sec, slots in slots_by_section.items():
        record = elf.section(sec)
        if record and slots:
            span = max(b for _, b in slots) - min(a for a, _ in slots)
            if record['size'] > span and not any(elf.content(record)[span:]):
                trimmed[sec] = span
    edited, _ = undefine_dropped(raw, keep)
    if trimmed:
        edited = trim_sections(edited, trimmed)
    path.write_bytes(edited)
    bindings = load_symbols()
    # Only globals used by a kept relocation need an original binding.
    used = set()
    import struct
    binding_elf = Elf(edited)
    symbols = binding_elf.symbols()
    for s in binding_elf.sections:
        if s['type'] == 9 and binding_elf.sections[s['info']]['name'] in keep:
            data = binding_elf.content(s)
            used.update(struct.unpack_from('<I', data, i+4)[0] >> 8 for i in range(0, len(data), 8))
    unknown = []
    known_image = set()
    validate_nm = '-DNON_MATCHING' in spec['flags'] and 'NON_MATCHING' in Path(spec['src']).read_text()
    if validate_nm:
        import re
        shared=Path(output).parents[2]
        if shared.name.endswith('-nm'):
            shared=shared.with_name(shared.name[:-3])
        # Use the split image, never a previous matching build or its caches.
        known_image={n for _,n in json.loads((shared/'labels.json').read_text())}
        known_image.update(f['name'] for f in json.loads((shared/'placement.json').read_text())['functions'])
        known_image.update(re.findall(r'^([^\s=]+)\s*=',(shared/'symbols.ld').read_text(),re.M))
        aliases=Path(output).parents[2]/'asm_aliases.ld'
        known_image.update(re.findall(r'^([^\s=]+)\s*=',aliases.read_text(),re.M))
        known_image.update(('_gp','__end_bss'))
    for i in used:
        s = symbols[i]
        if s['bind'] not in (1, 2) or s['name'] in renames:
            continue
        if s['shndx'] and (s['shndx'] >= len(elf.sections) or elf.sections[s['shndx']]['name'] in keep):
            continue
        addr = bindings.address(s['name'], unit.get('externs'))
        if s['name'].startswith('context_func_'):
            addr = int(s['name'].removeprefix('context_func_'), 16)
        if addr is not None and not s['name'].startswith(('func_', 'D_', 'jtbl_', 'ehtbl_', 'STR_', '.L')):
            externs[s['name']] = addr
            renames[s['name']] = '%s$%X' % (s['name'], addr)
        elif validate_nm and s['name'] not in known_image:
            unknown.append(s['name'])
    if unknown:
        raise ValueError('unbound draft symbols: '+', '.join(sorted(set(unknown))[:12]))
    base, env = environment()
    args = [env['BLACK_BINUTILS_PREFIX']+'objcopy']
    args += ['--redefine-sym=%s=%s' % p for p in renames.items()]
    args += ['--rename-section=%s=%s' % p for p in unplaced_allocated_sections(raw, keep).items()]
    if len(args) > 1:
        subprocess.run(args + [str(path)], env=env, check=True)
    import re
    contexts=[s['name'] for s in symbols if s['shndx']==0 and s['name'] not in renames
              and re.fullmatch(r'context_func_[0-9A-F]{8}',s['name'])]
    from graph_io import write_text
    write_text(str(path)+'.json',json.dumps(dict(resolved=resolved, externs=externs, context_undefined=contexts)))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('spec', help='generated object specification')
    ap.add_argument('output')
    a = ap.parse_args()
    spec = json.loads(Path(a.spec).read_text())
    output = Path(a.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    before=output.read_bytes() if output.exists() else None
    timestamps=output.stat() if before is not None else None
    deps = [a.spec, spec['src']]
    if spec['kind'] == 'cc':
        deps += [p.as_posix() for p in dependencies(spec['src'])]
        deps += spec.get('includes', [])
        try:
            compile_file(spec['compiler'], spec['flags'] + ['-I', 'include'], spec['src'], str(output))
            finish_object(spec, output)
        except (SystemExit, ValueError, subprocess.CalledProcessError) as error:
            output.unlink(missing_ok=True)
            if '-DNON_MATCHING' not in spec['flags']:
                raise
            print('NON_MATCHING fallback %s: draft cannot compile (%s)' % (spec['src'],error))
            flags=[f for f in spec['flags'] if f!='-DNON_MATCHING']
            compile_file(spec['compiler'], flags + ['-I', 'include'], spec['src'], str(output))
            finish_object(dict(spec,flags=flags), output)
            state_path=Path(str(output)+'.json')
            state=json.loads(state_path.read_text())
            state['draft_fallback']='draft cannot compile: '+str(error)
            state_path.write_text(json.dumps(state))
    else:
        base, env = environment()
        src = spec['src']
        text = Path(src).read_text()
        # Old EE GAS lacks .incbin. Expand ignored blob inputs into words.
        if '.incbin' in text:
            import struct
            lines = []
            for line in text.splitlines():
                if line.startswith('.incbin'):
                    blob = line.split('"')[1]
                    deps.append(blob)
                    data = Path(blob).read_bytes()
                    lines += ['.byte ' + ','.join(str(x) for x in data[i:i+32]) for i in range(0, len(data), 32)]
                else:
                    lines.append(line)
            scratch = tempfile.TemporaryDirectory(prefix='black-data-as-')
            src = str(Path(scratch.name)/'input.s')
            Path(src).write_text('\n'.join(lines) + '\n')
        p = subprocess.run([str(base / 'compilers/ee-gcc2.96/ee/bin/as'), '-I', 'include', '-o', str(output), src], env=env)
        if '.incbin' in text:
            scratch.cleanup()
        if p.returncode:
            raise SystemExit(p.returncode)
    if before is not None and output.read_bytes()==before:
        os.utime(output,ns=(timestamps.st_atime_ns,timestamps.st_mtime_ns))
    (Path(str(output) + '.d')).write_text('%s: %s\n' % (output, ' '.join(dict.fromkeys(deps))))


if __name__ == '__main__':
    main()
