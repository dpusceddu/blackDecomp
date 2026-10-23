#!/usr/bin/env python3
"""Print the sections, symbols and relocations of a relocatable ELF object (reads the file only).
Usage: objdump.py OBJECT [-r]"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf

RELOC = {2: 'R_MIPS_32', 4: 'R_MIPS_26', 5: 'R_MIPS_HI16', 6: 'R_MIPS_LO16', 7: 'R_MIPS_GPREL16', 10: 'R_MIPS_PC16'}


def relocations(e, sec):
    syms = e.symbols()
    out = []
    for t in e.sections:
        if t['type'] == 9 and t['info'] == sec['index']:
            c = e.content(t)
            for o in range(0, len(c), 8):
                off, info = struct.unpack_from('<II', c, o)
                out.append((off, info & 255, syms[info >> 8]))
    return out


def main():
    e = Elf(Path(sys.argv[1]).read_bytes())
    for s in e.sections[1:]:
        print('%2d %-24s type %-9d size %6d align %3d flags %#x' % (s['index'], s['name'], s['type'], s['size'], s['align'], s['flags']))
    print()
    for i, y in enumerate(e.symbols()):
        print('%3d %-48s val %#8x size %5d type %d bind %d shndx %d' % (i, y['name'], y['value'], y['size'], y['type'], y['bind'], y['shndx']))
    if '-r' in sys.argv:
        for s in e.sections:
            if s['type'] == 9:
                print('\nrelocations for', e.sections[s['info']]['name'])
                for off, kind, y in relocations(e, e.sections[s['info']]):
                    print('  %#6x %-16s %s' % (off, RELOC.get(kind, kind), y['name'] or 'section#%d' % y['shndx']))


if __name__ == '__main__':
    main()
