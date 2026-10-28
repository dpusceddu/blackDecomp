#!/usr/bin/env python3
"""Write the self-hosted progress badges (progress/) and the progress table and source facts in docs/status.md.

Metric source: `tools/progress.py --libraries`, which computes objdiff's definition of code, matched function bytes /
total function bytes, from the function extents tools/objdiff.py uses (no padding, no orphan pieces). The figures need only
the build, not objdiff-cli, and the overall ones equal `ninja report`. A function is matched when a split compiles it (no
INCLUDE_ASM marker in its TU file), which the build's `OK` guarantees byte-identical. When a current objdiff report exists,
progress.py fails if its matched functions or totals differ (docs/progress-reports.md), so `ninja badges` cannot publish
numbers that disagree with it. Libraries are by address (tools/build/layout.py); the image measure stays in `ninja progress`.

Usage: badges.py [SLUG]       runs progress.py (default SLUS_213.76 only), then writes
         progress/code.json, progress/functions.json   shields.io endpoint files (share of code bytes / of functions)
         build/<GAME_ID>/badges/<library>.json        the same for one library (ignored)
       and refreshes the table and the two measures between the progress markers of docs/status.md and the facts about the
       sources between the facts markers of docs/status.md. Every progress number in the documentation comes from here.
Maintainer tool: contributors do not commit progress/ or the generated status sections (the maintainer regenerates them after merging, so
pull requests never conflict on them). The output has no timestamps, so an unchanged progress leaves Git clean.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build')]
import preflight
LIBRARIES = ['game', 'kynapse', 'rw_core', 'rw_audio', 'animation', 'physics', 'apt', 'sony', 'libc']
BEGIN, END = '<!-- progress:begin (tools/badges.py) -->', '<!-- progress:end -->'
FACTS_BEGIN, FACTS_END = '<!-- facts:begin (tools/badges.py) -->', '<!-- facts:end -->'
COLORS = [(5, 'red'), (15, 'orange'), (30, 'yellow'), (50, 'yellowgreen'), (75, 'green')]


def color(percent):
    """shields.io color for a percentage: red below 5, orange below 15, yellow below 30, yellowgreen below 50, green below 75."""
    return next((c for limit, c in COLORS if percent < limit), 'brightgreen')


def pct(part, whole):
    return 100.0 * part / whole if whole else 0.0


def badge(label, percent):
    shown = '%.1f' % percent  # color follows the displayed value, so "15.0%" is never colored as below 15
    return dict(schemaVersion=1, label=label, message=shown + '%', color=color(float(shown)))


def table(libs):
    """Markdown table with one row per library and a total, from {library: {functions, matched_functions, bytes, matched_bytes}}."""
    rows = ['| Library | Functions matched | Share | Code matched (bytes) | Share |', '| --- | ---: | ---: | ---: | ---: |']
    total = dict(functions=0, matched_functions=0, bytes=0, matched_bytes=0)
    for name in LIBRARIES + sorted(set(libs) - set(LIBRARIES)):
        r = libs.get(name)
        if not r:
            continue
        for k in total:
            total[k] += r[k]
        rows.append('| %s | %s / %s | %.1f %% | %s / %s | %.1f %% |' % (
            name, format(r['matched_functions'], ','), format(r['functions'], ','), pct(r['matched_functions'], r['functions']),
            format(r['matched_bytes'], ','), format(r['bytes'], ','), pct(r['matched_bytes'], r['bytes'])))
    r = total
    rows.append('| **Total** | **%s / %s** | **%.1f %%** | **%s / %s** | **%.1f %%** |' % (
        format(r['matched_functions'], ','), format(r['functions'], ','), pct(r['matched_functions'], r['functions']),
        format(r['matched_bytes'], ','), format(r['bytes'], ','), pct(r['matched_bytes'], r['bytes'])))
    return '\n'.join(rows), total


def replace_between(text, new, begin=BEGIN, end=END):
    a, b = text.find(begin), text.find(end)
    if a < 0 or b < a:
        return None
    return text[:a + len(begin)] + '\n\n' + new + '\n\n' + text[b:]


def measures(data):
    """One paragraph with both measures: objdiff's (functions and code) and the image's (every function start and byte)."""
    code, image = data['code'], data['rows']['ALL']
    orphans = image['functions'] - code['functions']
    return ('Functions as objdiff counts them: %s of %s (%.1f %%); code: %s of %s bytes (%.2f %%). Image measure (`ninja progress`): '
            '%s of %s function starts and %s of %s bytes (%.2f %%), which includes the %s orphan pieces and the alignment padding.' % (
                format(code['matched_functions'], ','), format(code['functions'], ','), pct(code['matched_functions'], code['functions']),
                format(code['matched_bytes'], ','), format(code['bytes'], ','), pct(code['matched_bytes'], code['bytes']),
                format(image['source_functions'], ','), format(image['functions'], ','), format(image['source_bytes'], ','),
                format(image['bytes'], ','), pct(image['source_bytes'], image['bytes']), format(orphans, ',')))


def source_facts(slug):
    """Markdown bullets about the sources, from the split list, the source files and the TU map (no hand-written numbers)."""
    sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build')]
    import re
    import include_asm
    import splits as S
    import units as U
    splits = S.load_splits(slug)
    files = sorted({s.src for s in splits})
    asm = nm_files = nm_blocks = sn_min6 = 0
    for src in files:
        text = (ROOT / src).read_text()
        asm += len(include_asm.markers(text, set()))
        blocks = len(re.findall(r'^\s*#\s*ifdef\s+NON_MATCHING\b', text, re.M))
        nm_files += bool(blocks)
        nm_blocks += blocks
    sn_min6 = sum(1 for s in splits if s.assembler == 'sn-min6')
    units = U.load_units(variant=slug)
    exact_files = len({u['source'] for u in units if any(f['status'] == 'source' for f in u['functions'])})
    lines = ['- The split list has %s entries for %s source files; %s of the files hold recovered functions.' % (
                 format(len(splits), ','), format(len(files), ','), format(exact_files, ',')),
             '- %s functions are still `INCLUDE_ASM` lines (one per function, in the one file that owns it).' % format(asm, ','),
             '- %s files contain %s `#ifdef NON_MATCHING` blocks (drafts that do not match yet, plus blocks that only carry includes and notes).' % (
                 format(nm_files, ','), format(nm_blocks, ',')),
             '- %s split entries select `assembler: sn-min6`.' % format(sn_min6, ',')]
    tus = ROOT / 'build' / slug / 'tus.yaml'
    if tus.exists():
        import yaml
        summary = yaml.safe_load(tus.read_text())['summary']
        share = summary['by_confidence']
        lines.append('- The TU map has %s translation units; confidence of its boundaries by bytes of `.text`: %s.' % (
            format(summary['tus'], ','), ', '.join('`%s` %.1f %%' % (k, 100 * share[k]['share']) for k in ('exact', 'high', 'medium', 'low') if k in share)))
    return '\n'.join(lines)


def write_if_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def main():
    slug = next((a for a in sys.argv[1:] if not a.startswith('-')), 'SLUS_213.76')
    if slug != 'SLUS_213.76':
        raise SystemExit('badges are produced for SLUS_213.76 only')
    preflight.require(slug, build=('placement.json', 'layout.json'))
    if '--no-progress' not in sys.argv:
        subprocess.run([sys.executable, str(ROOT / 'tools/progress.py'), slug, '--libraries'], check=True, stdout=subprocess.DEVNULL)
    data = json.loads((ROOT / 'build' / slug / 'progress.json').read_text())
    libs = data['code_by_library']
    md, total = table(libs)
    md = md + '\n\n' + measures(data)
    out = ROOT / 'progress'
    libraries = ROOT / 'build' / slug / 'badges'
    libraries.mkdir(parents=True, exist_ok=True)

    def dump(path, obj):
        write_if_changed(path, json.dumps(obj, indent=2) + '\n')

    dump(out / 'code.json', badge('code', pct(total['matched_bytes'], total['bytes'])))
    dump(out / 'functions.json', badge('functions', pct(total['matched_functions'], total['functions'])))
    for name, r in libs.items():
        dump(libraries / ('%s.json' % name), badge(name, pct(r['matched_bytes'], r['bytes'])))
    status = ROOT / 'docs' / 'status.md'
    new = replace_between(status.read_text(), md)
    if new is None:
        raise SystemExit('docs/status.md has no progress markers; cannot publish progress')
    new = replace_between(new, source_facts(slug), FACTS_BEGIN, FACTS_END)
    if new is None:
        raise SystemExit('docs/status.md has no facts markers; cannot publish source facts')
    write_if_changed(status, new)
    print('code %.1f %%  functions %.1f %%  (%d/%d functions, %d/%d bytes)' % (
        pct(total['matched_bytes'], total['bytes']), pct(total['matched_functions'], total['functions']),
        total['matched_functions'], total['functions'], total['matched_bytes'], total['bytes']))


if __name__ == '__main__':
    preflight.guard(main)
