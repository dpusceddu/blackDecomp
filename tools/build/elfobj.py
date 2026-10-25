"""Fix-ups for relocatable objects written by the SN assembler (-snas) so that mainline GNU ld accepts them.

The SN assembler does not keep local symbols in front of the global ones in `.symtab` (C++ objects interleave
`__FRAME_BEGIN__n` locals with globals) and writes sh_info (index of the first non-local symbol) as the number of
section symbols. Mainline ld rejects both ("local symbol at index N >= sh_info"). The symbol table is stably
reordered, locals first, the symbol indices of every relocation entry are renumbered, and sh_info is set. No code,
data or relocation type/offset changes; symbol names, values and bindings are unchanged.

The separate discarded-input helpers retain original assembly bindings. Kept
absolute function-entry pointers may use an existing global symbol instead of a
local section symbol; the final linked address is unchanged.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
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


def restore_gprel(data):
    """SN has no explicit GPREL16 operand under -G0. Translate marked symbolic
    .word relocations to their declared instruction and R_MIPS_GPREL16. Neither
    symbol targets nor addends are inferred from the image or patched at link.
    """
    from elfinfo import Elf
    import re
    elf = Elf(data)
    out = bytearray(data)
    for symbol in elf.symbols():
        marker = re.fullmatch(r'__(gprel|jump)_([0-9A-F]{8})_[0-9A-F]{8}', symbol['name'])
        if not marker:
            continue
        section = elf.sections[symbol['shndx']]
        offset = symbol['value']
        matches = []
        for reloc in elf.sections:
            if reloc['type'] == 9 and reloc['info'] == symbol['shndx']:
                for at in range(reloc['offset'], reloc['offset']+reloc['size'], 8):
                    address, info = struct.unpack_from('<II', data, at)
                    if address == offset:
                        matches.append((at, info))
        if len(matches) != 1 or matches[0][1] & 255 != 2:
            raise ValueError('GP marker needs exactly one R_MIPS_32 relocation: '+symbol['name'])
        at, info = matches[0]
        addend = struct.unpack_from('<I', data, section['offset']+offset)[0]
        if marker[1] == 'gprel' and 0x8000 <= addend < 0xffff8000:
            raise ValueError('GP addend does not fit the instruction field')
        struct.pack_into('<I', out, section['offset']+offset, int(marker[2],16) | (addend >> 2 if marker[1] == 'jump' else addend & 0xffff))
        struct.pack_into('<I', out, at+4, (info & ~255) | (4 if marker[1] == 'jump' else 7))
    return bytes(out)


def fit_included_sections(data, spec):
    """Remove only SN's zero section tails and excessive default alignment from
    original assembly inputs. Recovered C code never passes through this rule.
    The original include spans already contain their real instruction/padding words.
    """
    from elfinfo import Elf
    elf = Elf(data)
    syms = {s['name']:s for s in elf.symbols()}
    bounds = {}
    for f in spec['unit']['functions']:
        marker = syms.get('__nonmatching_func_%08X' % f['addr'])
        if marker:
            bounds[elf.sections[marker['shndx']]['name']] = (f['addr'],f['size'])
    for sec, slots in spec.get('slots',{}).items():
        for low, high, addr in slots:
            bounds['%s.%08X' % (sec,low)] = (low,high-low)
    out = bytearray(data)
    trims = {}
    for name,(address,span) in bounds.items():
        section = elf.section(name)
        if not section:
            continue
        alignment = min(section['align'], address & -address)
        struct.pack_into('<I',out,elf.shoff+section['index']*elf.shentsize+32,alignment)
        if section['size'] > span:
            if any(elf.content(section)[span:]):
                raise ValueError('assembler emitted nonzero bytes beyond '+name)
            trims[name] = span
    return trim_sections(bytes(out),trims) if trims else bytes(out)


def split_text_sections(data, spec):
    """Split an unsectioned compiler text input without changing code or CFI.

    This preserves compilers' native unwind ranges when -ffunction-sections changes
    their end labels. Relocations to the former section become function-relative;
    no per-function object or address-keyed section is created.
    """
    from elfinfo import Elf
    elf = Elf(data)
    text = elf.section('.text')
    if not text or not text['size']:
        return data
    syms = elf.symbols()
    defined = {s['name']:(i,s) for i,s in enumerate(syms) if s['shndx']==text['index'] and s['type']==2}
    pieces = []
    for f in spec['unit']['functions']:
        match = next((defined[n] for n in f.get('candidates',[f['symbol']])+['func_%08X'%f['addr']] if n in defined),None)
        if match:
            index, symbol = match
            pieces.append(dict(start=symbol['value'],symbol=index,name='.text.'+symbol['name'],address=f['addr']))
    pieces.sort(key=lambda p:p['start'])
    if not pieces or pieces[0]['start']!=0 or len({p['start'] for p in pieces})!=len(pieces):
        raise ValueError('unsectioned text does not have unique owned function starts')
    for i,piece in enumerate(pieces):
        piece['end'] = pieces[i+1]['start'] if i+1<len(pieces) else text['size']
        piece['index'] = len(elf.sections)+i
    def owner(value):
        return next((p for p in reversed(pieces) if p['start']<=value),None)
    out=bytearray(data)
    table=elf.section('.symtab')
    split_relocs={p['index']:[] for p in pieces}
    for r in elf.sections:
        if r['type']!=9 or r['link']!=table['index']:
            continue
        target=elf.sections[r['info']]
        for offset in range(r['offset'],r['offset']+r['size'],8):
            at,info=struct.unpack_from('<II',out,offset)
            symbol=syms[info>>8];kind=info&255
            if symbol['type']==3 and symbol['shndx']==text['index']:
                word=struct.unpack_from('<I',out,target['offset']+at)[0]
                if kind==2:
                    value=word
                elif kind==4:
                    value=(word&0x3ffffff)<<2
                else:
                    raise ValueError('unsupported relocation to unsectioned text: '+str(kind))
                piece=owner(value)
                if piece is None or value>text['size']:
                    raise ValueError('unsectioned text addend outside input')
                delta=value-piece['start']
                word=delta if kind==2 else (word&0xfc000000)|(delta>>2)
                struct.pack_into('<I',out,target['offset']+at,word)
                info=piece['symbol']<<8|kind
                struct.pack_into('<I',out,offset+4,info)
            if target['index']==text['index']:
                piece=owner(at)
                split_relocs[piece['index']].append((at-piece['start'],info))
    for i,symbol in enumerate(syms):
        if symbol['shndx']!=text['index'] or symbol['type']==3:
            continue
        piece=owner(symbol['value'])
        struct.pack_into('<I',out,table['offset']+i*16+4,symbol['value']-piece['start'])
        struct.pack_into('<H',out,table['offset']+i*16+14,piece['index'])
    headers=[list(struct.unpack_from('<10I',out,elf.shoff+i*elf.shentsize)) for i in range(elf.shnum)]
    headers[text['index']][2]=0
    headers[text['index']][5]=0
    for section in elf.sections:
        if section['type']==9 and section['info']==text['index']:
            headers[section['index']][5]=0
    strings=bytearray(elf.content(elf.sections[elf.shstrndx]))
    def append(name,payload,kind,flags,link,info,alignment,entry_size=0):
        name_offset=len(strings);strings.extend(name.encode()+b'\0')
        out.extend(bytes((-len(out))%4));offset=len(out);out.extend(payload)
        headers.append([name_offset,kind,flags,0,offset,len(payload),link,info,alignment,entry_size])
    for piece in pieces:
        append(piece['name'],out[text['offset']+piece['start']:text['offset']+piece['end']],1,text['flags'],0,0,
               min(text['align'],piece['address']&-piece['address']))
    for piece in pieces:
        entries=split_relocs[piece['index']]
        if entries:
            append('.rel'+piece['name'],b''.join(struct.pack('<II',*p) for p in entries),9,0,table['index'],piece['index'],4,8)
    out.extend(bytes((-len(out))%4));offset=len(out);out.extend(strings)
    headers[elf.shstrndx][4:6]=[offset,len(strings)]
    out.extend(bytes((-len(out))%4));offset=len(out)
    out.extend(b''.join(struct.pack('<10I',*h) for h in headers))
    struct.pack_into('<I',out,32,offset)
    struct.pack_into('<H',out,48,len(headers))
    return bytes(out)


def undefine_dropped(data, keep):
    """Make the global symbols defined in sections the link will not place undefined, so that they resolve to the
    original definitions elsewhere in the image (vtables, unwind data and other duplicates a compiled unit emits).
    Kept absolute pointers to a dropped function's entry use its existing global
    symbol instead of a local section symbol. Interior or ambiguous references
    remain unresolved. `keep` names linked sections; only allocated inputs drop.
    """
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
        symbols = [struct.unpack_from('<IIIBBH', data, h[4] + k * 16)
                   for k in range(h[5] // 16)]
        entries = {}
        for k, (symbol_name, value, size, info, _, shndx) in enumerate(symbols):
            if symbol_name and shndx in dropped and info >> 4 in (1, 2) and info & 15 == 2 and size:
                entries.setdefault((shndx, value), []).append(k)
        for rel in hdrs:
            if rel[1] != 9 or rel[6] != i or name(rel[7]) not in keep:
                continue
            target = hdrs[rel[7]]
            if target[1] != 1:
                continue
            for offset in range(rel[4], rel[4] + rel[5], 8):
                at, info = struct.unpack_from('<II', data, offset)
                if info & 255 != 2 or at + 4 > target[5]:  # R_MIPS_32, backed by bytes
                    continue
                symbol = symbols[info >> 8]
                if symbol[3] >> 4 != 0 or symbol[3] & 15 != 3 or symbol[5] not in dropped:  # local STT_SECTION
                    continue
                addend, = struct.unpack_from('<I', data, target[4] + at)
                entry = symbol[1] + addend
                candidates = entries.get((symbol[5], entry), [])
                if len(candidates) != 1:
                    continue
                # The same entry address is now global_function + zero. This
                # permits native FDEs for assembly-backed context functions.
                struct.pack_into('<I', out, offset + 4, candidates[0] << 8 | 2)
                struct.pack_into('<I', out, target[4] + at, 0)
        for k in range(h[5] // 16):
            o = h[4] + k * 16
            n, value, size, info, other, shndx = struct.unpack_from('<IIIBBH', data, o)
            if shndx in dropped and (info >> 4) != 0:
                struct.pack_into('<IIIBBH', out, o, n, 0, 0, 0x10 | (info & 0xF), other, 0)   # global: weak undefined would link as 0
                count += 1
    return bytes(out), count


def unplaced_allocated_sections(data, keep):
    """Move unplaced allocated inputs to the linker's explicit discard namespace.

    Undefining a context function's symbol alone leaves its bytes allocated.
    Rename its section so the linker discards those bytes instead of treating
    them as an orphan input.
    """
    shoff, = struct.unpack_from('<I', data, 32)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 46)
    headers = [struct.unpack_from('<IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    strings = data[headers[shstrndx][4]:headers[shstrndx][4] + headers[shstrndx][5]]
    names = [strings[h[0]:].split(b'\0', 1)[0].decode() for h in headers]
    return {name: '.discard.source.%d' % i for i, (name, h) in enumerate(zip(names, headers))
            if i and h[2] & 2 and name not in keep}


def trim_sections(data, sizes):
    """Shorten sections (name -> new size). Used to drop the alignment padding the assembler appends to the end of a
    constants section when the original continues straight away; only zero bytes may be removed (checked by the caller)."""
    shoff, = struct.unpack_from('<I', data, 32)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 46)
    out = bytearray(data)
    hdrs = [struct.unpack_from('<IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    names = data[hdrs[shstrndx][4]:hdrs[shstrndx][4] + hdrs[shstrndx][5]]
    for i, h in enumerate(hdrs):
        name = names[h[0]:].split(b'\0', 1)[0].decode()
        if name in sizes and sizes[name] < h[5]:
            struct.pack_into('<I', out, shoff + i * shentsize + 20, sizes[name])
    return bytes(out)


def copy_header_flags(data, template):
    """The object bytes with the ELF header flags (e_flags, which hold the MIPS ABI) of the template object. The EE assembler
    leaves the ABI field empty while the compiler sets EABI64, and objdiff names the registers $8..$11 after it (t0..t3 or
    a4..a7), so an instruction with a relocation that uses one of them would differ by the register name alone."""
    out = bytearray(data)
    out[0x24:0x28] = template[0x24:0x28]
    return bytes(out)


def literal_as_gprel(data):
    """The object bytes with R_MIPS_LITERAL relocations (how the compiler addresses .lit4/.lit8 constants from $gp) retyped
    as R_MIPS_GPREL16, the way the split assembly writes them (`%gp_rel(D_...)($gp)`). The linker resolves both the same;
    objdiff compares the types."""
    out = bytearray(data)
    shoff, = struct.unpack_from('<I', out, 0x20)
    entsize, count = struct.unpack_from('<HH', out, 0x2E)
    for i in range(count):
        header = shoff + i * entsize
        kind, = struct.unpack_from('<I', out, header + 4)
        offset, size = struct.unpack_from('<II', out, header + 16)
        if kind != 9:                                  # SHT_REL
            continue
        for at in range(offset, offset + size, 8):
            info, = struct.unpack_from('<I', out, at + 4)
            if info & 0xFF == 8:                       # R_MIPS_LITERAL
                struct.pack_into('<I', out, at + 4, (info & ~0xFF) | 7)
    return bytes(out)
