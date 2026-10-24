#!/usr/bin/env python3
"""Write include/types_ghidra.h: the data types and function signatures of the Ghidra program /SLUS_213.76 as C, for the
m2c context and for the compile context of the automatically drafted sources.

Read-only with respect to Ghidra. Inputs, in .local/ghidra/ (ignored; same convention as tools/ghidra_export.py):
  structures_N.json   {"structures": [get-structure-info responses: name, size, fields[fieldName, offset, dataType, length]]}
                      one call of `get-structure-info` per structure listed by `list-structures` (programPath /SLUS_213.76)
  config/symbols.txt  (written by tools/ghidra_export.py) for the signatures of the named functions.
Enums, typedefs and unions: the program has none beyond the ELF header types, which are not exported.

Ghidra's types are recovered guesses. Every structure is marked as such in the header, and the mark changes to "used by N
matching functions" once a matched function actually accesses members through that structure type: a layout is trusted only when a function using it matches. Offsets and sizes are asserted at compile time.
Usage: ghidra_types.py [--pages DIR]
"""
import argparse, json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(Path(__file__).resolve().parent))

SCALARS = {'uchar': 'u8', 'char': 'char', 'byte': 'u8', 'short': 's16', 'ushort': 'u16', 'word': 'u16', 'int': 's32',
           'uint': 'u32', 'dword': 'u32', 'long': 's64', 'ulong': 'u64', 'longlong': 's64', 'ulonglong': 'u64',
           'float': 'f32', 'double': 'f64', 'bool': 'u8', 'void': 'void', 'undefined': 'u8', 'undefined1': 'u8',
           'undefined2': 'u16', 'undefined4': 'u32', 'undefined8': 'u64', 'qword': 'u64'}


def ctype(t, structs):
    """(prefix, suffix) of a declaration of Ghidra type `t`: `prefix name suffix`."""
    t = t.strip()
    dims = ''
    while True:
        m = re.match(r'^(.*)\[(\d+)\]$', t)
        if not m:
            break
        t, dims = m.group(1).strip(), dims + '[%s]' % m.group(2)
    # arrays of pointers and multi-dimensional arrays list their dimensions innermost first
    stars = 0
    while t.endswith('*'):
        t = t[:-1].strip()
        stars += 1
    if t in structs:
        base = t
    elif t in SCALARS:
        base = SCALARS[t]
    else:
        raise ValueError('unknown Ghidra type ' + t)
    return base + (' ' + '*' * stars if stars else ''), dims


def order(structs):
    """Dependency order: a structure embedded by value is defined before the one that contains it."""
    out, seen = [], set()

    def visit(n):
        if n in seen:
            return
        seen.add(n)
        for f in structs[n]['fields']:
            t = re.sub(r'\[\d+\]', '', f['dataType']).strip()
            if '*' not in t and t in structs:
                visit(t)
        out.append(n)
    for n in sorted(structs):
        visit(n)
    return out


def users(names):
    """Count matched functions with actual member accesses through this exact type.

    Merely including a header or mentioning a type elsewhere in a TU cannot verify
    its layout. Conservative omissions remain UNVERIFIED until their use is explicit.
    """
    from context_recovery import source_seeds
    from units import dependencies
    count = {n: 0 for n in names}
    seeds, _ = source_seeds()
    for addr, seed in seeds.items():
        if not seed.get('matched') or not seed.get('body') or seed['source'] == 'ghidra':
            continue
        if not any(str(p) == 'include/types_ghidra.h' for p in dependencies(seed['source'])):
            continue
        text = seed['raw'] + ' ' + seed['body']
        for name in names:
            variables = re.findall(r'\b' + re.escape(name) + r'\s*\*\s*(\w+)', text)
            direct = any(re.search(r'\b' + re.escape(v) + r'\s*->\s*\w+', seed['body']) for v in variables)
            cast = re.search(r'\(\s*\(\s*' + re.escape(name) + r'\s*\*\s*\)[^;]+?\)\s*->', seed['body'])
            if direct or cast:
                count[name] += 1
    return count


