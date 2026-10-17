#!/usr/bin/env python3
"""Dump symbols and debug data from every ELF kept under orig/ and estimate transfer to USA retail.

For each ELF with .symtab, .mdebug or DWARF1/2 sections this writes, under .local/inputs/symbols/<slug>/:
functions (address, size), objects, source files, a line-table summary and the compiler banner. The
transfer estimate looks for each symbol-bearing function body inside the retail .text using
address-masked instruction windows (meaningful only for code built for the same CPU).

Usage: symbols.py [--summary-json PATH]
"""
import argparse, hashlib, json, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from elfinfo import Elf
from inputs import mask_text

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / '.local/inputs/symbols'
MACHINE = {8: 'MIPS'}


def cstrings(b, suffixes=('.c', '.cpp', '.cc', '.h', '.s', '.asm')):
    out, cur = [], bytearray()
    for c in b:
        if 32 <= c < 127:
            cur.append(c)
        else:
            if len(cur) >= 4 and bytes(cur).lower().endswith(tuple(x.encode() for x in suffixes)):
                out.append(cur.decode())
            cur = bytearray()
    return out


def dump(slug, path, retail_index):
    e = Elf(path.read_bytes())
    names = {s['name'] for s in e.sections}
    has_sym = '.symtab' in names and e.section('.symtab')['size'] > 16
    debug = [n for n in names if n.startswith(('.debug', '.line', '.stab', '.mdebug'))
             and e.section(n)['size'] > 1]
    if not has_sym and not debug:
        return None
    rec = dict(slug=slug, file=str(path.relative_to(ROOT / 'orig' / slug / 'files')),
               machine=e.machine, debug_sections={n: e.section(n)['size'] for n in sorted(debug)})
    comment = e.section('.comment')
    if comment:
        rec['comment'] = [x for x in e.content(comment).decode('latin1').split('\0') if x]
    syms = e.symbols() if has_sym else []
    funcs = [s for s in syms if s['type'] == 2]
    objs = [s for s in syms if s['type'] == 1]
    rec.update(functions=len(funcs), objects=len(objs), file_symbols=sum(s['type'] == 4 for s in syms),
               undefined=sum(s['shndx'] == 0 and s['name'] != '' for s in syms))
    sources = []
    for n in ('.debug', '.debug_str', '.debug_info', '.mdebug'):
        s = e.section(n)
        if s and s['size'] > 1:
            sources += cstrings(e.content(s))
    rec['source_files'] = sorted(set(sources))
    if e.section('.debug'):
        rec['type_info'] = 'DWARF 1 (.debug entries: types, variables, function scopes)'
    if e.section('.line'):
        rec['line_table'] = dict(section_bytes=e.section('.line')['size'],
                                 approx_entries=(e.section('.line')['size'] - 8) // 10, format='DWARF 1 .line')
    d = OUT / slug / rec['file'].replace('/', '_')
    d.parent.mkdir(parents=True, exist_ok=True)
    text = e.section('.text')
    lines = ['# functions: address size name'] + [f"{s['value']:08x} {s['size']:6d} {s['name']}" for s in
                                                 sorted(funcs, key=lambda s: s['value'])]
    lines += ['# objects: address size name'] + [f"{s['value']:08x} {s['size']:6d} {s['name']}" for s in
                                                 sorted(objs, key=lambda s: s['value'])]
    lines += ['# source files'] + rec['source_files']
    d.with_suffix('.symbols.txt').write_text('\n'.join(lines) + '\n')
    hits = 0
    if funcs and text and e.machine in retail_index['machines']:
        words = list(struct.unpack('<%dI' % (text['size'] // 4), e.content(text)))
        sm, _ = mask_text(words)
        for s in funcs:
            lo = (s['value'] - text['addr']) // 4
            body = sm[lo:lo + s['size'] // 4]
            if len(body) >= 6 and hash(tuple(body[:6])) in retail_index['heads']:
                hits += 1
    rec['functions_found_in_retail'] = hits
    return rec


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--summary-json', type=Path, default=ROOT / '.local/inputs/symbols-summary.json')
    a = ap.parse_args()
    retail = Elf((ROOT / 'orig/usa-retail/files/SLUS_213.76').read_bytes())
    t = retail.section('.text')
    words = list(struct.unpack('<%dI' % (t['size'] // 4), retail.content(t)))
    sm, _ = mask_text(words)
    heads = {hash(tuple(sm[i:i + 6])) for i in range(len(sm) - 6)}
    index = dict(heads=heads, machines={retail.machine})
    recs, seen = [], set()
    for p in sorted((ROOT / 'orig').glob('*/files/**/*')):
        if not p.is_file() or p.read_bytes()[:4] != b'\x7fELF':
            continue
        slug = p.relative_to(ROOT / 'orig').parts[0]
        digest = hashlib.sha256(p.read_bytes()).hexdigest()
        if digest in seen:
            continue
        seen.add(digest)
        r = dump(slug, p, index)
        if r:
            r['sha256'] = digest
            recs.append(r)
    a.summary_json.parent.mkdir(parents=True, exist_ok=True)
    a.summary_json.write_text(json.dumps(recs, indent=1) + '\n')
    for r in recs:
        print(r['slug'], r['file'], 'funcs', r['functions'], 'objs', r['objects'], r['debug_sections'],
              r.get('comment'), 'found in retail:', r['functions_found_in_retail'])
    if not recs:
        print('No symbol or debug data in any ELF.')


if __name__ == '__main__':
    main()
