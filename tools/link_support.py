#!/usr/bin/env python3
"""Make splat's output linkable: define the symbols splat could not, so that every reference goes through a symbol.

splat names every address that code or data refers to, but it cannot define those that fall inside another
object (a byte inside a larger variable, a code address in the middle of a function, a VU program inside the
.vutext blob) or that are not addresses at all (hardware registers, masks). Reads splat's
undefined_syms_auto.txt / undefined_funcs_auto.txt and the generated assembly, and writes
  build/<slug>/extra_labels.txt  NAME ADDRESS: code labels fixasm.py inserts into the text file;
  build/<slug>/symbols.ld        linker assignments: `NAME = <preceding symbol> + <delta>` inside data sections,
                                 `NAME = <section>_end` at a section end, `NAME = VALUE` for plain constants.
Usage: link_support.py VARIANT_SLUG [WORK]    (WORK names the asm/ and build/ directories, default the slug)
"""
import json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LABEL = re.compile(r'^(?:glabel|alabel|jlabel|dlabel|ehlabel)\s+(\S+)', re.M)
ADDR = re.compile(r'([0-9A-Fa-f]+)$')


def main():
    slug = sys.argv[1]
    work = sys.argv[2] if len(sys.argv) > 2 else slug
    boot = json.loads((ROOT / 'config/variants.json').read_text())[slug]['boot']
    layout = json.loads((ROOT / 'config' / ('%s.layout.json' % boot)).read_text())
    secs = [(s['name'], s['addr'], s['addr'] + s['orig_size']) for s in layout['sections']
            if s['source'] == 'linked' and s['orig_size']]
    build = ROOT / 'build' / work
    undefined = {}
    for f in ('undefined_syms_auto.txt', 'undefined_funcs_auto.txt'):
        for line in (build / f).read_text().split('\n'):
            m = re.match(r'(\S+) = (0x[0-9A-Fa-f]+);', line)
            if m:
                undefined[m.group(1)] = int(m.group(2), 16)
    # defined labels per section, from the generated assembly (names carry their address)
    defined = {name: [] for name, _, _ in secs}
    for p in sorted((ROOT / 'asm' / work).rglob('*.s')):
        for name in LABEL.findall(p.read_text()):
            m = ADDR.search(name)
            if not m or name.startswith('.L'):
                continue
            a = int(m.group(1), 16)
            for sn, lo, hi in secs:
                if lo <= a < hi:
                    defined[sn].append((a, name))
    for v in defined.values():
        v.sort()
    labels, ld = [], []
    kinds = dict(label=0, rel=0, end=0, const=0)
    for name, a in sorted(undefined.items(), key=lambda kv: kv[1]):
        sec = next((s for s in secs if s[1] <= a < s[2]), None)
        if sec and sec[0] == '.text' and a % 4 == 0:
            labels.append('%s %08X' % (name, a))
            kinds['label'] += 1
        elif sec:
            prev = [x for x in defined[sec[0]] if x[0] <= a]
            if not prev:
                raise SystemExit('no preceding symbol for %s in %s' % (name, sec[0]))
            ld.append('%s = %s + 0x%X;' % (name, prev[-1][1], a - prev[-1][0]))
            kinds['rel'] += 1
        elif any(a == hi for _, _, hi in secs):
            sn = next(n for n, _, hi in secs if hi == a)
            ld.append('%s = __end%s;' % (name, sn.replace('.', '_')))
            kinds['end'] += 1
        else:
            ld.append('%s = 0x%X;' % (name, a))
            kinds['const'] += 1
    (build / 'extra_labels.txt').write_text('\n'.join(labels) + '\n')
    (build / 'symbols.ld').write_text('\n'.join(ld) + '\n')
    print('link support:', kinds)


if __name__ == '__main__':
    main()
