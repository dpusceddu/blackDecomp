#!/usr/bin/env python3
"""Report how much of .text is provided by source (config/units.yaml, status source), overall and by region.

Regions come from config/regions.txt (PS2 address -> game, kynapse, animation, physics or other), derived from the
companion project's Xbox-to-PS2 counterpart map (`progress.py --refresh` rewrites it). An unmapped function takes the
region of its neighbours when both sides agree, otherwise it is `unclassified`. Regions are therefore approximate;
the overall number is exact.
A function counts as source when config/units.yaml lists it with `status: source` (units_verify.py/settle_units.py keep
that list identical to the target); bytes are the original span of the function up to the next function.
Usage: progress.py [SLUG]       writes build/<slug>/progress.json and prints a table
       progress.py --tus [N]     also list the N (default 15) partially done translation units with most bytes still in assembly
When config/tus.yaml exists (tools/tus.py) the report adds the progress by TU: complete TUs (every function from source),
partially done ones and bytes per TU, by confidence of the TU boundaries.
"""
import json, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from units import load_units

ROOT = Path(__file__).resolve().parents[1]
REGIONS = ROOT / 'config/regions.txt'
PARENT_MAP = ROOT.parent / 'the counterpart map'


def refresh_regions():
    """Rewrite config/regions.txt (address, region) from the companion project's Xbox-to-PS2 counterpart map."""
    pairs = json.loads(PARENT_MAP.read_text())['pairs']
    rows = sorted({(int(p['ps2'], 16), p['region']) for p in pairs})
    REGIONS.write_text('# PS2 function address -> region (game, kynapse, animation, physics, other), from the\n'
                       '# companion project counterpart map (discovery leads, not byte-compared); tools/progress.py --refresh\n' +
                       ''.join('0x%08X %s\n' % r for r in rows))
    print('wrote %s: %d functions' % (REGIONS.name, len(rows)))


def regions(addrs):
    reg = {}
    if REGIONS.exists():
        for line in REGIONS.read_text().split('\n'):
            if line and not line.startswith('#'):
                a, r = line.split()
                reg[int(a, 16)] = r
    lab = [reg.get(a) for a in addrs]
    nxt, n = [None] * len(lab), None
    for i in range(len(lab) - 1, -1, -1):
        n = lab[i] or n
        nxt[i] = n
    out, prev = [], None
    for i, l in enumerate(lab):
        if l:
            prev = l
            out.append(l)
        else:
            out.append(prev if prev == nxt[i] and prev else 'unclassified')
    return out, bool(reg)


def tu_report(slug, fs, spans, source, top):
    """Progress by translation unit (config/tus.yaml): rows by confidence and the TUs closest to completion."""
    path = ROOT / 'config/tus.yaml'
    if not path.exists() or slug != 'usa-retail':
        return None
    import bisect, yaml
    tus = yaml.safe_load(path.read_text())['tus']
    starts = [int(t['text'][0], 16) for t in tus]
    rows = [dict(name=t['name'], kind=t['kind'], conf=t['confidence'], lib=t['library'], lo=starts[k], functions=0,
                 source_functions=0, bytes=0, source_bytes=0) for k, t in enumerate(tus)]
    orphan = set()                 # unreferenced `<instruction>; nop` runs stay assembly and do not count against a TU
    auto = ROOT / 'build/auto.json'
    if auto.exists():
        orphan = {int(k, 16) for k, v in json.loads(auto.read_text()).items() if v.get('status') == 'orphan'}
    for f, span in zip(fs, spans):
        k = bisect.bisect_right(starts, f['addr']) - 1
        r = rows[k]
        if f['addr'] in orphan:
            r['bytes'] += span
            continue
        r['functions'] += 1
        r['bytes'] += span
        if f['addr'] in source:
            r['source_functions'] += 1
            r['source_bytes'] += span
    kinds = {}
    for r in rows:
        for key in ('ALL', 'conf: ' + r['conf'], 'kind: ' + r['kind'], 'lib: ' + (r['lib'] or '?')):
            k = kinds.setdefault(key, dict(tus=0, complete=0, partial=0, untouched=0, complete_bytes=0, source_bytes=0, bytes=0))
            k['tus'] += 1
            k['bytes'] += r['bytes']
            k['source_bytes'] += r['source_bytes']
            if r['source_functions'] == r['functions']:
                k['complete'] += 1
                k['complete_bytes'] += r['bytes']
            elif r['source_functions']:
                k['partial'] += 1
            else:
                k['untouched'] += 1
    print()
    print('by translation unit (config/tus.yaml; boundaries of the TUs below `exact` are proposals)')
    print('%-18s %6s %9s %8s %10s   %11s %11s %9s' % ('', 'TUs', 'complete', 'partial', 'untouched', 'complete B', 'source B', 'bytes'))
    for key in sorted(kinds, key=lambda k: (k != 'ALL', k.startswith('lib'), k)):
        k = kinds[key]
        print('%-18s %6d %9d %8d %10d   %11d %11d %9d' % (key, k['tus'], k['complete'], k['partial'], k['untouched'],
                                                         k['complete_bytes'], k['source_bytes'], k['bytes']))
    if top:
        part = [r for r in rows if r['source_functions'] and r['source_functions'] < r['functions']]
        part.sort(key=lambda r: (r['bytes'] - r['source_bytes']))
        print()
        print('partially done TUs with the fewest bytes left in assembly')
        for r in part[:top]:
            print('  %-34s 0x%06x %-9s %-6s %4d/%-4d functions  %6d of %6d bytes left' % (
                r['name'][:34], r['lo'], r['lib'][:9], r['conf'], r['functions'] - r['source_functions'], r['functions'],
                r['bytes'] - r['source_bytes'], r['bytes']))
    return dict(rows=kinds, tus=rows)


