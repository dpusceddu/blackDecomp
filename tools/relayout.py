#!/usr/bin/env python3
"""Lay out src/ as src/<library>/<name>.c|cpp and record each unit's library, provenance and evidence tier in config/units.yaml.

  relayout.py plan     print the moves and the per-library counts, change nothing
  relayout.py apply    move the files, update config/units.yaml and rewrite the path mentions in the text files

Rules (tools/layout.py): the library comes from the TU map for the unit's first function; a file is named after the
descriptive name it already had (wave suffixes dropped) or else after its TU (`tu_<address>`, plus `_<unit address>` when the
unit does not start the TU). Sources that no unit uses (nonmatching drafts) go to src/<library>/nonmatching/. A file that is
already at src/<library>/<name> stays, so the script can be re-run after other tools added files. The provenance
(`auto`, `imported`, `manual`, `equivalent`) is read from the old directory and the `origin` label once and then kept as a field.
`origin` keeps its meaning as the progress-report label.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse
import collections
import os
import re
import subprocess
from pathlib import Path

import yaml

import layout

ROOT = layout.ROOT
HEX6 = re.compile(r'(?<![0-9a-fA-F])([0-9a-f]{6})(?![0-9a-fA-F])')
OLD_LIB_HINT = {'animation': 'animation', 'kynapse': 'kynapse', 'physics': 'physics', 'rwa_ee': 'rw_audio',
                'renderware_core': 'rw_core', 'context': 'kynapse', 'ps2': 'game', 'mod': 'game', 'campaign': 'game',
                'game': 'game', 'classes': 'game'}
TEXT_SUFFIXES = {'.h', '.hpp', '.c', '.cpp', '.md', '.py', '.json', '.txt', '.yaml', '.inc', '.s', '.ld'}
TIER_RANK = {'draft': 0, 'equivalent': 1, 'exact': 2}


HEADER_DIRS = {'renderware_core': 'rw_core', 'rwa_ee': 'rw_audio'}      # include/ directories named after the library dirs


def rename_header_dirs():
    """include/<old>/ -> include/<library>/ and the quoted includes that name them; returns the number of files rewritten."""
    changed = 0
    for old, new in HEADER_DIRS.items():
        if (ROOT / 'include' / old).is_dir():
            os.rename(ROOT / 'include' / old, ROOT / 'include' / new)
    paths = [q for d in ('src', 'include', 'docs', 'tools') for q in (ROOT / d).rglob('*')] + list(ROOT.glob('*.md'))
    for p in paths:
        if p.name == 'relayout.py' or p.suffix not in TEXT_SUFFIXES or not p.is_file():
            continue
        s = p.read_text()
        t = s
        for old, new in HEADER_DIRS.items():
            t = t.replace('include "%s/' % old, 'include "%s/' % new).replace('include/%s/' % old, 'include/%s/' % new)
        if t != s:
            p.write_text(t)
            changed += 1
    return changed


def clean_stem(stem):
    stem = re.sub(r'_wave\d+', '', stem)
    return re.sub(r'^w\d+_', '', stem)


def descriptive(old):
    """The stem to keep from the old file name, or None when the old name carries no information."""
    p = Path(old)
    parts = p.relative_to('src').parts
    if parts[0] in ('auto', 'tu'):
        return None
    stem = clean_stem(p.stem)
    if layout.TU_STEM.match(stem) or re.fullmatch(r'[0-9a-f]{6}(_[0-9a-f]{6})?', stem):
        stem = None
    if len(parts) > 2 and parts[-2].startswith('tu_'):        # src/animation/tu_34eae0/advance.c: a split unit of a TU
        return parts[-2] + ('_' + stem if stem else '')
    return stem


def provenance(unit, old):
    top = Path(old).relative_to('src').parts[0]
    origin = unit.get('origin', '')
    if top == 'equivalent':
        return 'equivalent'
    if top == 'auto' or origin.startswith('auto'):
        return 'auto'
    if origin in ('kynapse', 'game', 'vector') and unit['name'].split('_')[0] in ('kynapse', 'game'):
        return 'imported'
    return 'manual'


def unit_tier(unit):
    best = 'draft'
    for f in unit['functions']:
        tier = 'exact' if f.get('status') == 'source' else (f.get('evidence') or {}).get('tier', 'draft')
        if TIER_RANK[tier] > TIER_RANK[best]:
            best = tier
    return best


def num(v):
    return int(v, 0) if isinstance(v, str) else int(v)


def conforming(path, libs):
    parts = Path(path).relative_to('src').parts
    return (len(parts) == 2 and parts[0] in libs) or (len(parts) == 3 and parts[0] in libs and parts[1] == 'nonmatching')


def build_plan(doc):
    units = doc['units']
    by_source = collections.defaultdict(list)
    for u in units:
        by_source[u['source']].append(u)
    files = sorted(str(p.relative_to(ROOT)) for p in (ROOT / 'src').rglob('*') if p.is_file() and p.suffix in ('.c', '.cpp'))
    old_dir_libs = collections.defaultdict(collections.Counter)
    for src, us in by_source.items():
        old_dir_libs[os.path.dirname(src)][layout.library_of(num(us[0]['functions'][0]['addr']))] += 1
    nm_refs = {}                             # sources only named by a function's `nonmatching` evidence -> its address
    for u in units:
        for f in u['functions']:
            if (f.get('nonmatching') or {}).get('source'):
                nm_refs.setdefault(f['nonmatching']['source'], num(f['addr']))
    taken, plan = {}, {}

    def claim(path, old):
        if path in taken and taken[path] != old:
            return False
        taken[path] = old
        return True

    pending = []
    for old in files:                       # first pass: files that already conform keep their place
        us = by_source.get(old)
        parts = Path(old).relative_to('src').parts
        if us:
            lib = layout.library_of(num(us[0]['functions'][0]['addr']))
            libs = {lib, 'kynapse'} if lib == 'linkonce' else {lib}
            keep = len(parts) == 2 and parts[0] in libs
        else:
            keep = len(parts) == 3 and parts[0] in layout.LIBRARIES and parts[1] == 'nonmatching'
        if keep and claim(old, old):
            plan[old] = old
        else:
            pending.append(old)

    for old in pending:
        us = by_source.get(old)
        suffix = Path(old).suffix
        stem = descriptive(old)
        if us:
            addr = num(us[0]['functions'][0]['addr'])
            lib = layout.library_of(addr)
            if lib == 'linkonce' and old.startswith(('src/kynapse/', 'src/auto/kynapse/')):
                lib = 'kynapse'               # link-once code of the Kynapse area stays with its library
            cands = []
            if stem:
                cands = ['src/%s/%s%s' % (lib, stem, suffix),
                         'src/%s/%s_%06x%s' % (lib, stem, addr, suffix)]
            cands.append(layout.source_path(addr, suffix).replace('src/%s/' % layout.library_of(addr), 'src/%s/' % lib))
            cands.append('src/%s/%s_%s%s' % (lib, layout.stem_for(addr), re.sub(r'\W', '_', unit_key(us[0])), suffix))
        else:
            lib = layout.library_of(nm_refs[old]) if old in nm_refs else None
            m = None if lib else HEX6.search(Path(old).stem)
            if not lib and m and 0x100000 <= int(m.group(1), 16) < 0x400000:
                lib = layout.library_of(int(m.group(1), 16))
            if not lib:
                counts = old_dir_libs.get(os.path.dirname(old))
                lib = counts.most_common(1)[0][0] if counts else None
            if not lib:
                lib = OLD_LIB_HINT.get(Path(old).relative_to('src').parts[0], 'game')
            if lib == 'linkonce':
                lib = 'kynapse' if Path(old).relative_to('src').parts[0] == 'kynapse' else 'game'
            parts = Path(old).relative_to('src').parts
            stem = clean_stem(Path(old).stem)
            tag = '_'.join(p for p in parts[:-1] if p not in ('auto', 'tu', lib))
            cands = ['src/%s/nonmatching/%s_%s%s' % (lib, tag, stem, suffix) if tag else None,
                     'src/%s/nonmatching/%s%s' % (lib, stem, suffix)]
            cands = [c for c in cands if c]
        for c in cands:
            if claim(c, old):
                plan[old] = c
                break
        else:
            raise SystemExit('no free name for ' + old)
    return plan, by_source


def unit_key(u):
    return u['name']


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('mode', choices=['plan', 'apply'])
    args = ap.parse_args()
    path = ROOT / 'config/units.yaml'
    text = path.read_text()
    header = text[:text.index('variant:')]
    doc = yaml.safe_load(text)
    plan, by_source = build_plan(doc)
    moves = {o: n for o, n in plan.items() if o != n}
    counts = collections.Counter(Path(n).parts[1] for n in plan.values())
    print('%d files, %d to move' % (len(plan), len(moves)))
    for lib, n in sorted(counts.items()):
        print('  src/%-10s %5d files' % (lib, n))
    if args.mode == 'plan':
        for o, n in list(moves.items())[:40]:
            print('   %s -> %s' % (o, n))
        return

    for o, n in moves.items():
        (ROOT / n).parent.mkdir(parents=True, exist_ok=True)
        os.rename(ROOT / o, ROOT / n)

    # units.yaml: sources, nonmatching sources, and the new fields
    for u in doc['units']:
        old = u['source']
        new = plan[old]
        if 'provenance' not in u:
            u['provenance'] = provenance(u, old)
        u['source'] = new
        u['library'] = Path(new).parts[1]
        u['tier'] = unit_tier(u)
        for f in u['functions']:
            nm = f.get('nonmatching')
            if nm and nm.get('source') in plan:
                nm['source'] = plan[nm['source']]
        ordered = {}
        for k in ('name', 'source', 'library', 'provenance', 'tier', 'origin'):
            if k in u:
                ordered[k] = u[k]
        ordered.update({k: v for k, v in u.items() if k not in ordered})
        u.clear()
        u.update(ordered)
    path.write_text(header + yaml.safe_dump(doc, sort_keys=False, width=140))

    # path mentions in the other tracked text files (include comments, source comments, docs, harness plan)
    if moves:
        pattern = re.compile(r'(?<![A-Za-z0-9_./-])(' + '|'.join(re.escape(o) for o in sorted(moves, key=len, reverse=True)) + r')(?![A-Za-z0-9_])')
        tracked = subprocess.run(['git', 'ls-files'], cwd=ROOT, capture_output=True, text=True, check=True).stdout.split('\n')
        changed = 0
        for rel in tracked:
            p = ROOT / rel
            if not rel or rel in ('config/units.yaml',) or rel.startswith(('tests/', '.venv')) or p.suffix not in TEXT_SUFFIXES or not p.is_file():
                continue
            if rel in moves:
                rel = moves[rel]
                p = ROOT / rel
            try:
                s = p.read_text()
            except (UnicodeDecodeError, OSError):
                continue
            t = pattern.sub(lambda m: moves[m.group(1)], s)
            if t != s:
                p.write_text(t)
                changed += 1
        print('rewrote path mentions in %d files' % changed)
    print('renamed header directories, rewrote includes in %d files' % rename_header_dirs())
    for d, _, _ in sorted(os.walk(ROOT / 'src'), key=lambda x: -len(x[0])):
        if not os.listdir(d):
            os.rmdir(d)


if __name__ == '__main__':
    main()
