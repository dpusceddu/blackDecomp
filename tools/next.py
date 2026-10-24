#!/usr/bin/env python3
"""Best next work, from the automatic pipeline's results (build/auto.json) and the source units (tools/build/units.py).

  next.py [near|types|families|data|ee|all] [--top N] [--max-size N]

  near      near misses by differing-instruction count, with what differs (registers, order, code, length)
  types     functions the pipeline could not compile or decompile for want of a type, grouped by what they need
  families  groups of assembly functions with identical bodies (candidates for one template or one shared source)
  data      exact drafts that could not be placed because the function owns rodata (strings, tables)
  ee        functions m2c cannot read (EE instructions), grouped by instruction
  tus       candidate translation units for a Phase 5 agent (config/tus.yaml): shown first by `all`
Functions already provided by source units are left out everywhere.
"""
import argparse, collections, json, re, struct, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
from units import load_units, ROOT

RESULTS = ROOT / 'build' / 'auto.json'
GLOBAL = re.compile(r'\bD_[0-9A-F]{6,8}\b')
CALLEE = re.compile(r'\bfunc_[0-9A-F]{6,8}\b')


def load():
    res = json.loads(RESULTS.read_text()) if RESULTS.exists() else {}
    done = {f['addr'] for u in load_units(variant='SLUS_213.76') for f in u['functions'] if f.get('status') == 'source'}
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
    sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
    import autodecomp
    inv = autodecomp.load_inventory()
    done = {f['addr'] for u in load_units(variant='SLUS_213.76') for f in u['functions'] if f.get('status') == 'source'}
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


EE_VECTOR = re.compile(r'^(p(add|sub|cpy|ext|pac|mul|div|and|or|nor|xor|abs|min|max|lzc|sll|srl|sra|rot|ack|mfh|mth|mfl|mtl|ceq|cgt|inc|sat)[a-z0-9]*|lqc2|sqc2|qm[ft]c2.*|c[ft]c2|v[a-z0-9.]+|mf(sa|hi1|lo1)|mt(sa|sah|hi1|lo1)|madd1|mult1|multu1|div1|divu1|adda.*|suba.*|madda.*)$')


