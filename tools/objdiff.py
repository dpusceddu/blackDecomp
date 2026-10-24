#!/usr/bin/env python3
"""Per-unit objects and the project file for objdiff, and the progress report that decomp.dev reads.

Usage: objdiff.py [GAME_ID] [--report]       (GAME_ID defaults to SLUS_213.76; source units apply to that version only)
       objdiff.py --build PATH               rebuild the base object PATH of one unit (what the objdiff GUI calls after an edit)
Needs a finished `ninja` build (the compiled unit objects are cached under build/<GAME_ID>/cache/).
`--build` is the build command written to objdiff.json: it recompiles the changed sources through the build backend (the
same incremental compile stage as `ninja`, without the link), then rebuilds the object of that one unit.

The image is built as one program, but objdiff compares objects, so this tool derives one pair of objects per source unit:
  target  the original machine code of the unit's functions (their split assembly, assembled again), symbols func_XXXXXXXX
  base    the object compiled from the unit's source, its function symbols and references renamed to the same func_/D_ names
Both go to build/<GAME_ID>/objdiff/{target,base}/<unit>.o and are listed in objdiff.json (project root, not committed) with
one progress category per library. A function belongs to the unit that compiles it; every other function (INCLUDE_ASM, or
in a split that compiles nothing) gets a target-only unit per translation unit, so the report covers the whole program and
unrecovered code is unmatched. `--report` then runs objdiff-cli (see `tools/toolchain.py install --objdiff`) and writes
build/<GAME_ID>/report.json. The objects are normalized (sizes without padding, names, ABI flags, data symbols; see
docs/progress-reports.md) so that every function that is exact in the image is 100 % here.

objdiff compares instructions and relocations: a function could match here and still not be byte-exact in the image (data
placement). The build's `OK` and `ninja progress` remain the authority for exactness.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, io, json, re, subprocess, sys, tarfile
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
from units import load_units

ROOT = Path(__file__).resolve().parents[1]
DEFAULT = 'SLUS_213.76'
OPTIONS = {'demangler': 'gnu_legacy'}      # the SN compiler mangles like GCC 2.x


INSTRUCTION = re.compile(r'^\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/', re.M)


SECTION = re.compile(r'^\s*\.section\s+(\S+)', re.M)


def code_size(asm_text, addr, span):
    """Bytes of the function's code: from its start to its last `endlabel` in the text section, without the alignment
    padding that follows (the compiler's own symbol size does not include the padding either). A function with switch
    cases has several labelled fragments, hence the last one. `span` (up to the next function) is the fallback."""
    text = asm_text
    for m in SECTION.finditer(asm_text):
        if not m.group(1).strip(',"').startswith('.text'):
            text = asm_text[:m.start()]
            break
    end = text.rfind('\nendlabel')
    if end < 0:
        return span
    last = [int(m.group(1), 16) for m in INSTRUCTION.finditer(text[:end])]
    return min(span, last[-1] + 4 - addr) if last else span


ABSOLUTE = re.compile(r'^(D_[0-9A-Fa-f]+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', re.M)
NAME = re.compile(r'\bD_[0-9A-Fa-f]+\b')


def numeric_names(text, constants):
    """The assembly with the numeric names (`%lo(D_10F00)`) replaced by their values: the original code holds the number,
    and an assembler would still emit a relocation against the name."""
    def value(m):
        v = constants.get(m.group(2))
        if v is None:
            return m.group(0)
        lo = (v & 0xFFFF) - 0x10000 if v & 0x8000 else v & 0xFFFF
        return str(lo) if m.group(1) == 'lo' else '%#x' % (((v - lo) >> 16) & 0xFFFF)
    return re.sub(r'%(hi|lo)\((D_[0-9A-Fa-f]+)\)', value, text)


def absolute_symbols(slug):
    """Numeric constants the split assembly names like data (`%lo(D_10F00)`), from the linker symbols of the build: the
    original code holds the number, not a relocation, so the target object must define the name as a number too."""
    path = ROOT / 'build' / slug / 'symbols.ld'
    return {m.group(1): int(m.group(2), 16) for m in ABSOLUTE.finditer(path.read_text())} if path.is_file() else {}


DATA_SECTIONS = ('.rodata', '.lit4', '.lit8', '.sdata', '.sbss', '.data', '.bss', '.gcc_except_table')
DATA_NAME = re.compile(r'\bD_([0-9A-Fa-f]{8})\b')


def data_slots(slug):
    """{unit name: {section: address}}: where the link places each data section of a compiled unit. The build renames them
    to `<section>.<ADDRESS>` (build/<GAME_ID>/plan.json); the address is that of the original data the unit replaces."""
    path = ROOT / 'build' / slug / 'plan.json'
    slots = {}
    for entry in json.loads(path.read_text()).get('rename', []) if path.is_file() else []:
        unit = entry['obj'][len('obj/units/'):-len('.o')]
        for old, new in entry['sections'].items():
            key = new[len(old) + 1:]
            if old in DATA_SECTIONS and new.startswith(old + '.') and re.fullmatch(r'[0-9A-Fa-f]{8}', key):
                slots.setdefault(unit, {})[old] = int(key, 16)
    return slots


def local_data_symbols(texts, slots, sizes, known):
    """{name: (section, offset)} for the data the unit's own functions refer to by address name (`D_003F7150`) that the
    compiler keeps in a section of the unit's object: the object has no symbol there, so its reference would read
    `.rodata+0x8`, which objdiff does not equate with the original's name."""
    found = {}
    for text in texts:
        for m in DATA_NAME.finditer(text):
            name, address = m.group(0), int(m.group(1), 16)
            if name in known or name in found:
                continue
            for section, key in slots.items():
                if key <= address < key + sizes.get(section, 0):
                    found[name] = (section, address - key)
                    break
    return found


def unit_plan(slug):
    """One entry per compiled source unit: cached object, function list and the symbol renames."""
    build = ROOT / 'build' / slug
    objects = [o for o in json.loads((build / 'objects.json').read_text()) if o['kind'] == 'cc']
    cache = json.loads((build / 'objects_cache.json').read_text())
    placement = json.loads((build / 'placement.json').read_text())
    starts = {f['addr'] for f in placement['functions']}
    units = {u['name']: u for u in load_units(variant=slug)}
    owners = {}                         # symbol -> addresses of the functions that define it
    for u in units.values():
        for f in u['functions']:
            if f.get('symbol') and not f['symbol'].startswith('func_'):
                owners.setdefault(f['symbol'], set()).add(f['addr'])
    globals_ = {s: next(iter(a)) for s, a in owners.items() if len(a) == 1}
    extern_names = {}
    for u in units.values():
        for name, addr in (u.get('externs') or {}).items():
            extern_names.setdefault(name, int(addr, 0) if isinstance(addr, str) else int(addr))
    absolute = absolute_symbols(slug)
    slots = data_slots(slug)
    plan = []
    for o in objects:
        name = o['name'][len('units/'):]
        unit = units.get(name)
        cached = cache.get(o['name'])
        if unit is None or not cached or not (build / cached).is_file():
            continue
        elf = Elf((build / cached).read_bytes())
        symbols = elf.symbols()
        sections = {x['name'] for x in elf.sections}
        section_sizes = {x['name']: x['size'] for x in elf.sections}
        present = {s['name'] for s in symbols}
        defined = {s['name'] for s in symbols if s['shndx']}
        functions, redefine = [], {}
        for f in unit['functions']:
            if f.get('status') != 'source':
                continue                  # INCLUDE_ASM: still assembly, listed with the unrecovered code (remaining_plan)
            asm = ROOT / 'asm' / slug / 'nonmatchings' / ('func_%08X.s' % f['addr'])
            symbol = f.get('symbol') or ('func_%08X' % f['addr'])
            if symbol not in defined or not asm.is_file() or not f.get('size'):
                continue
            label = 'func_%08X' % f['addr']
            functions.append(dict(addr=f['addr'], symbol=symbol, status=f.get('status'),
                                  size=code_size(asm.read_text(), f['addr'], f['size']),
                                  asm=asm.relative_to(ROOT).as_posix(), label=label))
            redefine[symbol] = label
        if not functions:
            continue
        texts = [(ROOT / f['asm']).read_text() for f in functions]
        constants = {n: absolute[n] for text in texts for n in NAME.findall(text) if n in absolute}
        mine = {f['addr'] for f in functions}
        for sym in present - set(redefine):
            if sym in globals_:
                addr = globals_[sym]
                new = 'func_%08X' % addr
            elif sym in extern_names:
                addr = extern_names[sym]
                new = ('func_%08X' if addr in starts else 'D_%08X') % addr
            else:
                continue
            if sym in defined and addr in starts and addr not in mine:
                continue                  # another function's duplicate definition (weak template or inline): not this unit's
            redefine[sym] = new
        taken, clean = defined - set(redefine), {}
        for old_name, new_name in redefine.items():       # a name can be the target of one rename only
            if old_name != new_name and new_name not in taken:
                clean[old_name] = new_name
                taken.add(new_name)
        # -ffunction-sections names a function's section after its symbol (`.text._$_Q24Kaim9PoolArray`); objdiff pairs
        # symbols badly when the section name is a mangled name that no longer belongs to the symbol, so the section
        # follows the symbol's new name
        renamed = {'.text.' + f['symbol']: '.text.' + f['label'] for f in functions
                   if '.text.' + f['symbol'] in sections and f['symbol'] != f['label']}
        local = local_data_symbols(texts, slots.get(name, {}), section_sizes, present | set(clean.values()) | taken)
        plan.append(dict(name=name, base_in=cached, source=unit['source'], library=unit.get('library') or 'game',
                         functions=functions, redefine=clean, sections=renamed, constants=constants,
                         symbols=local,
                         complete=all(f.get('status') == 'source' for f in unit['functions'])))
    return plan


def remaining_plan(slug, covered):
    """Target-only units for the functions no source unit lists, one per translation unit, so that the report covers the
    whole program. Orphan pieces (`<instruction>; nop` between functions) are not functions and are left out."""
    import layout
    from progress import orphan_pieces
    build = ROOT / 'build' / slug
    fs = json.loads((build / 'placement.json').read_text())['functions']
    orphans = orphan_pieces(slug, fs)
    groups = {}
    for f in fs:
        if f['addr'] in covered or f['addr'] in orphans:
            continue
        asm = ROOT / 'asm' / slug / 'nonmatchings' / ('func_%08X.s' % f['addr'])
        if not asm.is_file():
            continue
        library = layout.library_of(f['addr'])
        stem = layout.tu_stem(layout.tu_of(f['addr']))
        unit = groups.setdefault((library, stem), dict(name='asm_%s_%s' % (library, stem), base_in=None, source=None,
                                                         library=library, functions=[], redefine={}, complete=False))
        unit['functions'].append(dict(addr=f['addr'], symbol=f['name'], status='asm',
                                      size=code_size(asm.read_text(), f['addr'], f['end'] - f['addr']),
                                      asm=asm.relative_to(ROOT).as_posix(), label='func_%08X' % f['addr']))
    return [groups[k] for k in sorted(groups)]


def run_job(slug, plan):
    """Build every target and base object in one backend job and unpack them under build/<GAME_ID>/objdiff/."""
    build = ROOT / 'build' / slug
    work = build / 'objdiff'
    work.mkdir(parents=True, exist_ok=True)
    rel = lambda cached: (Path('build') / slug / cached).as_posix()      # inputs keep repository-relative names in the job
    keys_file = work / 'keys.json'
    old_keys = json.loads(keys_file.read_text()) if keys_file.exists() else {}
    keys, todo = {}, []
    for u in plan:                       # a unit is rebuilt when its assembly, sizes, object or renames changed
        h = hashlib.sha256()
        for f in u['functions']:
            h.update((ROOT / f['asm']).read_bytes() + b'%d%s' % (f['size'], f['label'].encode()))
        if u['base_in']:
            h.update((build / u['base_in']).read_bytes() + json.dumps([u['redefine'], u.get('sections'), u.get('constants'), u.get('symbols')],
                                                                             sort_keys=True).encode())
        h.update((ROOT / 'tools/build/objdiff_job.py').read_bytes() + (ROOT / 'tools/build/elfobj.py').read_bytes())
        keys[u['name']] = h.hexdigest()
        outputs = [work / 'target' / (u['name'] + '.o')] + ([work / 'base' / (u['name'] + '.o')] if u['base_in'] else [])
        if old_keys.get(u['name']) != keys[u['name']] or not all(p.exists() for p in outputs):
            todo.append(u)
    print('objdiff: %d of %d units to build' % (len(todo), len(plan)))
    if todo:
        names = lambda u, f: 'numbers/%s.s' % f['label'] if u.get('constants') else f['asm']    # assembly as the job reads it
        send = [dict(name=u['name'], base_in=rel(u['base_in']) if u['base_in'] else None, redefine=u['redefine'],
                     sections=u.get('sections') or {}, symbols=u.get('symbols') or {},
                     functions=[dict(asm=names(u, f), label=f['label'], size=f['size']) for f in u['functions']]) for u in todo]
        (work / 'plan.json').write_text(json.dumps(dict(units=send)))
        buf = io.BytesIO()
        with tarfile.open(fileobj=buf, mode='w:gz', compresslevel=1) as tar:
            tar.add(ROOT / 'include/macro.inc', arcname='include/macro.inc')
            tar.add(ROOT / 'tools/build/elfobj.py', arcname='tools/elfobj.py')
            for unit in todo:
                if unit['base_in']:
                    tar.add(build / unit['base_in'], arcname=rel(unit['base_in']))
                for f in unit['functions']:
                    if unit.get('constants'):
                        text = numeric_names((ROOT / f['asm']).read_text(), unit['constants']).encode()
                        info = tarfile.TarInfo(names(unit, f))
                        info.size = len(text)
                        tar.addfile(info, io.BytesIO(text))
                    else:
                        tar.add(ROOT / f['asm'], arcname=f['asm'])
        build_objects(slug, work, buf.getvalue())
    keys_file.write_text(json.dumps(dict(old_keys, **keys)))


def build_objects(slug, work, payload):
    (work / 'inputs.tgz').write_bytes(payload)
    (work / 'out.tgz').unlink(missing_ok=True)
    r = subprocess.run([sys.executable, str(ROOT / 'tools/build/sandbox.py'), str(ROOT / 'tools/build/objdiff_job.py'), '--timeout', '1800',
                        '--file', 'inputs.tgz=' + str(work / 'inputs.tgz'), '--file', 'plan.json=' + str(work / 'plan.json'),
                        '--out', 'out.tgz=' + str(work / 'out.tgz')], capture_output=True, text=True)
    sys.stdout.write(r.stdout[-3000:])
    if r.returncode or not (work / 'out.tgz').exists():
        sys.stderr.write(r.stderr[-3000:])
        raise SystemExit('objdiff objects could not be built')
    with tarfile.open(work / 'out.tgz') as tar:
        tar.extractall(work, **({'filter': 'data'} if hasattr(tarfile, 'data_filter') else {}))


def write_project(slug, plan):
    libraries = sorted({u['library'] for u in plan})
    units = []
    for u in plan:
        entry = dict(name='%s/%s' % (u['library'], u['name']),
                     target_path='build/%s/objdiff/target/%s.o' % (slug, u['name']),
                     metadata=dict(complete=u['complete'], progress_categories=[u['library']]))
        if u['base_in']:
            entry['base_path'] = 'build/%s/objdiff/base/%s.o' % (slug, u['name'])
            entry['metadata']['source_path'] = u['source']
        else:
            entry['metadata']['auto_generated'] = True     # original code that is not recovered yet: counted, not listed
        units.append(entry)
    py = '.venv/bin/python' if (ROOT / '.venv/bin/python').exists() else 'python3'
    project = {'$schema': 'https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json',
               'min_version': '3.0.0', 'custom_make': py, 'custom_args': ['tools/objdiff.py', '--build'],
               'build_target': False, 'build_base': True, 'watch_patterns': ['src/**/*.c', 'src/**/*.cpp', 'include/**/*'],
               'options': OPTIONS, 'progress_categories': [dict(id=l, name=l) for l in libraries], 'units': units}
    (ROOT / 'objdiff.json').write_text(json.dumps(project, indent=2) + '\n')
    return len(units)


def report(slug):
    import toolchain
    cli = toolchain.root() / 'bin' / 'objdiff-cli'
    if not cli.is_file():
        raise SystemExit('objdiff-cli is not installed; run: python3 tools/toolchain.py install --objdiff')
    output = ROOT / 'build' / slug / 'report.json'
    subprocess.run([str(cli), 'report', 'generate', '-p', str(ROOT), '-o', str(output), '-f', 'json-pretty'], check=True)
    data = json.loads(output.read_text())
    m = data.get('measures', {})
    print('report: %s' % output.relative_to(ROOT))
    for key in ('fuzzy_match_percent', 'matched_code_percent', 'matched_functions_percent', 'complete_code_percent'):
        if key in m:
            print('  %-26s %s' % (key, m[key]))
    for key in ('total_code', 'matched_code', 'total_functions', 'matched_functions', 'complete_code', 'total_units', 'complete_units'):
        if key in m:
            print('  %-26s %s' % (key, m[key]))


def build_unit(slug, path):
    """Rebuild the objects of the unit whose base object is PATH (objdiff passes the base_path of the unit)."""
    path = Path(path)
    if path.parent.name != 'base':
        return 0                                    # target objects are fixed by the assembly; `ninja objdiff` writes them
    done = subprocess.run(['ninja', '-f', 'build.ninja', 'build/%s/compiled.stamp' % slug], cwd=ROOT)
    if done.returncode:
        return done.returncode
    plan = [u for u in unit_plan(slug) if u['name'] == path.stem]
    if not plan:
        raise SystemExit('no source unit %s in the last full build; run `ninja` and `ninja objdiff` first' % path.stem)
    run_job(slug, plan)
    return 0


def main():
    if sys.argv[1:2] == ['--build']:
        if len(sys.argv) != 3:
            raise SystemExit('usage: objdiff.py --build PATH')
        return build_unit(DEFAULT, sys.argv[2])
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    slug = args[0] if args else DEFAULT
    if slug != DEFAULT:
        raise SystemExit('source units apply to %s only' % DEFAULT)
    plan = unit_plan(slug)
    plan += remaining_plan(slug, {f['addr'] for u in plan for f in u['functions']})
    run_job(slug, plan)
    print('objdiff.json: %d units, %d functions' % (write_project(slug, plan), sum(len(u['functions']) for u in plan)))
    if '--report' in sys.argv:
        report(slug)
    return 0


if __name__ == '__main__':
    sys.exit(main())
