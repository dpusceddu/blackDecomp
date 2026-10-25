#!/usr/bin/env python3
"""Compile a hand-written or templated C source for one function and score it against the original.

Usage: trysrc.py ADDR SOURCE.c [--flags "-O2 -G0 -snas"] [--quiet]
The function in SOURCE must be named like the image's symbol (func_XXXXXXXX). Tries the pipeline's flag variants,
prints the best score and the instruction diff (same format as `autodecomp.py show`). Exit status 0 when exact.
"""
import argparse, difflib, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
import preflight


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('addr')
    ap.add_argument('source')
    ap.add_argument('--flags', help='only this flag set')
    ap.add_argument('--quiet', action='store_true')
    a = ap.parse_args()
    preflight.require()
    import autodecomp as A
    import rabbitizer
    f = next(x for x in A.load_inventory() if x['addr'] == int(a.addr, 16))
    src = Path(a.source).read_text()
    d, flags, toks, note = A.try_source(f, src, a.flags.split() if a.flags else None)
    if d is None:
        print('compile failed:', note)
        sys.exit(2)
    target = A.Target(f, None)
    print('%s: %s, flags %s, differing %d (%s)' % (f['name'], 'EXACT' if d == 0 else 'not exact', ' '.join(flags), d, note))
    if d and not a.quiet:
        want = target.tokens
        sm = difflib.SequenceMatcher(None, [repr(t) for t in want], [repr(t) for t in toks], autojunk=False)
        text = lambda t, pc: '%-44s %s' % (rabbitizer.Instruction(t[0], pc).disassemble(), t[1] if t[1] else '')
        for tag, i1, i2, j1, j2 in sm.get_opcodes():
            for k in range(max(i2 - i1, j2 - j1)):
                l = text(want[i1 + k], f['addr'] + 4 * (i1 + k)) if i1 + k < i2 else ''
                r = text(toks[j1 + k], 0) if j1 + k < j2 else ''
                print('%s %-90s | %s' % (' ' if tag == 'equal' else '*', l, r))
    sys.exit(0 if d == 0 else 1)


if __name__ == '__main__':
    preflight.guard(main)
