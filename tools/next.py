#!/usr/bin/env python3
"""Best next work, from the automatic pipeline's results (build/auto.json) and the source units (config/units.yaml).

  next.py [near|types|families|data|ee|all] [--top N] [--max-size N]

  near      near misses by differing-instruction count, with what differs (registers, order, code, length)
  types     functions the pipeline could not compile or decompile for want of a type, grouped by what they need
  families  groups of assembly functions with identical bodies (candidates for one template or one shared source)
  data      exact drafts that could not be placed because the function owns rodata (strings, tables)
  ee        functions m2c cannot read (EE instructions), grouped by instruction
Functions already provided by source units are left out everywhere.
"""
import argparse, collections, json, re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from units import load_units, ROOT

RESULTS = ROOT / 'build' / 'auto.json'
GLOBAL = re.compile(r'\bD_[0-9A-F]{6,8}\b')
CALLEE = re.compile(r'\bfunc_[0-9A-F]{6,8}\b')


def load():
    res = json.loads(RESULTS.read_text()) if RESULTS.exists() else {}
    done = {f['addr'] for u in load_units(variant='usa-retail') for f in u['functions'] if f.get('status') == 'source'}
    return {k: v for k, v in res.items() if int(k, 16) not in done}


def near(res, top, max_size):
    rows = [(v['score'], v['size'], k, v) for k, v in res.items() if v['status'] == 'near' and (max_size is None or v['size'] < max_size)]
    rows.sort(key=lambda r: (r[0], r[1]))
    by = collections.Counter((r[0], r[3].get('note', '')) for r in rows)
    print('near misses: %d functions' % len(rows))
    print('  differing instructions x kind of difference:')
    for n in sorted({s for s, _ in by}):
        print('   %2d: %s' % (n, ', '.join('%s %d' % (kind or '?', c) for (s, kind), c in sorted(by.items()) if s == n)))
    print('  closest (address, size, differing, kind, permuter):')
    for score, size, k, v in rows[:top]:
        p = v.get('permuter')
        print('   %s  %4d bytes  %d  %-10s %s' % (k, size, score, v.get('note', ''), ('tried %d, best %s' % (p.get('tries', 0), p.get('best'))) if p else ''))


def needs(v):
    """What a failed draft is missing, as (kind, subject)."""
    src = v.get('source', '')
    reason = v.get('reason', '')
    if v['status'] == 'm2c-failed':
        if reason.startswith('stack-object'):
            return 'local aggregate type (address of a stack object is passed on)', ''
        if reason.startswith('unset-register'):
            return 'calling convention (register read before it is set)', ''
        return None
    callee = CALLEE.findall(src.split('{', 1)[-1])
    glob = GLOBAL.findall(src)
    if 'too few arguments' in reason or 'too many' in reason:
        return 'callee signature', callee[0] if callee else ''
    if 'invalid type argument' in reason or 'invalid operands' in reason or 'void' in reason or 'wide integer' in reason \
            or 'cannot convert' in reason or 'pointer value' in reason:
        return 'type of a global or pointer (deref or arithmetic on an untyped value)', glob[0] if glob else 'argument/pointer'
    if 'undeclared' in reason:
        return 'declaration', reason.split('`')[1] if '`' in reason else ''
    return 'other compile error: ' + reason[:50], ''


def types(res, top, max_size):
    groups = collections.defaultdict(list)
    for k, v in res.items():
        if v['status'] in ('compile-failed', 'm2c-failed') and (max_size is None or v['size'] < max_size):
            n = needs(v)
            if n:
                groups[n].append(k)
    total = sum(len(g) for g in groups.values())
    print('missing types: %d functions' % total)
    kinds = collections.Counter()
    for (kind, _), g in groups.items():
        kinds[kind] += len(g)
    for kind, c in kinds.most_common():
        print('  %5d  %s' % (c, kind))
    print('  most needed subjects (one type or signature fixes all of a row):')
    for (kind, subject), g in sorted(groups.items(), key=lambda t: -len(t[1]))[:top]:
        if subject:
            print('   %3d  %-14s %s' % (len(g), subject, kind[:60]))


def families(res, top, max_size):
    sys.path.insert(0, str(ROOT / 'tools'))
    import autodecomp
    inv = autodecomp.load_inventory()
    done = {f['addr'] for u in load_units(variant='usa-retail') for f in u['functions'] if f.get('status') == 'source'}
    groups = collections.defaultdict(list)
    for f in inv:
        if f['addr'] in done or f['size'] <= 4 or (max_size is not None and f['size'] >= max_size):
            continue
        masked = []
        for i, w in enumerate(f['words']):
            r = f['rel'].get(str(i))
            masked.append(w & (0xFC000000 if r and r[0] == 'jal' else 0xFFFF0000) if r else w)
        groups[tuple(masked)].append(f)
    fams = [g for g in groups.values() if len(g) > 1]
    fams.sort(key=lambda g: -len(g) * g[0]['size'])
    print('families of identical bodies (relocations masked): %d families, %d functions' % (len(fams), sum(len(g) for g in fams)))
    for g in fams[:top]:
        st = collections.Counter(res.get('0x%x' % f['addr'], {}).get('status', 'untried') for f in g)
        print('  %4d x %3d bytes  e.g. 0x%x  %s' % (len(g), g[0]['size'], g[0]['addr'], dict(st)))


def data(res, top, max_size):
    rows = [(k, v) for k, v in res.items() if v['status'] == 'verify-failed' and v['reason'] == 'size']
    print('exact drafts blocked by owned rodata: %d functions, %d bytes' % (len(rows), sum(v['size'] for _, v in rows)))
    for k, v in rows[:top]:
        print('  %s %4d bytes %s' % (k, v['size'], v['name']))


def ee(res, top, max_size):
    c = collections.Counter()
    for k, v in res.items():
        if v['status'] == 'm2c-failed' and 'unknown instruction' in v.get('reason', ''):
            m = re.search(r'unknown instruction: (\S+)', v['reason'])
            c[m.group(1)] += 1
    print('functions m2c cannot read: %d' % sum(c.values()))
    for m, n in c.most_common(top):
        print('  %4d  %s' % (n, m))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('what', nargs='?', default='all', choices=['near', 'types', 'families', 'data', 'ee', 'all'])
    ap.add_argument('--top', type=int, default=15)
    ap.add_argument('--max-size', type=int)
    a = ap.parse_args()
    res = load()
    if not res:
        raise SystemExit('no results: run tools/autodecomp.py run first')
    for name, fn in (('near', near), ('types', types), ('families', families), ('data', data), ('ee', ee)):
        if a.what in (name, 'all'):
            fn(res, a.top, a.max_size)
            print()


if __name__ == '__main__':
    main()
