#!/usr/bin/env python3
"""Compare two ELF files section by section (a debugging aid for the identical rebuild).
Usage: diffelf.py REFERENCE.elf BUILT.elf [--words N]   shows differing sections, first differing words."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf


def main():
    a, b = Path(sys.argv[1]).read_bytes(), Path(sys.argv[2]).read_bytes()
    n = int(sys.argv[sys.argv.index('--words') + 1]) if '--words' in sys.argv else 6
    ea, eb = Elf(a), Elf(b)
    print('size', len(a), len(b), 'e_flags %x %x' % (ea.flags, eb.flags), 'entry %x %x' % (ea.entry, eb.entry))
    sb = {s['name']: s for s in eb.sections}
    for x in ea.sections[1:]:
        y = sb.get(x['name'])
        if y is None:
            print('missing section', x['name'])
            continue
        ca, cb = ea.content(x), eb.content(y)
        hdr = (x['addr'], x['size'], x['offset'], x['type'], x['flags'], x['align']) != \
              (y['addr'], y['size'], y['offset'], y['type'], y['flags'], y['align'])
        if ca != cb or hdr:
            diff = [i for i in range(0, min(len(ca), len(cb)), 4) if ca[i:i + 4] != cb[i:i + 4]]
            print('%-20s hdr %s content %s: %d words differ of %d, sizes %#x/%#x addr %#x/%#x' % (
                x['name'][:20], 'DIFF' if hdr else 'same', 'DIFF' if ca != cb else 'same', len(diff), len(ca) // 4,
                x['size'], y['size'], x['addr'], y['addr']))
            for i in diff[:n]:
                print('    +%#x  want %s  got %s' % (i, ca[i:i + 4].hex(), cb[i:i + 4].hex()))


main()
