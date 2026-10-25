#!/usr/bin/env python3
"""Compare a rebuilt executable with the target hash in config/<GAME_ID>/checksums.sha256.
Usage: check_elf.py GAME_ID BUILT.elf [--stamp FILE]
Prints OK if the SHA-256 is equal. Otherwise prints a mismatch report: size, e_flags, entry and the sections whose
header or content differ, compared with the target image in orig/ (private) when it is present, followed by the functions (and source
files) that own the differing words."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    slug, built = sys.argv[1], Path(sys.argv[2])
    want = None
    sums = ROOT / 'config' / slug / 'checksums.sha256'
    for line in (sums.read_text().split('\n') if sums.exists() else []):
        if line and not line.startswith('#'):
            h, name = line.split()
            want = h, name
    if not want:
        raise SystemExit('no target hash for %s: expected %s' % (slug, sums.relative_to(ROOT)))
    data = built.read_bytes()
    got = hashlib.sha256(data).hexdigest()
    if got == want[0]:
        print('OK  %s  %s  sha256 %s' % (want[1], slug, got))
        if '--stamp' in sys.argv:
            Path(sys.argv[sys.argv.index('--stamp') + 1]).write_text(got + '\n')
        return 0
    print('MISMATCH  %s  %s\n  want %s\n  got  %s  (%d bytes)' % (want[1], slug, want[0], got, len(data)))
    ref = ROOT / 'orig' / slug / want[1]
    if ref.exists():
        explained = False
        if (built.parent/'objects.json').exists() and slug=='SLUS_213.76':
            sys.path[:0]=[str(ROOT/'tools'),str(ROOT/'tools/build')]
            from unit_compare import compare
            explained = bool(compare(slug,built.parent))
        if not explained:
            subprocess.run([sys.executable,str(ROOT/'tools/diffelf.py'),str(ref),str(built)])
    return 1


if __name__ == '__main__':
    sys.exit(main())
