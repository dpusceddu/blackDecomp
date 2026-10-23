#!/usr/bin/env python3
"""Merge the source units of one translation unit (config/tus.yaml) into one source file and one unit.

  regroup.py plan [--sections]   show what would be merged
  regroup.py merge [--limit N] [--sections]
                                 merge, settle (compile, link, compare) and keep the merges that leave the image identical

Without --sections only runs of adjacent functions are merged. With --sections one unit holds every source function of a TU,
compiled with -ffunction-sections: each function gets its own section (`.text.<symbol>`) and make_ld.py places it in the slot of
its original function, so assembly functions (orphan pieces, hard cases) may sit between the source functions of the TU and the
source file still shows the TU in address order. The constants of the unit keep one section, which must find adjacent slots.

The automatic pipeline registers adjacent exact drafts in groups of at most 24 without knowing the translation units. A
group is a run of adjacent functions that a unit replaces as a whole, so any run of adjacent functions with the same
compiler and flags inside one TU can be one unit: its source is the concatenation of the sources (declarations once, then the
bodies in address order) and it is written to src/<library>/<tu>.c (tools/layout.py). The merge only has to leave the linked image identical:
`settle_units.py` compiles and links, and a merged unit that fails (a constant pool the original did not have, a declaration
that no longer agrees with a definition in the same file, ...) is replaced by the units it came from.

Units that are not plain C drafts (imported C++ with its own headers, owned-constant arrays shared between functions) are
left alone. Asm functions between the source functions of a TU split its runs; a run is never extended over them. The
clean way to interleave source and assembly inside one source file, `-ffunction-sections`, is described in the README
("Translation units", "Regrouping").
"""
import argparse, bisect, json, re, shutil, subprocess, sys
from pathlib import Path

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
from units import load_units, ROOT
import layout
import units_verify

SLUG = 'usa-retail'
BUILD = ROOT / 'build' / SLUG


def split_source(text):
    """(includes, preamble lines, body) of a plain C draft: everything before the first function definition is preamble."""
    lines = text.split('\n')
    inc, pre, i = [], [], 0
    while i < len(lines):
        l = lines[i]
        if l.startswith('#include'):
            inc.append(l)
        elif l.strip() == '' or l.startswith('extern') or l.startswith('typedef') or l.startswith('const') or l.startswith('static const'):
            if l.strip():
                pre.append(l)
        else:
            break
        i += 1
    return inc, pre, '\n'.join(lines[i:]).strip('\n')


def base_flags(u):
    return [f for f in u['flags'] if f != '-ffunction-sections']


def plan(units, tus, limit=None, sections=False):
    """Groups of units to merge: [(tu name, [units])]. Units must be wholly source, plain C, same compiler and flags, and (unless
    `sections`) adjacent."""
    placement = json.loads((BUILD / 'placement.json').read_text())['functions']
    index = {f['addr']: i for i, f in enumerate(placement)}
    starts = [int(t['text'][0], 16) for t in tus]
    ends = [int(t['text'][1], 16) for t in tus]

    def tu_of(addr):
        k = bisect.bisect_right(starts, addr) - 1
        return k if k >= 0 and addr < ends[k] else None

    cand = []
    for u in units:
        fs = u['functions']
        if not fs or any(f.get('status') != 'source' for f in fs) or u.get('origin') != 'auto' or not u['source'].endswith('.c'):
            continue
        if u.get('trim') or u.get('unbound'):
            continue
        ks = {tu_of(f['addr']) for f in fs}
        if len(ks) != 1 or None in ks:
            continue                                    # the unit straddles a TU boundary of the map
        cand.append((index[fs[0]['addr']], index[fs[-1]['addr']], next(iter(ks)), u))
    cand.sort(key=lambda c: c[0])
    groups, cur = [], []
    for first, last, k, u in cand:
        if cur and cur[-1][2] == k and (sections or cur[-1][1] + 1 == first) and base_flags(cur[-1][3]) == base_flags(u) \
                and cur[-1][3]['compiler'] == u['compiler']:
            cur.append((first, last, k, u))
        else:
            if len(cur) > 1:
                groups.append(cur)
            cur = [(first, last, k, u)]
    if len(cur) > 1:
        groups.append(cur)
    out = [(tus[g[0][2]]['name'], [c[3] for c in g]) for g in groups]
    if sections:                                   # one function per symbol: a section is named after its symbol
        out = [(n, g) for n, g in out if len({f['symbol'] for u in g for f in u['functions']}) == sum(len(u['functions']) for u in g)]
    return out[:limit] if limit else out


