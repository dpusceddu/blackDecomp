#!/usr/bin/env python3
"""Write the self-hosted progress badges and the per-library table (progress/) from the exact progress data.

Metric source: `tools/progress.py --libraries`, not the objdiff report. `ninja progress` measures the finished image: a
function counts when a split compiles it (no INCLUDE_ASM marker in its TU file), which the build's `OK` guarantees byte-identical,
and bytes are the original spans up to the next function. It needs only the build (no objdiff-cli download), covers
every library directory of src/, and is the number the README and docs/status.md quote. The objdiff report
(`ninja report`) counts per object and differs slightly (docs/progress-reports.md); it is not used here.

Usage: badges.py [SLUG]       runs progress.py (default SLUS_213.76 only), then writes
         progress/code.json, progress/functions.json   shields.io endpoint files (share of .text bytes / of functions)
         progress/libraries/<library>.json             the same for one library
         progress/summary.md                           per-library table
       and refreshes the table between the progress markers of README.md.
Commit progress/ and README.md with the change that moved the numbers. The output has no timestamps, so an unchanged
progress leaves Git clean.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LIBRARIES = ['game', 'kynapse', 'rw_core', 'rw_audio', 'animation', 'physics', 'apt', 'sony', 'libc', 'linkonce']
BEGIN, END = '<!-- progress:begin (tools/badges.py) -->', '<!-- progress:end -->'
COLORS = [(5, 'red'), (15, 'orange'), (30, 'yellow'), (50, 'yellowgreen'), (75, 'green')]


def color(percent):
    """shields.io color for a percentage: red below 5, orange below 15, yellow below 30, yellowgreen below 50, green below 75."""
    return next((c for limit, c in COLORS if percent < limit), 'brightgreen')


def pct(part, whole):
    return 100.0 * part / whole if whole else 0.0


def badge(label, percent):
    return dict(schemaVersion=1, label=label, message='%.1f%%' % percent, color=color(percent))


def table(libs):
    """Markdown table with one row per library and a total, from {library: {functions, source_functions, bytes, source_bytes}}."""
    rows = ['| Library | Functions from source | Share | Bytes from source | Share |', '| --- | ---: | ---: | ---: | ---: |']
    total = dict(functions=0, source_functions=0, bytes=0, source_bytes=0)
    for name in LIBRARIES + sorted(set(libs) - set(LIBRARIES)):
        r = libs.get(name)
        if not r:
            continue
        for k in total:
            total[k] += r[k]
        rows.append('| %s | %s / %s | %.1f %% | %s / %s | %.1f %% |' % (
            name, format(r['source_functions'], ','), format(r['functions'], ','), pct(r['source_functions'], r['functions']),
            format(r['source_bytes'], ','), format(r['bytes'], ','), pct(r['source_bytes'], r['bytes'])))
    r = total
    rows.append('| **Total** | **%s / %s** | **%.1f %%** | **%s / %s** | **%.1f %%** |' % (
        format(r['source_functions'], ','), format(r['functions'], ','), pct(r['source_functions'], r['functions']),
        format(r['source_bytes'], ','), format(r['bytes'], ','), pct(r['source_bytes'], r['bytes'])))
    return '\n'.join(rows), total


def replace_between(text, new):
    a, b = text.find(BEGIN), text.find(END)
    if a < 0 or b < a:
        return None
    return text[:a + len(BEGIN)] + '\n\n' + new + '\n\n' + text[b:]


def write_if_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def main():
    slug = next((a for a in sys.argv[1:] if not a.startswith('-')), 'SLUS_213.76')
    if slug != 'SLUS_213.76':
        raise SystemExit('badges are produced for SLUS_213.76 only')
    subprocess.run([sys.executable, str(ROOT / 'tools/progress.py'), slug, '--libraries'], check=True, stdout=subprocess.DEVNULL)
    data = json.loads((ROOT / 'build' / slug / 'progress.json').read_text())
    libs = data['by_library']
    md, total = table(libs)
    out = ROOT / 'progress'
    (out / 'libraries').mkdir(parents=True, exist_ok=True)

    def dump(path, obj):
        write_if_changed(path, json.dumps(obj, indent=2) + '\n')

    dump(out / 'code.json', badge('code', pct(total['source_bytes'], total['bytes'])))
    dump(out / 'functions.json', badge('functions', pct(total['source_functions'], total['functions'])))
    for name, r in libs.items():
        dump(out / 'libraries' / ('%s.json' % name), badge(name, pct(r['source_bytes'], r['bytes'])))
    write_if_changed(out / 'summary.md',
                     '# Progress (SLUS_213.76)\n\nFunctions and bytes of `.text` provided by recovered source that rebuilds the '
                     'executable byte for byte, per library directory of `src/`. Produced by `ninja badges` '
                     '(`tools/badges.py`, from `tools/progress.py`); do not edit.\n\n' + md + '\n')
    readme = ROOT / 'README.md'
    new = replace_between(readme.read_text(), md)
    if new is None:
        print('note: README.md has no progress markers; table not updated', file=sys.stderr)
    else:
        write_if_changed(readme, new)
    print('code %.1f %%  functions %.1f %%  (%d/%d functions, %d/%d bytes)' % (
        pct(total['source_bytes'], total['bytes']), pct(total['source_functions'], total['functions']),
        total['source_functions'], total['functions'], total['source_bytes'], total['bytes']))


if __name__ == '__main__':
    main()
