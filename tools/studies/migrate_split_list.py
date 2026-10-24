#!/usr/bin/env python3
"""One-time migration, stage 2: config/units.yaml -> split list, symbol table and equivalent-tier file.

  migrate_split_list.py write     read config/units.yaml (written by migrate_include_asm.py) and write
                                    config/SLUS_213.76/splits.yaml     one entry per source file/range, flags, assembler variant
                                    config/SLUS_213.76/symbols.txt     mangled definition names and extern bindings
                                    config/SLUS_213.76/equivalent.yaml functions of the equivalent evidence tier
  migrate_split_list.py check     derive the units back with tools/build/units.py and compare them with config/units.yaml

The function statuses are not written: they come from the INCLUDE_ASM markers of the source files. Extern bindings come from the
units' `externs` and from the optional legacy `.local/import/*_bindings.json`; a name bound to two addresses stays in the split
that needs it (`externs:`). Facts that settlement computed (`trim`, resolved externs) are rebuilt by the build into build/.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import glob, json, sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import splits as S

SLUG = 'SLUS_213.76'
CFG = ROOT / 'config' / SLUG
HEADER = ('# Source splits of SLUS_213.76: one entry per source file and address range (docs/build.md). Edit by hand.\n'
          '# range is [start, end); every function of the range is compiled from the file unless the file marks it\n'
          '# INCLUDE_ASM. `functions` lists the compiled addresses of files that carry no markers.\n')


def num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


def load():
    doc = yaml.safe_load((ROOT / 'config/units.yaml').read_text())
    units = doc['units']
    for u in units:
        for f in u['functions']:
            f['addr'] = num(f['addr'])
    return units


def split_entry(u, ends):
    flags = [f for f in u['flags'] if f != '-ffunction-sections' and not f.startswith('--assembler=')]
    assembler = next((f.split('=', 1)[1] for f in u['flags'] if f.startswith('--assembler=')), None)
    if 'range' in u:
        lo, hi = num(u['range'][0]), num(u['range'][1])
        functions = None
    else:                                           # a file compiled several times with -D selectors
        src = sorted(f['addr'] for f in u['functions'] if f['status'] == 'source')
        lo, hi = src[0], ends[src[-1]]
        functions = src
    e = {'src': u['source'], 'range': [lo, hi]}
    if functions is not None:
        e['functions'] = functions
    if u.get('compiler', S.DEFAULT_COMPILER) != S.DEFAULT_COMPILER:
        e['compiler'] = u['compiler']
    if flags != S.DEFAULT_FLAGS:
        e['flags'] = flags
    if assembler:
        e['assembler'] = assembler
    if '-ffunction-sections' not in u['flags']:
        e['sections'] = False
    if u.get('owner'):
        e['owner'] = u['owner']
    for k in ('data_ranges', 'rodata_type_splits', 'shared_exception_tables', 'full_tu_context', 'unlinked_context_helpers'):
        if u.get(k):
            e[k] = u[k]
    if u.get('note'):
        e['note'] = u['note']
    if u.get('full_tu_context'):          # the real bodies of the TU's other functions are compiled for context only
        own = {f['symbol'] for f in u['functions'] if f['status'] == 'source'}
        helpers = set(u.get('unlinked_context_helpers') or []) | {f['symbol'] for f in u['functions']
                                                               if f.get('symbol') and f['symbol'] not in own}
        e['unlinked_context_helpers'] = sorted(helpers)
    return e


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else ''
    if cmd not in ('write', 'check'):
        raise SystemExit(__doc__)
    units = load()
    placement = json.loads((ROOT / 'build' / SLUG / 'placement.json').read_text())['functions']
    ends = {f['addr']: f['end'] for f in placement}
    starts = set(ends)
    if cmd == 'write':
        entries = sorted((split_entry(u, ends) for u in units), key=lambda e: (e['range'][0], e['src']))
        # symbols: definitions with a name other than func_XXXXXXXX, and extern bindings
        rows, bound = set(), {}
        for u in units:
            for f in u['functions']:
                if f.get('symbol') and f['symbol'] != 'func_%08X' % f['addr']:
                    rows.add((f['symbol'], f['addr'], 'func'))
            for k, v in (u.get('externs') or {}).items():
                bound.setdefault(k, set()).add(num(v))
        for p in glob.glob(str(ROOT / '.local/import/*_bindings.json')):
            for _, b in json.loads(Path(p).read_text()).items():
                for k, v in b.items():
                    bound.setdefault(k, set()).add(num(v))
        for name, addrs in bound.items():
            for a in addrs:
                rows.add((name, a, 'func' if a in starts else 'data'))
        # names bound to several addresses: the units that use one of them say which in their split
        ambiguous = {n for n, a in bound.items() if len(a) > 1}
        for u, e in zip(sorted(units, key=lambda u: 0), []):
            pass
        by_src = {}
        for u in units:
            ext = {k: num(v) for k, v in (u.get('externs') or {}).items() if k in ambiguous}
            if ext:
                by_src.setdefault((u['source'], num(u['range'][0]) if 'range' in u else None), {}).update(ext)
        for e in entries:
            ext = by_src.get((e['src'], e['range'][0])) or by_src.get((e['src'], None))
            if ext:
                e['externs'] = {k: '0x%x' % v for k, v in sorted(ext.items())}
        CFG.mkdir(parents=True, exist_ok=True)
        (CFG / 'splits.yaml').write_text(S.format_splits(entries, {'compiler': S.DEFAULT_COMPILER, 'flags': S.DEFAULT_FLAGS,
                                                                    'sections': True}, HEADER))
        (CFG / 'symbols.txt').write_text(S.format_symbols(rows))
        eq = []
        for u in units:
            for f in u['functions']:
                if f.get('evidence'):
                    nm = f.get('nonmatching') or {}
                    eq.append(dict(addr='0x%06x' % f['addr'], **{k: nm[k] for k in ('source', 'symbol', 'returns') if k in nm},
                                   evidence=f['evidence']))
        eq.sort(key=lambda r: r['addr'])
        (CFG / 'equivalent.yaml').write_text(
            '# Functions of the `equivalent` evidence tier (agreement on recorded states, measured coverage; not a proof).\n'
            '# They stay assembly in the build; `source` is the TU file whose NON_MATCHING block holds the candidate.\n' +
            yaml.safe_dump({'functions': eq}, sort_keys=False, width=140))
        print('%d splits, %d symbols, %d equivalent functions' % (len(entries), len(rows), len(eq)))
        return 0
    import units as U
    derived = {}
    table = [(f['addr'], f['end']) for f in placement]
    for d in U.derive_units(S.load_splits(SLUG), table, S.load_symbols(SLUG), S.load_equivalent(SLUG)):
        derived[(d['source'], d['range'][0])] = d
    bad = 0
    for u in units:
        lo = num(u['range'][0]) if 'range' in u else min(f['addr'] for f in u['functions'] if f['status'] == 'source')
        d = derived.get((u['source'], lo)) or next((v for (s, _), v in derived.items() if s == u['source'] and
                                                    {f['addr'] for f in v['functions'] if f['status'] == 'source'} ==
                                                    {f['addr'] for f in u['functions'] if f['status'] == 'source'}), None)
        want = {f['addr']: f.get('symbol') for f in u['functions'] if f['status'] == 'source'}
        got = {f['addr']: (f['symbol'] if f['symbol'] == want.get(f['addr']) or want.get(f['addr']) in f.get('candidates', ()) else f['symbol']) for f in d['functions'] if f['status'] == 'source'} if d else None
        if got is not None:
            got = {a: (want[a] if want.get(a) in next((x.get('candidates', ()) for x in d['functions'] if x['addr'] == a), ()) else s) for a, s in got.items()}
        if got != want or (d and sorted(d['flags']) != sorted(u['flags'])):
            bad += 1
            if bad < 8:
                print('differs:', u['name'], u['source'], None if got is None else (set(got) ^ set(want), [k for k in want if got.get(k) != want[k]][:3]),
                      sorted(d['flags']) if d else None, sorted(u['flags']))
    print('%d of %d units differ' % (bad, len(units)))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