def merged_unit(name, group, sections=False, taken=None):
    taken = set() if taken is None else taken
    pre_all, inc_all, bodies, externs, notes = [], [], [], {}, []
    placement = json.loads((BUILD / 'placement.json').read_text())['functions'] if sections else []
    prev_last = None
    for u in group:
        text = (ROOT / u['source']).read_text()
        text = re.sub(r'/\* Translation unit .*?\*/\n', '', text, flags=re.S)           # notes of an earlier regrouping
        text = re.sub(r'/\* Assembly between the functions: .*?\*/\n\n', '', text, flags=re.S)
        inc, pre, body = split_source(text)
        note = ''
        if sections and prev_last is not None:             # the assembly functions that sit between this run and the one before
            gap = [f for f in placement if prev_last < f['addr'] < u['functions'][0]['addr']]
            if gap:
                note = '/* Assembly between the functions: %s */\n\n' % (
                    ', '.join('%s (%d bytes)' % (f['name'], f['end'] - f['addr']) for f in gap[:12]) + (' ...' if len(gap) > 12 else ''))
        notes.append(note)
        prev_last = u['functions'][-1]['addr']
        for l in inc:
            if l not in inc_all:
                inc_all.append(l)
        for l in pre:
            if l not in pre_all:
                pre_all.append(l)
        bodies.append(body)
        for k, v in (u.get('externs') or {}).items():
            if externs.setdefault(k, v) != v:
                return None
    defined = {re.search(r'\b(\w+)\s*\(', b.split('{')[0]).group(1) for b in bodies if '{' in b}
    pre_all = [l for l in pre_all if not (l.startswith('extern') and re.search(r'\b(%s)\s*\(' % '|'.join(map(re.escape, defined)), l))]
    text = '\n'.join(inc_all) + '\n\n' + ('\n'.join(pre_all) + '\n\n' if pre_all else '') + '\n\n'.join(n + b for n, b in zip(notes, bodies)) + '\n'
    first = group[0]['functions'][0]['addr']
    rel = layout.source_path(first)
    flags = base_flags(group[0])
    if sections:
        base = name.replace('/', '_')
        taken.add(base)
        flags.append('-ffunction-sections')
        text = '/* Translation unit %s of the TU map: its source functions in address order; assembly functions between them stay\n   in the image and are placed by address. */\n' % name + text
    k = 1
    stem = rel[:-2]
    while (ROOT / rel).exists():                       # never overwrite a source a unit still refers to (a failed merge is undone)
        k += 1
        rel = '%s_%d.c' % (stem, k)
    funcs = [dict(f) for u in group for f in u['functions']]
    return dict(name=('tuf_' if sections else 'tu_') + '%06x' % first, source=rel, library=Path(rel).parts[1], provenance='auto', tier='exact', origin='auto', compiler=group[0]['compiler'],
                flags=flags, externs=externs, functions=funcs), text


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('what', choices=['plan', 'merge'])
    ap.add_argument('--limit', type=int)
    ap.add_argument('--retry', action='store_true', help='try the groups that failed before again')
    ap.add_argument('--sections', action='store_true', help='one unit per TU compiled with -ffunction-sections (assembly may sit between its functions)')
    a = ap.parse_args()
    tus = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())['tus']
    units = load_units(variant=SLUG)
    groups = plan(units, tus, a.limit, a.sections)
    failed_path = BUILD / 'regroup_failed.json'
    failed_before = set(json.loads(failed_path.read_text())) if failed_path.exists() and not a.retry else set()
    groups = [(n, g) for n, g in groups if '%s:%d' % (a.sections, g[0]['functions'][0]['addr']) not in failed_before or a.what == 'plan']
    print('%d groups of units in one TU: %d units -> %d' % (len(groups), sum(len(g) for _, g in groups), len(groups)))
    if a.what == 'plan':
        for name, g in groups[:30]:
            print('  %-30s %2d units, %3d functions at 0x%06x' % (name[:30], len(g), sum(len(u['functions']) for u in g), g[0]['functions'][0]['addr']))
        return 0
    backup = BUILD / 'units.before_regroup.yaml'
    shutil.copy(ROOT / 'config/units.yaml', backup)
    merged, replaced, taken = {}, set(), set()
    for name, g in groups:
        r = merged_unit(name, g, a.sections, taken)
        if r is None:
            continue
        mu, text = r
        (ROOT / mu['source']).parent.mkdir(parents=True, exist_ok=True)
        (ROOT / mu['source']).write_text(text)
        merged[mu['name']] = (mu, g)
        replaced.update(id(u) for u in g)
    new = []
    for u in units:
        if id(u) in replaced:
            for mu, g in merged.values():
                if g[0] is u:
                    new.append(mu)
            continue
        new.append(u)
    units_verify.save(new)
    for rnd in range(3):
        r = subprocess.run([sys.executable, str(ROOT / 'tools/settle_units.py')], cwd=ROOT, capture_output=True, text=True)
        print(r.stdout.strip().split('\n')[-1])
        cur = load_units(variant=SLUG)
        failed = [u for u in cur if u['name'] in merged and any(f.get('status') != 'source' for f in u['functions'])]
        print('round %d: %d of %d merged units failed' % (rnd, len(failed), len(merged)))
        if not failed and r.returncode == 0:
            break
        bad = {u['name'] for u in failed}
        known = set(json.loads(failed_path.read_text())) if failed_path.exists() else set()
        known.update('%s:%d' % (a.sections, merged[n][1][0]['functions'][0]['addr']) for n in bad)
        failed_path.write_text(json.dumps(sorted(known)))
        restored = []
        for u in cur:
            if u['name'] in bad:
                restored.extend(merged[u['name']][1])
                (ROOT / u['source']).unlink(missing_ok=True)
                merged.pop(u['name'])
            else:
                restored.append(u)
        units_verify.save(restored)
    live = {u['source'] for u in load_units(variant=SLUG)}
    for mu, g in merged.values():                       # the drafts the merged source replaced are no longer referenced
        for u in g:
            if u['source'] not in live:
                (ROOT / u['source']).unlink(missing_ok=True)
    r = subprocess.run(['ninja'], cwd=ROOT, capture_output=True, text=True)
    print(r.stdout.strip().split('\n')[-1])
    print('kept %d merged units (%d units merged away)' % (len(merged), sum(len(g) for _, g in merged.values())))
    return 0


if __name__ == '__main__':
    sys.exit(main())