def candidates(top, args=None):
    """TUs a Phase 5 agent can finish by hand: most of the TU already in source, a moderate rest, known classes, few EE vector
    functions. Scored from config/tus.yaml, the source units and the function inventory."""
    import bisect, yaml
    path = ROOT / 'config/tus.yaml'
    if not path.exists():
        return
    sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
    import autodecomp
    tus = [t for t in yaml.safe_load(path.read_text())['tus'] if t['kind'] == 'object']
    inv = autodecomp.load_inventory()
    done = {f['addr'] for u in load_units(variant='SLUS_213.76') for f in u['functions'] if f.get('status') == 'source'}
    import splits
    alias = splits.load_symbols('SLUS_213.76').function_aliases()
    starts = [int(t['text'][0], 16) for t in tus]
    rows = [dict(t=t, n=0, src=0, bytes=0, left=0, vec=0, left_n=0, named=0, orphans=0,
                 large_left=0, large_bytes=0) for t in tus]
    for f in inv:
        k = bisect.bisect_right(starts, f['addr']) - 1
        if k < 0 or f['addr'] >= int(tus[k]['text'][1], 16):
            continue
        r = rows[k]
        if autodecomp.is_orphan(f['words']):
            r['orphans'] += 1
            continue
        r['n'] += 1
        r['bytes'] += f['span']
        r['named'] += f['addr'] in alias
        if f['addr'] in done:
            r['src'] += 1
        else:
            r['left'] += f['span']
            r['left_n'] += 1
            r['vec'] += any(EE_VECTOR.match(m) for m in f['mnem'])
            if f['size'] > 300:
                r['large_left'] += 1
                r['large_bytes'] += f['span']
    out = []
    wide = bool(args and getattr(args, 'wide', False))
    libraries = set(getattr(args, 'library', None) or
                    ('game', 'kynapse', 'animation', 'physics', 'apt', 'rwa_ee', 'renderware_core'))
    for r in rows:
        t = r['t']
        if t['library'] not in libraries or r['n'] < (2 if wide else 4) or r['left_n'] < (1 if wide else 2) \
                or not 1 <= r['left'] <= (60000 if wide else 20000) or r['left_n'] > (160 if wide else 60):
            continue
        share = r['src'] / r['n']
        if not wide and (share < 0.15 or r['left'] < 250 or r['vec'] > max(1, r['left_n'] // 6)):
            continue
        conf = {'exact': 1.0, 'high': 0.8, 'medium': 0.5, 'low': 0.2}[t['confidence']]
        known = (r['named'] / r['n']) + (0.3 if t['library'] in ('kynapse', 'animation', 'physics') else 0) \
            + (0.9 if 0x1a0000 <= int(t['text'][0], 16) < 0x1b8000 else 0)         # the AI action and movement code (CBkRwAI* strings)
        score = 2 * share + conf + known - 0.15 * r['vec'] + min(r['left'], 6000) / 4000.0 - r['left'] / 40000.0
        if wide:
            score += min(r['large_bytes'], 12000) / 12000.0
        out.append((score, r))
    out.sort(key=lambda x: -x[0])
    seen, per_lib, picked = set(), collections.Counter(), []
    if args and getattr(args, 'debug', False):
        for score, r in out[:60]:
            print('   %.2f %s n=%d src=%d left=%d vec=%d' % (score, r['t']['name'], r['n'], r['src'], r['left'], r['vec']))
    per_library = getattr(args, 'per_library', 3) if args else 3
    for score, r in out:
        shape = (r['t']['library'], r['n'], r['src'], r['left'])
        if shape in seen or (per_library and per_lib[r['t']['library']] >= per_library):
            continue
        seen.add(shape)
        per_lib[r['t']['library']] += 1
        picked.append((score, r))
    out = picked
    if args and getattr(args, 'json', False):
        print(json.dumps([dict(r, score=score) for score, r in out[:top]], indent=2))
        return out[:top]
    print('Candidates: ' + ('wide queue, including large and vector functions' if wide else
          'translation units to finish by hand (most already in source, moderate rest, few EE vector functions)'))
    print('  %-34s %-9s %-6s %9s %12s %9s %5s' % ('TU', 'library', 'bounds', 'functions', 'in source', 'left (B)', 'vec'))
    for score, r in out[:top]:
        t = r['t']
        print('  %-34s %-9s %-6s %9d %5d (%3d%%) %9d %5d   %s-%s' % (t['name'][:34], t['library'][:9], t['confidence'], r['n'], r['src'],
              100 * r['src'] // r['n'], r['left'], r['vec'], t['text'][0], t['text'][1]) +
              ('  large: %d / %d B' % (r['large_left'], r['large_bytes']) if wide else ''))
    print()
    return out[:top]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('what', nargs='?', default='all', choices=['near', 'types', 'families', 'data', 'ee', 'tus', 'all'])
    ap.add_argument('--top', type=int, default=15)
    ap.add_argument('--max-size', type=int)
    ap.add_argument('--library', action='append', help='TU library filter (repeatable)')
    ap.add_argument('--wide', action='store_true', help='include untouched/vector TUs and rank remaining large functions')
    ap.add_argument('--per-library', type=int, default=3, help='maximum candidates per library; 0 means unlimited')
    ap.add_argument('--json', action='store_true', help='machine-readable TU queue candidates')
    a = ap.parse_args()
    if a.what in ('tus', 'all'):
        candidates(max(a.top, 10) if a.what == 'all' else a.top, a)
        if a.what == 'tus':
            return
    res = load()
    if not res:
        raise SystemExit('no results: run tools/autodecomp.py run first')
    for name, fn in (('near', near), ('types', types), ('families', families), ('data', data), ('ee', ee)):
        if a.what in (name, 'all'):
            fn(res, a.top, a.max_size)
            print()


if __name__ == '__main__':
    main()
