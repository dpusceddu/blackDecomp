#!/usr/bin/env python3
"""Build the NON_MATCHING drafts into a separate executable (`python3 configure.py --non-matching`, then `ninja`).

The matching build compiles only recovered functions; here every `#ifdef NON_MATCHING` block of the translation unit files is
compiled too and replaces the assembly of its function. Drafts are not byte-exact, so the result is not compared with the
original: the rebuild is shiftable, the linker moves everything and fixes the references (it is not expected to boot).
A translation unit whose drafts do not compile or link keeps its matching version; the list is in
build/<GAME_ID>-nm/nm_fallback.json. Output: build/<GAME_ID>-nm/<boot>.nonmatching.elf and a summary line.
Usage: nm_build.py [GAME_ID]
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, os, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
PY = sys.executable


def run(*args, check=True):
    r = subprocess.run([PY] + [str(a) for a in args], cwd=ROOT, capture_output=True, text=True,
                       env=dict(os.environ, BLACK_NON_MATCHING='1'))
    if check and r.returncode not in (0,):
        sys.stdout.write(r.stdout[-6000:] + r.stderr[-3000:])
        raise SystemExit('nm_build: %s failed' % ' '.join(str(a) for a in args[:2]))
    return r


def main():
    slug = sys.argv[1] if len(sys.argv) > 1 and not sys.argv[1].startswith('-') else 'SLUS_213.76'
    boot = json.loads((ROOT / 'config/versions.json').read_text())[slug]['boot']
    out = ROOT / 'build' / (slug + '-nm')
    out.mkdir(parents=True, exist_ok=True)
    fallback = out / 'nm_fallback.json'
    fallback.unlink(missing_ok=True)
    (out / 'units-nm.json').unlink(missing_ok=True)
    for attempt in range(8):
        run('tools/build/units.py', slug)
        run('tools/build/make_ld.py', slug)
        r = run('tools/build/build_objects.py', slug, '--compile-only', check=False)
        if r.returncode == 75:
            print(r.stdout.strip().split('\n')[-1])
            continue
        if r.returncode and not (out / 'results.json').exists():
            sys.stdout.write(r.stdout[-3000:] + r.stderr[-3000:])
            raise SystemExit('nm_build: the build backend failed')
        run('tools/build/units_verify.py', 'prepare', check=False)
        run('tools/build/units.py', slug)
        run('tools/build/make_ld.py', slug)
        r = run('tools/build/build_objects.py', slug, check=False)
        if r.returncode == 0:
            break
        lk = run('tools/build/units_verify.py', 'link', check=False)
        problems = json.loads((out / 'unit_problems.json').read_text())
        names = {p[0] for p in problems}
        known = set(json.loads(fallback.read_text())) if fallback.exists() else set()
        if not names - known:
            sys.stdout.write(r.stdout[-3000:] + lk.stdout[-2000:])
            raise SystemExit('nm_build: the link failed')
        fallback.write_text(json.dumps(sorted(known | names)))
        print('non-matching: %d more translation units keep their matching version (link errors)' % len(names - known))
    else:
        raise SystemExit('nm_build: no stable set of translation units after 8 attempts')
    elf = out / (boot + '.nonmatching.elf')
    p = run('tools/build/pack_elf.py', out / 'linked.elf', ROOT / 'config' / slug / 'layout.json', ROOT / 'data' / slug / 'elf', elf)
    units = json.loads((out / 'units-nm.json').read_text())['units']
    kept = set(json.loads(fallback.read_text())) if fallback.exists() else set()
    asm = {f['addr'] for u in json.loads((ROOT / 'build' / slug / 'units.json').read_text())['units'] for f in u['functions'] if f['status'] == 'source'}
    now = {f['addr'] for u in units for f in u['functions'] if f['status'] == 'source'}
    print('%s: %d bytes; %d draft functions compiled in, %d translation units kept their matching version' % (
        elf.relative_to(ROOT), elf.stat().st_size, len(now - asm), len(kept)))


if __name__ == '__main__':
    main()
