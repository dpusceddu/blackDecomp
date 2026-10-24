"""Resolve words in compiler-owned constants for matching, including switch targets.

This reads relocatable objects on the host; it neither links nor modifies them.
The full worker link and image comparison remain the placement authority.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import re
import struct

IMAGE_SYMBOL = re.compile(r'^(?:func|D|jtbl|ehtbl)_([0-9A-Fa-f]{6,8})$')


def constant_word(elf, symbols, section, offset, function, address):
    """Four bytes as they would link, or None for an unsupported relocation.

Only an R_MIPS_32 word referring to the candidate's own code or a named image
symbol can be resolved here. Other relocation kinds/targets remain uncertain.
"""
    data = elf.content(section)
    if not 0 <= offset <= len(data) - 4:
        return None
    raw = data[offset:offset + 4]
    for rel in elf.sections:
        if rel['type'] != 9 or rel['info'] != section['index']:
            continue
        entries = elf.content(rel)
        for pos in range(0, len(entries), 8):
            where, info = struct.unpack_from('<II', entries, pos)
            if not offset - 3 <= where <= offset + 3:
                continue
            if where != offset or info & 255 != 2:
                return None
            symbol = symbols[info >> 8]
            named = IMAGE_SYMBOL.fullmatch(symbol['name'])
            if symbol['shndx'] == 0xfff1:
                base = symbol['value']
            elif named:
                base = int(named.group(1), 16)
            elif address is not None and symbol['shndx'] == function['shndx']:
                base = address + symbol['value'] - function['value']
            else:
                return None
            value = (base + int.from_bytes(raw, 'little')) & 0xffffffff
            return struct.pack('<I', value)
    return raw
