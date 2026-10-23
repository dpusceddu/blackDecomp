"""Small ELF32 reader (little-endian, any machine) used by the Phase 0 tools."""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, struct

SHT = {0: 'NULL', 1: 'PROGBITS', 2: 'SYMTAB', 3: 'STRTAB', 4: 'RELA', 5: 'HASH', 6: 'DYNAMIC', 7: 'NOTE',
       8: 'NOBITS', 9: 'REL', 11: 'DYNSYM', 0x70000000: 'MIPS_REGINFO', 0x70000003: 'MIPS_DEBUG',
       0x70000006: 'MIPS_REGINFO', 0x70000700: 'EE_IOPMOD', 0x70000080: 'EE_EEMOD', 0x70000014: 'MIPS_DWARF'}


class Elf:
    def __init__(self, data):
        self.data = data
        if data[:4] != b'\x7fELF' or data[4] != 1 or data[5] != 1:
            raise ValueError('not a little-endian ELF32')
        (self.type, self.machine, _, self.entry, self.phoff, self.shoff, self.flags, _, self.phentsize,
         self.phnum, self.shentsize, self.shnum, self.shstrndx) = struct.unpack_from('<HHIIIIIHHHHHH', data, 16)
        self.sections = []
        for i in range(self.shnum):
            n, t, fl, addr, off, size, link, info, al, es = struct.unpack_from(
                '<IIIIIIIIII', data, self.shoff + i * self.shentsize)
            self.sections.append(dict(index=i, name_off=n, type=t, flags=fl, addr=addr, offset=off, size=size,
                                      link=link, info=info, align=al, entsize=es))
        if self.shnum:
            names = self.content(self.sections[self.shstrndx])
            for s in self.sections:
                s['name'] = names[s['name_off']:].split(b'\0', 1)[0].decode('latin1')
        self.segments = []
        for i in range(self.phnum):
            t, off, va, pa, fs, ms, fl, al = struct.unpack_from('<IIIIIIII', data, self.phoff + i * self.phentsize)
            self.segments.append(dict(type=t, offset=off, vaddr=va, filesz=fs, memsz=ms, flags=fl, align=al))

    def content(self, s):
        if s['type'] == 8:
            return b''
        return self.data[s['offset']:s['offset'] + s['size']]

    def section(self, name):
        return next((s for s in self.sections if s.get('name') == name), None)

    def symbols(self, table='.symtab'):
        s = self.section(table)
        if not s or not s['size']:
            return []
        strs = self.content(self.sections[s['link']])
        out = []
        c = self.content(s)
        for o in range(0, len(c) - 15, 16):
            n, v, sz, info, other, shn = struct.unpack_from('<IIIBBH', c, o)
            out.append(dict(name=strs[n:].split(b'\0', 1)[0].decode('latin1'), value=v, size=sz,
                            type=info & 15, bind=info >> 4, shndx=shn))
        return out

    def summary(self):
        return dict(type=self.type, machine=self.machine, entry=self.entry, flags=self.flags,
                    segments=[dict(t=g['type'], va=g['vaddr'], fsz=g['filesz'], msz=g['memsz'], fl=g['flags'])
                              for g in self.segments],
                    sections=[dict(name=s['name'], type=SHT.get(s['type'], hex(s['type'])), addr=s['addr'],
                                   size=s['size'], flags=s['flags']) for s in self.sections if s['index']])


def sha256(b):
    return hashlib.sha256(b).hexdigest()
