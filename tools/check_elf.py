#!/usr/bin/env python3
"""Compare a rebuilt executable with the target hash in config/checksums.sha256.
Usage: check_elf.py VARIANT_SLUG BUILT.elf [--stamp FILE]
Prints OK if the SHA-256 is equal. Otherwise prints a mismatch report: size, e_flags, entry and the sections whose
header or content differ, compared with the target image in orig/ (private) when it is present."""
import hashlib, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    slug, built = sys.argv[1], Path(sys.argv[2])
    want = None
    for line in (ROOT / 'config/checksums.sha256').read_text().split('\n'):
        if line and not line.startswith('#'):
            h, s, name = line.split()
            if s == slug:
                want = h, name
    if not want:
        raise SystemExit('no target hash for %s in config/checksums.sha256' % slug)
    data = built.read_bytes()
    got = hashlib.sha256(data).hexdigest()
    if got == want[0]:
        print('OK  %s  %s  sha256 %s' % (want[1], slug, got))
        if '--stamp' in sys.argv:
            Path(sys.argv[sys.argv.index('--stamp') + 1]).write_text(got + '\n')
        return 0
    print('MISMATCH  %s  %s\n  want %s\n  got  %s  (%d bytes)' % (want[1], slug, want[0], got, len(data)))
    ref = ROOT / 'orig' / slug / 'files' / want[1]
    if ref.exists():
        subprocess.run([sys.executable, str(ROOT / 'tools/diffelf.py'), str(ref), str(built)])
    return 1


if __name__ == '__main__':
    sys.exit(main())
