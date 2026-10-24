#!/usr/bin/env python3
"""Report how much of .text is provided by source (tools/build/units.py: functions the TU files do not mark INCLUDE_ASM), overall and by region.

Regions come from config/SLUS_213.76/function_regions.txt (PS2 address -> game, kynapse, animation, physics or other), derived from an
Xbox-to-PS2 counterpart map (`progress.py --refresh MAP.json` rewrites it; the committed file is enough to build and report). An unmapped function takes the
region of its neighbours when both sides agree, otherwise it is `unclassified`. Regions are therefore approximate;
the overall number is exact.
A function counts as source when its split compiles it (no INCLUDE_ASM marker), which the build's OK keeps identical to the target.
Headline ("code"): objdiff's definition, matched function bytes / total function bytes, with the function extents objdiff
uses (tools/objdiff.py code_size: up to the function's endlabel, no alignment padding, orphan pieces left out). It equals
`ninja report`'s matched_code / total_code. Secondary ("image"): bytes of the finished image, spans up to the next
function including padding and orphans. When build/<GAME_ID>/report.json is current, the exact functions are checked
against the functions objdiff counts as matched and the run fails if they differ (see docs/progress-reports.md).
Usage: progress.py [SLUG]       writes build/<GAME_ID>/progress.json and prints a table
       progress.py --check      fail when no objdiff report exists to compare with (the check always runs when a current one does)
       progress.py --libraries   also print the totals per library directory of src/
       progress.py --tus [N]     also list the N (default 15) partially done translation units with most bytes still in assembly
When config/tus.yaml exists (tools/maint/tus.py) the report adds the progress by TU: complete TUs (every function from source),
partially done ones and bytes per TU, by confidence of the TU boundaries.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, struct, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
from units import load_units

ROOT = Path(__file__).resolve().parents[1]
REGIONS = ROOT / 'config/SLUS_213.76/function_regions.txt'


def refresh_regions(counterpart_map):
    """Rewrite config/SLUS_213.76/function_regions.txt (address, region) from an Xbox-to-PS2 counterpart map (json with `pairs`), optional input."""
    pairs = json.loads(Path(counterpart_map).read_text())['pairs']
    rows = sorted({(int(p['ps2'], 16), p['region']) for p in pairs})
    REGIONS.write_text('# PS2 function address -> region (game, kynapse, animation, physics, other), from the\n'
                       '# optional Xbox-to-PS2 counterpart map (discovery leads, not byte-compared); tools/progress.py --refresh\n' +
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


def orphan_pieces(slug, fs):
    """Addresses of the functions that are orphan pieces: `<one non-branch instruction>; nop` repeated (see tools/maint/boundaries.py)."""
    from elfinfo import Elf
    boot = json.loads((ROOT / 'config/variants.json').read_text())[slug]['boot']
    elf = Elf((ROOT / 'orig' / slug / boot).read_bytes())
    sec = elf.section('.text')
    data = elf.content(sec)

    def control(x):
        op = x >> 26
        return (op in (1, 2, 3, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 0 and (x & 0x3F) in (8, 9, 12, 13))
                or (op in (0x10, 0x11, 0x12) and (x >> 21) & 0x1F == 8))

    out = set()
    for f in fs:
        lo = f['addr'] - sec['addr']
        words = list(struct.unpack('<%dI' % ((f['end'] - f['addr']) // 4), data[lo:lo + f['end'] - f['addr']]))
        while words and words[-1] == 0:                 # alignment padding after the last piece
            words = words[:-1]
        if words and all((w == 0) if i % 2 else (w != 0 and not control(w)) for i, w in enumerate(words)):
            out.add(f['addr'])
    return out


def code_extents(slug, fs, units):
    """{address: code bytes} of every function objdiff reports: the extent up to the endlabel of its split assembly
    (tools/objdiff.py code_size), orphan pieces left out. A recovered function takes its size from its unit as there."""
    import objdiff
    orphans = orphan_pieces(slug, fs)
    unit_size = {f['addr']: f.get('size') for u in units for f in u['functions'] if f.get('status') == 'source'}
    sizes = {}
    for f in fs:
        if f['addr'] in orphans:
            continue
        span = unit_size.get(f['addr']) or f['end'] - f['addr']
        asm = ROOT / 'asm' / slug / 'nonmatchings' / ('func_%08X.s' % f['addr'])
        sizes[f['addr']] = objdiff.code_size(asm.read_text(), f['addr'], span) if asm.is_file() else span
    return sizes


def code_totals(sizes, matched, library):
    """objdiff's code measure: ({functions, matched_functions, bytes, matched_bytes}, {library: the same}) from
    {address: bytes}, the set of matched addresses and a function address -> library name."""
    def row():
        return dict(functions=0, matched_functions=0, bytes=0, matched_bytes=0)
    total, libs = row(), {}
    for addr, size in sizes.items():
        for r in (total, libs.setdefault(library(addr), row())):
            r['functions'] += 1
            r['bytes'] += size
            if addr in matched:
                r['matched_functions'] += 1
                r['matched_bytes'] += size
    return total, libs


def report_matches(report):
    """({addresses of the functions objdiff counts as matched}, {address: size}) from a report.json; functions are `func_XXXXXXXX`."""
    matched, sizes = set(), {}
    for unit in report['units']:
        for f in unit.get('functions', []):
            addr = int(f['name'][len('func_'):], 16)
            sizes[addr] = int(f['size'])
            if f.get('fuzzy_match_percent', 0) >= 100.0:
                matched.add(addr)
    return matched, sizes


def agreement_problems(exact, total, report):
    """What differs between the image check (the exact functions and the code measure computed here) and an objdiff
    report: the functions on one side only, and any difference in the headline figures. An empty list means they agree."""
    matched, sizes = report_matches(report)
    problems = []
    for what, missing in (('exact in the image but not matched by objdiff', exact - matched),
                          ('matched by objdiff but not exact in the image', matched - exact)):
        if missing:
            problems.append('%d functions %s: %s' % (len(missing), what, ', '.join('func_%08X' % a for a in sorted(missing)[:10])
                                                     + (' ...' if len(missing) > 10 else '')))
    m = report['measures']
    for key, mine in (('total_code', total['bytes']), ('matched_code', total['matched_bytes']),
                      ('total_functions', total['functions']), ('matched_functions', total['matched_functions'])):
        if int(m[key]) != mine:
            problems.append('%s: report %s, computed %d' % (key, m[key], mine))
    return problems


def check_report(slug, build, exact, total, required):
    """Compare with build/<GAME_ID>/report.json when it is current (not older than the linked image); fail loudly on a difference."""
    path = build / 'report.json'
    image = build / 'linked.elf'
    if not path.is_file():
        if required:
            raise SystemExit('no objdiff report (%s); run `ninja report` first' % path.relative_to(ROOT))
        return
    if image.is_file() and path.stat().st_mtime < image.stat().st_mtime:
        if required:
            raise SystemExit('the objdiff report is older than the build; run `ninja report` again')
        print('\nnote: build/%s/report.json is older than the build; agreement check skipped' % slug)
        return
    problems = agreement_problems(exact, total, json.loads(path.read_text()))
    if problems:
        raise SystemExit('AGREEMENT FAILED: ninja progress and the objdiff report disagree:\n  ' + '\n  '.join(problems))
    print('\nagreement: the %d exact functions are the functions objdiff matches; code %d / %d bytes as in the report'
          % (len(exact), total['matched_bytes'], total['bytes']))


def tu_report(slug, fs, spans, source, top):
    """Progress by translation unit (config/tus.yaml): rows by confidence and the TUs closest to completion."""
    path = ROOT / 'config/tus.yaml'
    if not path.exists() or slug != 'SLUS_213.76':
        return None
    import bisect, yaml
    tus = yaml.safe_load(path.read_text())['tus']
    starts = [int(t['text'][0], 16) for t in tus]
    rows = [dict(name=t['name'], kind=t['kind'], conf=t['confidence'], lib=t['library'], lo=starts[k], functions=0,
                 source_functions=0, bytes=0, source_bytes=0) for k, t in enumerate(tus)]
    orphan = orphan_pieces(slug, fs)   # unreferenced `<instruction>; nop` runs stay assembly and do not count against a TU
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
    import layout
    for r in rows:
        lib = r['lib'] or '?'
        if lib == 'linkonce':          # a link-once copy is counted with the library that owns it (config/SLUS_213.76/inline_owners.txt)
            lib = 'inline>' + layout.library_of(r['lo'])
        for key in ('ALL', 'conf: ' + r['conf'], 'kind: ' + r['kind'], 'lib: ' + lib):
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
        k = sys.argv.index('--refresh')
        if k + 1 >= len(sys.argv):
            raise SystemExit('--refresh needs the path of the counterpart map json')
        return refresh_regions(sys.argv[k + 1])
    top = 0
    if '--tus' in sys.argv:
        k = sys.argv.index('--tus')
        top = int(sys.argv[k + 1]) if k + 1 < len(sys.argv) and sys.argv[k + 1].isdigit() else 15
    slug = next((a for a in sys.argv[1:] if not a.startswith('-') and not a.isdigit()), 'SLUS_213.76')
    build = ROOT / 'build' / slug
    fs = json.loads((build / 'placement.json').read_text())['functions']
    layout = json.loads((ROOT / 'config' / slug / 'layout.json').read_text())
    text = next(s for s in layout['sections'] if s['name'] == '.text')
    spans = [(fs[i + 1]['addr'] if i + 1 < len(fs) else text['addr'] + text['orig_size']) - fs[i]['addr']
             for i in range(len(fs))]
    source = {}
    equivalent = set()
    units = load_units(variant=slug)
    for u in units:
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
    import layout
    code, code_libs = code_totals(code_extents(slug, fs, units), set(source), layout.library_of) \
        if slug == 'SLUS_213.76' else (None, None)
    out = dict(text_bytes=text['orig_size'], regions_from_map=mapped, rows=rows, evidence_tiers=tiers)
    if code:
        out['code'], out['code_by_library'] = code, code_libs
    (build / 'progress.json').write_text(json.dumps(out, indent=1))
    if code:
        print('code (objdiff definition: matched function bytes / total function bytes)')
        print('  functions %d / %d (%.2f%%)   code bytes %d / %d (%.2f%%)\n' % (
            code['matched_functions'], code['functions'], 100.0 * code['matched_functions'] / code['functions'],
            code['matched_bytes'], code['bytes'], 100.0 * code['matched_bytes'] / code['bytes']))
        print('image measure (secondary: bytes of the final image, alignment padding and orphan pieces included)')
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
    if '--libraries' in sys.argv and slug == 'SLUS_213.76':
        import layout
        libs = {}
        for f, span in zip(fs, spans):
            r = libs.setdefault(layout.library_of(f['addr']), dict(functions=0, source_functions=0, bytes=0, source_bytes=0))
            r['functions'] += 1
            r['bytes'] += span
            if f['addr'] in source:
                r['source_functions'] += 1
                r['source_bytes'] += span
        out['by_library'] = libs
        print('\nby library directory (src/<library>, tools/build/layout.py)')
        for lib, r in sorted(libs.items()):
            print('%-12s %7d %7d %5.1f%%   %9d %9d %5.1f%%' % (lib, r['functions'], r['source_functions'],
                  100.0 * r['source_functions'] / r['functions'], r['bytes'], r['source_bytes'], 100.0 * r['source_bytes'] / max(r['bytes'], 1)))
    if code:
        check_report(slug, build, set(source), code, '--check' in sys.argv)
    tur = tu_report(slug, fs, spans, source, top)
    if tur:
        out['by_tu'] = tur['rows']
        (build / 'progress.json').write_text(json.dumps(out, indent=1))


if __name__ == '__main__':
    main()
