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
one progress category per library. Functions not compiled from a unit are not part of any object; the report therefore
measures the share of recovered source, not the whole program. `--report` then runs objdiff-cli (see
`tools/toolchain.py install --objdiff`) and writes build/<GAME_ID>/report.json.

objdiff compares instructions and relocations: a function can match here and still not be byte-exact in the image (data
placement), and the other way round for constants that the compiler names differently. The build's `OK` and
`ninja progress` remain the authority for exactness.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, io, json, subprocess, sys, tarfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf
from units import load_units

ROOT = Path(__file__).resolve().parents[1]
DEFAULT = 'SLUS_213.76'
OPTIONS = {'demangler': 'gnu_legacy'}      # the SN compiler mangles like GCC 2.x


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
    plan = []
    for o in objects:
        name = o['name'][len('units/'):]
        unit = units.get(name)
        cached = cache.get(o['name'])
        if unit is None or not cached or not (build / cached).is_file():
            continue
        present = {s['name'] for s in Elf((build / cached).read_bytes()).symbols()}
        functions, redefine = [], {}
        for f in unit['functions']:
            asm = ROOT / 'asm' / slug / 'nonmatchings' / ('func_%08X.s' % f['addr'])
            symbol = f.get('symbol') or ('func_%08X' % f['addr'])
            if symbol not in present or not asm.is_file() or not f.get('size'):
                continue
            label = 'func_%08X' % f['addr']
            functions.append(dict(addr=f['addr'], symbol=symbol, status=f.get('status'), size=f['size'],
                                  asm=asm.relative_to(ROOT).as_posix(), label=label))
            redefine[symbol] = label
        if not functions:
            continue
        for sym in present - set(redefine):
            if sym in globals_:
                redefine[sym] = 'func_%08X' % globals_[sym]
            elif sym in extern_names:
                addr = extern_names[sym]
                redefine[sym] = ('func_%08X' if addr in starts else 'D_%08X') % addr
        taken, clean = set(present) - set(redefine), {}
        for old_name, new_name in redefine.items():       # a name can be the target of one rename only
            if old_name != new_name and new_name not in taken:
                clean[old_name] = new_name
                taken.add(new_name)
        plan.append(dict(name=name, base_in=cached, source=unit['source'], library=unit.get('library') or 'game',
                         functions=functions, redefine=clean,
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
        unit['functions'].append(dict(addr=f['addr'], symbol=f['name'], status='asm', size=f['end'] - f['addr'],
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
            h.update((build / u['base_in']).read_bytes() + json.dumps(u['redefine'], sort_keys=True).encode())
        h.update((ROOT / 'tools/objdiff_job.py').read_bytes())
        keys[u['name']] = h.hexdigest()
        outputs = [work / 'target' / (u['name'] + '.o')] + ([work / 'base' / (u['name'] + '.o')] if u['base_in'] else [])
        if old_keys.get(u['name']) != keys[u['name']] or not all(p.exists() for p in outputs):
            todo.append(u)
    print('objdiff: %d of %d units to build' % (len(todo), len(plan)))
    if todo:
        send = [dict(name=u['name'], base_in=rel(u['base_in']) if u['base_in'] else None, redefine=u['redefine'],
                     functions=[dict(asm=f['asm'], label=f['label'], size=f['size']) for f in u['functions']]) for u in todo]
        (work / 'plan.json').write_text(json.dumps(dict(units=send)))
        buf = io.BytesIO()
        with tarfile.open(fileobj=buf, mode='w:gz', compresslevel=1) as tar:
            tar.add(ROOT / 'include/macro.inc', arcname='include/macro.inc')
            for unit in todo:
                if unit['base_in']:
                    tar.add(build / unit['base_in'], arcname=rel(unit['base_in']))
                for f in unit['functions']:
                    tar.add(ROOT / f['asm'], arcname=f['asm'])
        build_objects(slug, work, buf.getvalue())
    keys_file.write_text(json.dumps(dict(old_keys, **keys)))


def build_objects(slug, work, payload):
    (work / 'inputs.tgz').write_bytes(payload)
    (work / 'out.tgz').unlink(missing_ok=True)
    r = subprocess.run([sys.executable, str(ROOT / 'tools/sandbox.py'), str(ROOT / 'tools/objdiff_job.py'), '--timeout', '1800',
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
