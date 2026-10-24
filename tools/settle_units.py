#!/usr/bin/env python3
"""Bring config/units.yaml to a state that links to the identical image.

Compiles every unit, demotes functions whose object cannot take the place of the assembly (units_verify.py prepare),
then links repeatedly, demoting the units the linker names, and finally demotes the units owning any differing word.
Usage: settle_units.py [SLUG]         (needs the toolchain; ends by running ninja, which must print OK)
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import subprocess, sys
from pathlib import Path
import yaml

ROOT = Path(__file__).resolve().parents[1]
PY = sys.executable
SLUG = 'SLUS_213.76'


def source_addresses(text):
    data = yaml.safe_load(text) or {}
    return {int(f['addr'], 0) if isinstance(f['addr'], str) else f['addr']
            for unit in data.get('units', []) for f in unit['functions'] if f.get('status') == 'source'}


def check_source_regression(path, original, protected, stage):
    missing = protected - source_addresses(path.read_bytes())
    if missing:
        path.write_bytes(original)
        sample = ', '.join(hex(a) for a in sorted(missing)[:8])
        raise SystemExit('Source regression after %s: settlement demoted %d committed functions (%s). '
                         'Restored the input units file; fix the candidate or placement before retrying.' %
                         (stage, len(missing), sample))


def infrastructure_failure(output):
    return any(message in output for message in (
        'Build backend failed', 'Connection refused',
        'Connection reset by peer', 'subprocess.TimeoutExpired',
    ))


def run(*args, check=True):
    r = subprocess.run([PY] + [str(a) for a in args], cwd=ROOT, capture_output=True, text=True)
    if infrastructure_failure(r.stdout + r.stderr):
        raise SystemExit(r.stdout + r.stderr)
    if check and r.returncode:
        raise SystemExit(r.stdout + r.stderr)
    return r


def ninja():
    r = subprocess.run(['ninja'], cwd=ROOT, capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


def main():
    units = ROOT / 'config/units.yaml'
    original_units = units.read_bytes()
    committed = subprocess.run(['git', 'show', 'HEAD:config/units.yaml'], cwd=ROOT, capture_output=True)
    protected = source_addresses(committed.stdout) if committed.returncode == 0 else set()
    # Explicit storage and shared constants depend on the current manifest. Do
    # not validate a new ownership claim against an earlier placement snapshot.
    print(run('tools/split_objects.py', SLUG).stdout.strip().split('\n')[-1])
    print(run('tools/make_ld.py', SLUG).stdout.strip())
    results = ROOT / 'build' / SLUG / 'results.json'
    results.unlink(missing_ok=True)
    compiled = run('tools/build_objects.py', SLUG, '--compile-only', check=False)
    # Compiler failures can be settled, but a missing worker response cannot.
    if compiled.returncode and not results.exists():
        raise SystemExit(compiled.stdout + compiled.stderr)
    print(compiled.stdout.strip().split('\n')[-1])
    print(run('tools/units_verify.py', 'prepare').stdout.strip())
    check_source_regression(units, original_units, protected, 'prepare')
    for i in range(10):
        rc, out = ninja()
        if infrastructure_failure(out):
            raise SystemExit(out)
        if 'build:' in out and 'rc=0' not in out:
            print('link failed:', run('tools/units_verify.py', 'link').stdout.strip().split('\n')[0])
            check_source_regression(units, original_units, protected, 'link')
            continue
        if rc == 0:
            print(out.strip())
            print('identical')
            return 0
        r = run('tools/units_verify.py', 'compare', '--fix')
        check_source_regression(units, original_units, protected, 'compare')
        print(r.stdout.strip())
    return 1


if __name__ == '__main__':
    SLUG = sys.argv[1] if len(sys.argv) > 1 else 'SLUS_213.76'
    sys.exit(main())
