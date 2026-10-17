"""Fix-ups for relocatable objects written by the SN assembler (-snas) so that mainline GNU ld accepts them.

The SN assembler writes the `.symtab` header's sh_info (index of the first non-local symbol) as the number of
section symbols instead of the number of local symbols, and mainline ld rejects the object ("local symbol at index N
>= sh_info"). Only that header word is corrected; no code, data, symbol or relocation byte changes.
"""
import struct


def fix_symtab_info(data):
    """Return the object bytes with .symtab sh_info set to the first non-local symbol index."""
    if data[:4] != b'\x7fELF' or data[4] != 1 or data[5] != 1:
        return data
    shoff, = struct.unpack_from('<I', data, 32)
    shentsize, shnum = struct.unpack_from('<HH', data, 46)
    out = bytearray(data)
    for i in range(shnum):
        o = shoff + i * shentsize
        typ, = struct.unpack_from('<I', data, o + 4)
        if typ != 2:
            continue
        off, size = struct.unpack_from('<II', data, o + 16)
        count = size // 16
        first_global = count
        for k in range(count):
            if data[off + k * 16 + 12] >> 4:  # st_info bind: any non-local binding
                first_global = k
                break
        struct.pack_into('<I', out, o + 28, first_global)
    return bytes(out)
