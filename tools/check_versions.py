#!/usr/bin/env python3
"""Rebuild every supported version and print OK or MISMATCH for each; run before a release or after changes to shared build tools.

Usage: check_versions.py [GAME_ID ...]     default: all versions of config/variants.json, USA first
For each version it runs `configure.py --version GAME_ID` and `ninja`, and prints one line per version:
  OK        the rebuilt executable has the SHA-256 recorded in config/<GAME_ID>/checksums.sha256
  MISMATCH  ninja ran and reported a mismatch (its report follows)
  ERROR     the build did not finish (missing executable in orig/, toolchain or backend failure); the check stops there
At the end build.ninja is configured for SLUS_213.76 again. Exit status 0 only if every version is OK.
Routine work checks SLUS_213.76 only (plain `ninja`); the other four versions are rebuilt from assembly.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT = 'SLUS_213.76'


def versions():
    found = json.loads((ROOT / 'config/variants.json').read_text())
    names = [v for v in found if (ROOT / 'config' / v / 'checksums.sha256').exists()]
    return sorted(names, key=lambda v: (v != DEFAULT, v))


def run(cmd):
    return subprocess.run(cmd, cwd=ROOT, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)


def check(version):
    """Configure and build one version; return (status, output) with status OK, MISMATCH or ERROR."""
    c = run([sys.executable, 'configure.py', '--version', version])
    if c.returncode:
        return 'ERROR', c.stdout
    b = run(['ninja'])
    if b.returncode == 0:      # an up-to-date build prints nothing, so the image is compared again (cheap)
        boot = json.loads((ROOT / 'config/variants.json').read_text())[version]['boot']
        k = run([sys.executable, 'tools/check_elf.py', version, 'build/%s/%s.elf' % (version, boot)])
        return ('OK' if k.returncode == 0 else 'MISMATCH'), k.stdout
    if any(l.startswith('MISMATCH') for l in b.stdout.splitlines()):
        return 'MISMATCH', b.stdout
    return 'ERROR', b.stdout


def main():
    wanted = [a for a in sys.argv[1:] if not a.startswith('-')] or versions()
    unknown = [v for v in wanted if v not in versions()]
    if unknown:
        raise SystemExit('unknown version %s; known: %s' % (', '.join(unknown), ', '.join(versions())))
    results = {}
    try:
        for v in wanted:
            status, out = check(v)
            results[v] = status
            print('%-9s %s' % (status, v), flush=True)
            if status != 'OK':
                print('\n'.join('    ' + l for l in out.splitlines()[-25:]))
            if status == 'ERROR':
                print('stopping: the build for %s did not finish (check orig/, the toolchain and the backend)' % v)
                break
    finally:
        run([sys.executable, 'configure.py', '--version', DEFAULT])
    ok = all(s == 'OK' for s in results.values()) and len(results) == len(wanted)
    print('\nall %d versions OK' % len(wanted) if ok else '\nnot all versions are OK')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