def main():
    if '--refresh' in sys.argv:
        return refresh_regions()
    top = 0
    if '--tus' in sys.argv:
        k = sys.argv.index('--tus')
        top = int(sys.argv[k + 1]) if k + 1 < len(sys.argv) and sys.argv[k + 1].isdigit() else 15
    slug = next((a for a in sys.argv[1:] if not a.startswith('-') and not a.isdigit()), 'usa-retail')
    build = ROOT / 'build' / slug
    fs = json.loads((build / 'placement.json').read_text())['functions']
    layout = json.loads((ROOT / 'config' / ('%s.layout.json' % json.loads(
        (ROOT / 'config/variants.json').read_text())[slug]['boot'])).read_text())
    text = next(s for s in layout['sections'] if s['name'] == '.text')
    spans = [(fs[i + 1]['addr'] if i + 1 < len(fs) else text['addr'] + text['orig_size']) - fs[i]['addr']
             for i in range(len(fs))]
    source = {}
    equivalent = set()
    for u in load_units(variant=slug):
        for f in u['functions']:
            if f.get('evidence',{}).get('tier') == 'equivalent':
                equivalent.add(f['addr'])
            if f.get('status') == 'source':
                source[f['addr']] = u.get('origin', u['name'].split('_')[0])
    region, mapped = regions([f['addr'] for f in fs])
    rows = {}

    def add(key, span, src):
        r = rows.setdefault(key, dict(functions=0, source_functions=0, bytes=0, source_bytes=0))
        r['functions'] += 1
        r['bytes'] += span
        if src:
            r['source_functions'] += 1
            r['source_bytes'] += span

    for f, span, reg in zip(fs, spans, region):
        src = f['addr'] in source
        add('ALL', span, src)
        add('region: ' + reg, span, src)
        if src:
            add('origin: ' + source[f['addr']], span, True)
    tiers = {key:dict(functions=0,bytes=0) for key in ('exact','equivalent','draft')}
    for f,span in zip(fs,spans):
        tier = 'exact' if f['addr'] in source else 'equivalent' if f['addr'] in equivalent else 'draft'
        tiers[tier]['functions'] += 1
        tiers[tier]['bytes'] += span
    out = dict(text_bytes=text['orig_size'], regions_from_map=mapped, rows=rows, evidence_tiers=tiers)
    (build / 'progress.json').write_text(json.dumps(out, indent=1))
    print('%-22s %7s %7s %6s   %9s %9s %6s' % ('', 'funcs', 'source', '%', 'bytes', 'source', '%'))
    for key in sorted(rows, key=lambda k: (k != 'ALL', k.startswith('origin'), k)):
        r = rows[key]
        if key.startswith('origin'):
            print('%-22s %7s %7d %6s   %9s %9d %6s' % (key, '', r['source_functions'], '', '', r['source_bytes'], ''))
            continue
        print('%-22s %7d %7d %5.2f%%   %9d %9d %5.2f%%' % (
            key, r['functions'], r['source_functions'], 100.0 * r['source_functions'] / r['functions'],
            r['bytes'], r['source_bytes'], 100.0 * r['source_bytes'] / max(r['bytes'], 1)))
    print('\nRecorded evidence (matching source stays exact; equivalent means tested states):')
    for tier,r in tiers.items():
        print('  %-12s %7d functions %9d bytes' % (tier,r['functions'],r['bytes']))
    tur = tu_report(slug, fs, spans, source, top)
    if tur:
        out['by_tu'] = tur['rows']
        (build / 'progress.json').write_text(json.dumps(out, indent=1))


if __name__ == '__main__':
    main()
