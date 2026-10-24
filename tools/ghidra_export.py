#!/usr/bin/env python3
"""Export the names Ghidra knows for /SLUS_213.76 into config/symbols.txt, and reconcile Ghidra with splat.

Read-only with respect to Ghidra. The input is a directory of raw tool pages (default .local/ghidra/, ignored),
produced by these Ghidra MCP calls against the program `/SLUS_213.76` (each saves a JSON page; repeat with
`startIndex` until `nextStartIndex` reaches the total):
  functions_N.json       get-functions  filterDefaultNames=false maxCount=3000   (address, size, name, tags)
  functions_named.json   get-functions  filterDefaultNames=true  verbose=true    (adds signature and return type)
  symbols_N.json         get-symbols    filterDefaultNames=true  maxCount=3200   (labels and function symbols)
Anything else that writes the same JSON (for example a headless script) works too.

config/symbols.txt has one line per symbol, tab separated:
  ADDRESS  SIZE  KIND  SYMBOL  ALIAS  PROTOTYPE
  KIND     func or data. SIZE is the Ghidra size in bytes (`-` if unknown, for example data labels).
  SYMBOL   the link-time name of the assembly: func_XXXXXXXX, or D_XXXXXXXX for data. Functions provided by source
           (compiled from source, tools/units.py) carry the exact compiler-emitted mangled name instead.
  ALIAS    Ghidra's name where it is a recovered one (not FUN_/DAT_/PTR_/LAB_/... defaults); `-` otherwise. These are
           readable aliases, not original symbols.
  PROTOTYPE  Ghidra's signature where one was set, else `-`.

Reconciliation with splat's function list (build/<GAME_ID>/placement.json) is written to build/<GAME_ID>/ghidra_reconcile.json
and summarised on stdout.
Usage: ghidra_export.py [--pages DIR] [--slug SLUS_213.76]
"""
import argparse, bisect, json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_NAME = re.compile(r'^(FUN_|thunk_FUN_|DAT_|PTR_|LAB_|SUB_|UNK_|caseD_|switchD|s_|u_|BYTE_|WORD_|DWORD_|'
                          r'PTR_FUN_|DAT_|JMP_|LAB|_DAT_|[a-z]{2,4}_[0-9a-f]{8}$)')
ADDR = re.compile(r'0x([0-9a-fA-F]+)')


def pages(directory, prefix):
    out = []
    for p in sorted(Path(directory).glob(prefix + '_*.json')):
        out.append(json.loads(p.read_text()))
    return out


def meaningful(name):
    return bool(name) and not DEFAULT_NAME.match(name)


def load(directory):
    funcs = {}
    for page in pages(directory, 'functions'):
        for f in page['functions']:
            funcs[int(f['address'], 16)] = dict(size=f['sizeInBytes'], name=f['name'], thunk=f.get('isThunk', False))
    named = Path(directory) / 'functions_named.json'
    protos = {}
    if named.exists():
        for f in json.loads(named.read_text())['functions']:
            protos[int(f['address'], 16)] = f.get('signature')
    labels = {}
    for page in pages(directory, 'symbols'):
        for s in page['symbols']:
            a = int(s['address'], 16)
            if s['symbolType'] == 'Function' or s['namespace'] != 'Global':
                continue
            if meaningful(s['name']):
                labels.setdefault(a, s['name'])
    return funcs, protos, labels


def splat_functions(slug):
    pl = json.loads((ROOT / 'build' / slug / 'placement.json').read_text())
    return pl['functions']


