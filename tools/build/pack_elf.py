#!/usr/bin/env python3
"""Write the final boot executable: GNU ld's linked sections inside the container the retail tools produced.

GNU ld cannot produce the retail container (section header order, non-loaded SN/DVP sections, `.reginfo`,
e_flags 0x20924001), so ld output is used for what it is good at, laying out and relocating the loaded sections
(`.text` ... `.bss`), and this step re-packs them from committed configuration:
  * config/<GAME_ID>/layout.json: ELF header fields, program header and one record per section (no game bytes);
  * the extracted opaque payloads in data/<GAME_ID>/elf (DVP overlays and their tables; ignored, like .vutext);
  * `_gp` from the linked image for `.reginfo`; `.shstrtab` is regenerated from the section names;
  * `.DVP.ovlytab` addresses that point into `.vutext` are rebased if `.vutext` moved.
Section addresses and sizes of the loaded sections come from the linked image, file offsets from the usual
rule (offset - 0x1000 == address - base inside the segment, other sections packed by alignment).

Usage: pack_elf.py LINKED.elf LAYOUT.json BLOB_DIR OUT.elf
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, struct, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf


def align(x, a):
    return (x + a - 1) // a * a if a > 1 else x


def pack(linked, layout, blobdir):
    L = Elf(linked)
    lsec = {s['name']: s for s in L.sections if s['index']}
    gp = next((s['value'] for s in L.symbols() if s['name'] == '_gp'), 0)
    hdr, seg, recs = layout['header'], layout['segment'], layout['sections']
    base = seg['vaddr']
    # 1. contents and addresses
    secs, prev_end = [], base
    for r in recs:
        s = dict(r)
        src = r['source']
        if src == 'linked':
            ls = lsec.get(r['name'])
            if ls:
                s['addr'], s['size'] = ls['addr'], ls['size']
                s['data'] = L.content(ls) if r['type'] != 8 else b''
            else:  # empty section the linker dropped: sits at the end of the previous loaded section
                s['addr'], s['size'], s['data'] = prev_end, 0, b''
            prev_end = s['addr'] + s['size']
        elif src == 'reginfo':
            ri = r['reginfo']
            s['data'] = struct.pack('<I4II', ri['gprmask'], *ri['cprmask'], gp)
        elif src == 'zero':
            s['data'] = bytes(r['size'])
        elif src == 'blob':
            s['data'] = (Path(blobdir) / Path(r['blob']).name).read_bytes()
            if 'rebase' in r:
                rb = r['rebase']
                old = rb['base_addr']
                new = lsec[rb['base_section']]['addr']
                d = bytearray(s['data'])
                for o in range(rb['field'], len(d), rb['stride']):
                    v, = struct.unpack_from('<I', d, o)
                    if old <= v < old + rb['size']:
                        struct.pack_into('<I', d, o, v - old + new)
                s['data'] = bytes(d)
        if src != 'linked':
            s.setdefault('data', b'')
            s.setdefault('addr', r['addr'])
            s['size'] = len(s['data'])
        secs.append(s)
    # 2. generated string table
    names = bytearray(b'\0')
    for s in secs:
        s['name_off'] = len(names)
        names += s['name'].encode() + b'\0'
    for s in secs:
        if s['source'] == 'shstrtab':
            s['data'] = bytes(names)
            s['size'] = len(names)
    # 3. file offsets
    loaded = [s for s in secs if s['source'] == 'linked']
    seg_off = seg['offset']
    filesz = max(s['addr'] + s['size'] for s in loaded if s['type'] != 8) - base
    memsz = max(s['addr'] + s['size'] for s in loaded) - base
    cursor = seg_off + filesz
    for s in secs:
        if s['source'] == 'linked':
            s['offset'] = seg_off + s['addr'] - base
        else:
            cursor = align(cursor, s['align'])
            s['offset'] = cursor
            cursor += s['size']
    shoff = align(cursor, 4)
    out = bytearray(shoff + 40 * (len(secs) + 1))
    # 4. headers
    ident = bytes.fromhex(hdr['ident'])
    struct.pack_into('<16sHHIIIIIHHHHHH', out, 0, ident, hdr['type'], hdr['machine'], 1, hdr['entry'], hdr['phoff'],
                     shoff, hdr['flags'], 52, hdr['phentsize'], hdr['phnum'], hdr['shentsize'], len(secs) + 1,
                     len(secs))
    struct.pack_into('<IIIIIIII', out, hdr['phoff'], seg['type'], seg_off, base, base, filesz, memsz, seg['flags'],
                     seg['align'])
    for i, s in enumerate(secs, 1):
        if s['type'] != 8:
            out[s['offset']:s['offset'] + s['size']] = s['data']
        struct.pack_into('<IIIIIIIIII', out, shoff + 40 * i, s['name_off'], s['type'], s['flags'], s['addr'],
                         s['offset'], s['size'], s['link'], s['info'], s['align'], s['entsize'])
    return bytes(out)


def main():
    linked, layout, blobs, dest = sys.argv[1:5]
    data = pack(Path(linked).read_bytes(), json.loads(Path(layout).read_text()), blobs)
    Path(dest).write_bytes(data)
    import hashlib
    print('%s: %d bytes sha256 %s' % (dest, len(data), hashlib.sha256(data).hexdigest()))


if __name__ == '__main__':
    main()
