#!/usr/bin/env python3
"""Decide which library owns each link-once copy (compiler-emitted inline and template code) and write the owner list.

The linker keeps one copy of an inline function or template instantiation for the whole program, so the copies of the
original build sit in a block behind the regular code (0x383b50..0x396f48 in USA retail), in link order, grouped by the object
file that emitted them first. This tool assigns every copy to a library from evidence in the split assembly, in this order:
`callers` (every caller outside the block, direct or through a vtable slot, lies in one library), `between` (the neighbouring
copies on both sides have one owner and no caller disagrees), `via-inline` (every caller is a copy that already has one owner),
`callees` (the only specific callees are in one library), `vtable` (the other copies in the same vtable have one owner) and `shared` (callers in several libraries and nothing narrower:
the library that comes first in link order). The result is build/SLUS_213.76/inline_owners.txt (ignored, written by `ninja`), one line per run of
copies with one owner and evidence: `0xSTART 0xEND library evidence`, the evidence being the weakest one in the run.
tools/build/layout.py reads it, so progress and new source files follow it; the libraries of the regular code are the hand-edited
config/SLUS_213.76/libraries.txt, and a source file in src/<library>/inline/ is that library's by its directory.

Needs the split assembly (asm/SLUS_213.76/, written by `ninja`).
Usage: linkonce_owners.py [--write]     without --write only print the summary; --write writes build/SLUS_213.76/inline_owners.txt
       linkonce_owners.py --pairs       print `old new` for every src/ file of the block that is not in src/<owner>/inline/ yet
                                        (feed it to tools/studies/relocate_sources.py)
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import bisect, collections, re, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]
import layout

ROOT = layout.ROOT
OUT = ROOT / 'build/SLUS_213.76/inline_owners.txt'
SLUG = 'SLUS_213.76'
ORDER = ['callers', 'between', 'via-inline', 'callees', 'vtable', 'shared']     # strongest first
LINK_ORDER = ['game', 'apt', 'rw_core', 'kynapse', 'rw_audio', 'physics', 'animation']
GENERIC_CALLEE = 20            # a callee with this many callers (allocator, assert helper) says nothing about the owner


def block():
    return layout.linkonce_block()


def analyse():
    lo, hi = block()
    inblock = lambda a: lo <= a < hi
    text = (ROOT / 'asm' / SLUG / 'text.s').read_text()
    funcs = {int(m.group(1), 16): m.group(2) for m in re.finditer(r'glabel func_([0-9A-F]{8})\n(.*?)\nendlabel func_', text, re.S)}
    refs, callees = collections.defaultdict(set), collections.defaultdict(set)
    for f, body in funcs.items():
        for m in re.finditer(r'\b(func|D)_([0-9A-F]{8})\b', body):
            t = int(m.group(2), 16)
            if t != f:
                refs[t].add(f)
                if m.group(1) == 'func':
                    callees[f].add(t)
    labels, words = set(), []
    for line in (ROOT / 'asm' / SLUG / 'data/data.data.s').read_text().split('\n'):
        m = re.match(r'dlabel D_([0-9A-F]{8})', line)
        if m:
            labels.add(int(m.group(1), 16))
            continue
        m = re.match(r'\s*/\* \w+ ([0-9A-F]{8}) \w+ \*/ \.word func_([0-9A-F]{8})', line)
        if m:
            words.append((int(m.group(1), 16), int(m.group(2), 16)))
    users = sorted(t for t in refs if t in labels)          # data labels that code refers to: the vtables' entry points
    copies = sorted(a for a in funcs if inblock(a))
    outside = lambda a: layout.library_of_tu(a)
    votes = {a: collections.Counter() for a in copies}
    for a in copies:
        for g in refs.get(a, ()):
            if not inblock(g):
                votes[a][outside(g)] += 1
    table = collections.defaultdict(set)      # vtable entry point -> copies in its slots
    for slot, f in words:
        if inblock(f):
            i = bisect.bisect_right(users, slot) - 1
            if i >= 0 and slot - users[i] < 0x400:
                table[users[i]].add(f)
                for g in refs[users[i]]:
                    if not inblock(g):
                        votes[f][outside(g)] += 1
    owner, why = {}, {}
    for a in copies:
        if len(votes[a]) == 1:
            owner[a], why[a] = next(iter(votes[a])), 'callers'
    solid = sorted(owner)
    for a in copies:
        if a in owner:
            continue
        i = bisect.bisect_left(solid, a)
        before = owner[solid[i - 1]] if i else None
        after = owner[solid[i]] if i < len(solid) else None
        if before and before == after and (not votes[a] or before in votes[a]):
            owner[a], why[a] = before, 'between'
    changed = True
    while changed:
        changed = False
        for a in copies:
            if a in owner:
                continue
            seen = {owner.get(g) for g in refs.get(a, ()) if inblock(g)}
            if len(seen) == 1 and None not in seen and not votes[a]:
                owner[a], why[a] = seen.pop(), 'via-inline'
                changed = True
    for a in copies:
        if a in owner:
            continue
        libs = {outside(t) for t in callees[a] if not inblock(t) and len(refs[t]) < GENERIC_CALLEE} - {'sony', 'libc'}
        if len(libs) == 1:
            owner[a], why[a] = libs.pop(), 'callees'
    for a in copies:
        if a in owner or votes[a]:
            continue
        mates = {owner.get(f) for fs in table.values() if a in fs for f in fs if f != a}
        if len(mates) == 1 and None not in mates:
            owner[a], why[a] = mates.pop(), 'vtable'
    for a in copies:
        if a not in owner and votes[a]:
            owner[a], why[a] = min(votes[a], key=LINK_ORDER.index), 'shared'
    missing = [a for a in copies if a not in owner]
    if missing:
        raise SystemExit('no owner for ' + ', '.join('0x%x' % a for a in missing))
    return copies, owner, why


def lines(copies, owner, why):
    """[start, end, library, weakest evidence] for runs of consecutive copies with one owner (the last run ends at the block end)."""
    merged = []
    ends = copies[1:] + [layout.linkonce_block()[1]]
    for a, b in zip(copies, ends):
        if merged and merged[-1][2] == owner[a]:
            merged[-1][1] = b
            merged[-1][3] = max(merged[-1][3], why[a], key=ORDER.index)
        else:
            merged.append([a, b, owner[a], why[a]])
    return merged


def pairs():
    import yaml
    for s in yaml.safe_load((ROOT / 'config' / SLUG / 'splits.yaml').read_text())['splits']:
        start = s['range'][0]
        if layout.is_inline(start):
            new = '%s/%s' % (layout.source_dir(start), Path(s['src']).name)
            if new != s['src']:
                print(s['src'], new)


def main():
    if '--pairs' in sys.argv:
        return pairs()
    write = '--write' in sys.argv
    copies, owner, why = analyse()
    rows = lines(copies, owner, why)
    print('%d copies' % len(copies), dict(collections.Counter(owner.values())), dict(collections.Counter(why.values())))
    if write:
        text = ('# Owner of every link-once copy (compiler-emitted inline and template code, docs/build.md), per range [start, end).\n'
                '# Generated by tools/build/linkonce_owners.py (ninja); not committed. Evidence, weakest in the range:\n'
                '#   callers, between, via-inline, callees, vtable, shared (see the tool for what each means).\n')
        text += ''.join('0x%06x 0x%06x %s %s\n' % tuple(r) for r in rows)
        OUT.parent.mkdir(parents=True, exist_ok=True)
        OUT.write_text(text)
        print('wrote', OUT.relative_to(ROOT), len(rows), 'lines')


if __name__ == '__main__':
    main()
