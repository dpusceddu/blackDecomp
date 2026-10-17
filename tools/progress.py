#!/usr/bin/env python3
"""Report how much of .text is provided by source (config/units.yaml, status source), overall and by region.

Regions come from the Xbox-to-PS2 counterpart map of the companion project, when a copy is configured (the map's
`region` field: game, kynapse, animation, physics, other), else from `config/regions.json` (a copy of address ->
region pairs; ignored if absent). An unmapped function takes the region of its neighbours when both sides agree,
otherwise it is `unclassified`. Regions are therefore approximate; the overall number is exact.
A function counts as source when its unit lists it with `status: source` and its object replaced the assembly in the
last link (build/<slug>/objects.json); bytes are the original byte span of the function (to the next function).
Usage: progress.py [SLUG]       writes build/<slug>/progress.json and prints a table
"""
import json, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from units import load_units

ROOT = Path(__file__).resolve().parents[1]
MAP_CANDIDATES = [ROOT / 'config/xbox_ps2_map.json', ROOT.parent / 'the counterpart map']


def regions(addrs):
    reg = {}
    for p in MAP_CANDIDATES:
        if p.exists():
            for pair in json.loads(p.read_text())['pairs']:
                reg[int(pair['ps2'], 16)] = pair['region']
            break
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


def main():
    slug = sys.argv[1] if len(sys.argv) > 1 else 'usa-retail'
    build = ROOT / 'build' / slug
    fs = json.loads((build / 'placement.json').read_text())['functions']
    layout = json.loads((ROOT / 'config' / ('%s.layout.json' % json.loads(
        (ROOT / 'config/variants.json').read_text())[slug]['boot'])).read_text())
    text = next(s for s in layout['sections'] if s['name'] == '.text')
    spans = [(fs[i + 1]['addr'] if i + 1 < len(fs) else text['addr'] + text['orig_size']) - fs[i]['addr']
             for i in range(len(fs))]
    source = {}
    for u in load_units():
        for f in u['functions']:
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
    out = dict(text_bytes=text['orig_size'], regions_from_map=mapped, rows=rows)
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


if __name__ == '__main__':
    main()