def signatures():
    out = []
    for line in (ROOT / 'config/symbols.txt').read_text().split('\n'):
        c = line.split('\t')
        if len(c) < 6 or c[2] != 'func' or c[5] == '-' or c[0] == '0x00100008' or 'thunk_' in c[5]:
            continue
        m = re.match(r'^(.*?)\s*(?:__stdcall|__cdecl|__thiscall|__fastcall)?\s*([\w:~]+)\((.*)\)$', c[5])
        if not m:
            continue
        out.append((int(c[0], 16), m.group(2), m.group(1).strip(), m.group(3).strip()))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--pages', default=str(ROOT / '.local/ghidra'))
    a = ap.parse_args()
    structs = {}
    for p in sorted(Path(a.pages).glob('structures_*.json')):
        for s in json.loads(p.read_text())['structures']:
            structs[s['name']] = s
    if not structs:
        raise SystemExit('no structures_*.json pages in ' + a.pages)
    used = users(list(structs))
    lines = ['/* Generated by tools/ghidra_types.py from the Ghidra program /SLUS_213.76; do not edit.',
             ' *',
             ' * Ghidra\'s types are recovered guesses, not facts. A structure is trusted only once a function using it matches',
             ' * (see the "used by" mark on each). Offsets and sizes are asserted below. Names are Ghidra\'s, not the original\'s. */',
             '#ifndef TYPES_GHIDRA_H', '#define TYPES_GHIDRA_H', '#include "ps2/prelude.h"', '']
    for n in sorted(structs):
        lines.append('typedef struct %s %s;' % (n, n))
    lines.append('')
    asserts = []
    for n in order(structs):
        s = structs[n]
        lines.append('/* %s, %d bytes: %s */' % (n, s['size'], 'UNVERIFIED Ghidra guess' if not used[n] else
                                                  'used by %d matching functions' % used[n]))
        lines.append('struct %s {' % n)
        for f in s['fields']:
            pre, dims = ctype(f['dataType'], structs)
            lines.append('    %s%s%s; /* 0x%X */' % (pre if pre.endswith('*') else pre + ' ', f['fieldName'], dims, f['offset']))
            asserts.append('typedef char assert_%s_%s[(((int) &((%s *) 0)->%s) == %d) ? 1 : -1];' % (
                n, f['fieldName'], n, f['fieldName'], f['offset']))
        lines.append('};')
        asserts.append('typedef char assert_%s_size[(sizeof(%s) == %d) ? 1 : -1];' % (n, n, s['size']))
        lines.append('')
    lines.append('/* Function signatures of the named functions (Ghidra names in the comments; the symbols are the image\'s). */')
    lines.append('#ifndef TYPES_GHIDRA_NO_PROTOTYPES')
    nsig = 0
    for addr, name, ret, params in signatures():
        try:
            r = ctype(ret, structs) if ret != 'undefined' else ('void', '')
            if r[1]:
                continue
            ps = []
            if params not in ('', 'void'):
                for p in params.split(','):
                    p = p.strip()
                    m = re.match(r'^(.*?)\s*\b(\w+)$', p)
                    if not m:
                        raise ValueError(p)
                    pre, dims = ctype(m.group(1), structs)
                    ps.append(pre.strip() + (' *' if dims else ''))
            lines.append('extern %s func_%08X(%s); /* %s */' % (r[0].strip(), addr, ', '.join(ps) or 'void', name))
            nsig += 1
        except (ValueError, KeyError):
            continue
    lines += ['#endif', '', '/* Compile-time checks of the recovered layouts. */'] + asserts + ['', '#endif', '']
    (ROOT / 'include/types_ghidra.h').write_text('\n'.join(lines))
    print('include/types_ghidra.h: %d structures, %d signatures' % (len(structs), nsig))


if __name__ == '__main__':
    main()
