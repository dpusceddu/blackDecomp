"""Fix-ups for relocatable objects written by the SN assembler (-snas) so that mainline GNU ld accepts them.

The SN assembler does not keep local symbols in front of the global ones in `.symtab` (C++ objects interleave
`__FRAME_BEGIN__n` locals with globals) and writes sh_info (index of the first non-local symbol) as the number of
section symbols. Mainline ld rejects both ("local symbol at index N >= sh_info"). The symbol table is stably
reordered, locals first, the symbol indices of every relocation entry are renumbered, and sh_info is set. No code,
data or relocation type/offset changes; symbol names, values and bindings are unchanged.
"""
import struct


def normalize_object(data):
    """Return the object bytes with a loader-compatible .symtab (locals first, correct sh_info)."""
    if data[:4] != b'\x7fELF' or data[4] != 1 or data[5] != 1:
        return data
    shoff, = struct.unpack_from('<I', data, 32)
    shentsize, shnum = struct.unpack_from('<HH', data, 46)
    out = bytearray(data)
    hdrs = [struct.unpack_from('<IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    for i, h in enumerate(hdrs):
        if h[1] != 2:  # SHT_SYMTAB
            continue
        off, size = h[4], h[5]
        count = size // 16
        syms = [data[off + k * 16: off + k * 16 + 16] for k in range(count)]
        local = lambda s: (s[12] >> 4) == 0
        order = [k for k in range(count) if local(syms[k])] + [k for k in range(count) if not local(syms[k])]
        new_index = {old: new for new, old in enumerate(order)}
        for new, old in enumerate(order):
            out[off + new * 16: off + new * 16 + 16] = syms[old]
        struct.pack_into('<I', out, shoff + i * shentsize + 28, sum(1 for s in syms if local(s)))
        if order != list(range(count)):
            for j, r in enumerate(hdrs):
                if r[1] == 9 and r[6] == i:   # SHT_REL pointing at this symbol table
                    for o in range(r[4], r[4] + r[5], 8):
                        info, = struct.unpack_from('<I', data, o + 4)
                        struct.pack_into('<I', out, o + 4, (new_index[info >> 8] << 8) | (info & 0xFF))
                elif r[1] == 4 and r[6] == i:  # SHT_RELA
                    for o in range(r[4], r[4] + r[5], 12):
                        info, = struct.unpack_from('<I', data, o + 4)
                        struct.pack_into('<I', out, o + 4, (new_index[info >> 8] << 8) | (info & 0xFF))
    return bytes(out)


def undefine_dropped(data, keep):
    """Make the global symbols defined in sections the link will not place undefined, so that they resolve to the
    original definitions elsewhere in the image (vtables, unwind data and other duplicates a compiled unit emits).
    `keep` is the set of section names that will be linked; only allocated sections outside it are dropped."""
    shoff, = struct.unpack_from('<I', data, 32)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 46)
    out = bytearray(data)
    hdrs = [struct.unpack_from('<IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    names = data[hdrs[shstrndx][4]:hdrs[shstrndx][4] + hdrs[shstrndx][5]]
    name = lambda i: names[hdrs[i][0]:].split(b'\0', 1)[0].decode()
    dropped = {i for i in range(1, shnum) if hdrs[i][2] & 2 and name(i) not in keep}
    count = 0
    for i, h in enumerate(hdrs):
        if h[1] != 2:
            continue
        for k in range(h[5] // 16):
            o = h[4] + k * 16
            n, value, size, info, other, shndx = struct.unpack_from('<IIIBBH', data, o)
            if shndx in dropped and (info >> 4) != 0:
                struct.pack_into('<IIIBBH', out, o, n, 0, 0, info & 0xF0, other, 0)
                count += 1
    return bytes(out), count
