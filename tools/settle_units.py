#!/usr/bin/env python3
"""Bring config/units.yaml to a state that links to the identical image.

Compiles every unit, demotes functions whose object cannot take the place of the assembly (units_verify.py prepare),
then links repeatedly, demoting the units the linker names, and finally demotes the units owning any differing word.
Usage: settle_units.py [SLUG]         (needs the build backend; ends by running ninja, which must print OK)
"""
import subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PY = sys.executable
SLUG = 'usa-retail'


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
    print(run('tools/make_ld.py', SLUG).stdout.strip())
    results = ROOT / 'build' / SLUG / 'results.json'
    results.unlink(missing_ok=True)
    compiled = run('tools/build_objects.py', SLUG, '--compile-only', check=False)
    # Compiler failures can be settled, but a missing worker response cannot.
    if compiled.returncode and not results.exists():
        raise SystemExit(compiled.stdout + compiled.stderr)
    print(compiled.stdout.strip().split('\n')[-1])
    print(run('tools/units_verify.py', 'prepare').stdout.strip())
    for i in range(10):
        rc, out = ninja()
        if infrastructure_failure(out):
            raise SystemExit(out)
        if 'build:' in out and 'rc=0' not in out:
            print('link failed:', run('tools/units_verify.py', 'link').stdout.strip().split('\n')[0])
            continue
        if rc == 0:
            print(out.strip())
            print('identical')
            return 0
        r = run('tools/units_verify.py', 'compare', '--fix')
        print(r.stdout.strip())
    return 1


if __name__ == '__main__':
    SLUG = sys.argv[1] if len(sys.argv) > 1 else 'usa-retail'
    sys.exit(main())