def zero_function(slug, f):
    text = (ROOT / 'asm' / slug / 'nonmatchings' / (f['obj'].split('/')[-1] + '.s')).read_text()
    words = re.findall(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/', text)
    return bool(words) and all(w == '00000000' for w in words)


def function_words(slug, f):
    text = (ROOT / 'asm' / slug / 'nonmatchings' / (f['obj'].split('/')[-1] + '.s')).read_text()
    return [int(w, 16) for w in re.findall(r'/\* [0-9A-F]+ [0-9A-F]{8} ([0-9A-F]{8}) \*/', text)]


def ends_with_return(words):
    """True if the last non-zero words contain an unconditional jump away (jr, j, b) or a return."""
    tail = [w for w in words if w][-3:]
    for w in tail:
        op = int.from_bytes(w.to_bytes(4, 'big'), 'little') if False else w
    # words in the files are little-endian instruction words written as byte-swapped hex: 0800E003 == 03E00008
    def decode(w):
        return int.from_bytes(w.to_bytes(4, 'big'), 'little')
    for w in map(decode, tail):
        if w == 0x03E00008 or (w >> 26) == 2 or (w & 0xFFFF0000) == 0x10000000 or (w & 0xFC1FFFFF) == 0x00000008:
            return True
    return False


def orphan_piece(le_words):
    """`<non-branch instruction>; nop` pieces (the words here are byte-swapped hex, see ends_with_return)."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from boundaries import control
    dec = [int.from_bytes(w.to_bytes(4, 'big'), 'little') for w in le_words]
    return bool(dec) and all((w == 0) if i % 2 else (w != 0 and not control(w)) for i, w in enumerate(dec))


def reconcile(slug, ghidra):
    sf = splat_functions(slug)
    jal_targets = set()
    text = (ROOT / 'asm' / slug / 'text.s').read_text()
    for m in re.finditer(r'\bjal\s+func_([0-9A-F]{8})', text):
        jal_targets.add(int(m.group(1), 16))
    data_refs = set()
    for p in sorted((ROOT / 'asm' / slug / 'data').glob('*.s')):
        data_refs.update(int(m.group(1), 16) for m in re.finditer(r'\bfunc_([0-9A-F]{8})\b', p.read_text()))
    addr_loads = {int(m.group(1), 16) for m in re.finditer(r'%(?:hi|lo)\(func_([0-9A-F]{8})', text)}
    starts = [f['addr'] for f in sf]
    sset = set(starts)
    gaddrs = sorted(ghidra)
    gset = set(gaddrs)
    res = dict(splat=len(sf), ghidra=len(ghidra), agree=0, splat_only={}, ghidra_only={}, size_equal=0, size_differs=0)
    examples = {}

    def covered_by_ghidra(a):
        i = bisect.bisect_right(gaddrs, a) - 1
        return i >= 0 and gaddrs[i] < a < gaddrs[i] + max(ghidra[gaddrs[i]]['size'], 1)

    for f in sf:
        a = f['addr']
        if a in gset:
            res['agree'] += 1
            end = f['end']
            # Ghidra's size excludes trailing alignment; compare to splat's span up to its last non-padding word
            if ghidra[a]['size'] <= f['end'] - a and f['end'] - a - ghidra[a]['size'] < 8:
                res['size_equal'] += 1
            else:
                res['size_differs'] += 1
            continue
        if zero_function(slug, f):
            kind = 'padding (all-zero words)'
        elif orphan_piece(function_words(slug, f)):
            kind = 'orphan piece (instruction + nop between functions, tools/boundaries.py)'
        elif covered_by_ghidra(a):
            kind = 'splat splits inside a Ghidra function'
        else:
            prev = sf[sf.index(f) - 1] if f is not sf[0] else None
            if a in jal_targets:
                kind = 'Ghidra has no function here: called (jal) - missed function'
            elif prev is not None and not orphan_piece(function_words(slug, prev)) and not ends_with_return(function_words(slug, prev)):
                kind = 'Ghidra has no function here: previous function falls through - over-split'
            elif a in data_refs:
                kind = 'Ghidra has no function here: address stored in data (vtable or callback table) - missed function'
            elif a in addr_loads:
                kind = 'Ghidra has no function here: address built with lui/addiu - missed function'
            else:
                kind = 'Ghidra has no function here: unreferenced, follows a return - stub or fragment'
        res['splat_only'][kind] = res['splat_only'].get(kind, 0) + 1
        examples.setdefault('splat_only: ' + kind, []).append('%08X' % a)
    for a in gaddrs:
        if a in sset:
            continue
        i = bisect.bisect_right(starts, a) - 1
        if i >= 0 and sf[i]['addr'] < a < sf[i]['end']:
            kind = 'inside a splat function (Ghidra splits it or has a thunk/entry)' + (' - thunk' if ghidra[a]['thunk'] else '')
        else:
            kind = 'outside splat functions (data or padding region)'
        res['ghidra_only'][kind] = res['ghidra_only'].get(kind, 0) + 1
        examples.setdefault('ghidra_only: ' + kind, []).append('%08X' % a)
    res['examples'] = {k: v[:8] for k, v in examples.items()}
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--pages', default=str(ROOT / '.local/ghidra'))
    ap.add_argument('--slug', default='SLUS_213.76')
    a = ap.parse_args()
    funcs, protos, labels = load(a.pages)
    # source-provided functions carry their mangled name
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from units import load_units
    mangled = {f['addr']: f['symbol'] for u in load_units() for f in u['functions']
               if f.get('status') == 'source' and f.get('symbol')}
    rows = []
    for addr in sorted(funcs):
        f = funcs[addr]
        alias = f['name'] if meaningful(f['name']) else '-'
        rows.append((addr, f['size'], 'func', mangled.get(addr, 'func_%08X' % addr), alias, protos.get(addr) or '-'))
    for addr in sorted(labels):
        if addr in funcs:
            continue
        rows.append((addr, '-', 'data', 'D_%08X' % addr, labels[addr], '-'))
    rows.sort(key=lambda r: (r[0], r[2]))
    with open(ROOT / 'config/symbols.txt', 'w') as out:
        out.write('# Generated by tools/ghidra_export.py from the Ghidra program /SLUS_213.76; do not edit.\n')
        out.write('# ADDRESS\tSIZE\tKIND\tSYMBOL\tALIAS\tPROTOTYPE   (aliases are Ghidra names, not original symbols)\n')
        for addr, size, kind, sym, alias, proto in rows:
            out.write('0x%08X\t%s\t%s\t%s\t%s\t%s\n' % (addr, size if size == '-' else '0x%X' % size, kind, sym, alias, proto))
    named = sum(1 for r in rows if r[2] == 'func' and r[4] != '-')
    print('config/symbols.txt: %d functions (%d with a recovered Ghidra name, %d with prototypes), %d data labels' % (
        sum(1 for r in rows if r[2] == 'func'), named, sum(1 for r in rows if r[2] == 'func' and r[5] != '-'),
        sum(1 for r in rows if r[2] == 'data')))
    if (ROOT / 'build' / a.slug / 'placement.json').exists():
        res = reconcile(a.slug, funcs)
        (ROOT / 'build' / a.slug / 'ghidra_reconcile.json').write_text(json.dumps(res, indent=1))
        print('splat %d functions, Ghidra %d: %d start at the same address' % (res['splat'], res['ghidra'], res['agree']))
        print('  agreeing starts with equal extent: %d, different: %d' % (res['size_equal'], res['size_differs']))
        for k, v in res['splat_only'].items():
            print('  splat only: %5d  %s' % (v, k))
        for k, v in res['ghidra_only'].items():
            print('  Ghidra only: %5d  %s' % (v, k))


if __name__ == '__main__':
    main()
