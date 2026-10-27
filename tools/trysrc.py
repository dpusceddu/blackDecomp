#!/usr/bin/env python3
"""Compile a hand-written C/C++ source with its owning file's recipe and score it against the original.

Usage: trysrc.py ADDR SOURCE.c|cpp [--flags "-O2 -G0 -snas"] [--variants] [--quiet]
The function in SOURCE must be named like the image's symbol (func_XXXXXXXX). Uses the owning file's compiler,
flags and assembler by default; --flags replaces its flags, --variants explores the pipeline's flag sets.
Infers C++ from the candidate or owner unless -x explicitly selects a language. Exit status 0 when exact.
"""
import argparse, difflib, shlex, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
import preflight
from splits import load_splits, group_splits


def source_recipe(addr, source, flags=None, variants=False):
    """(flags or None for pipeline variants, language) for a scratch candidate."""
    owner = next((g[0] for g in group_splits(load_splits()) if any(s.start <= addr < s.end for s in g)), None)
    if owner is None:
        raise SystemExit('no source file owns 0x%x' % addr)
    language = 'c++' if Path(source).suffix in ('.cpp', '.cc', '.cxx', '.C') or Path(owner.src).suffix == '.cpp' else 'c'
    if variants:
        return None, language
    selected = list(flags) if flags is not None else owner.compile_flags()
    if not any(f.startswith('--cc=') for f in selected):
        selected.insert(0, '--cc=' + owner.compiler)
    return selected, language


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('addr')
    ap.add_argument('source')
    ap.add_argument('--flags', help='only this flag set')
    ap.add_argument('--variants', action='store_true', help="try the pipeline's flag variants instead of the owner's recipe")
    ap.add_argument('--quiet', action='store_true')
    a = ap.parse_args()
    if a.flags is not None and a.variants:
        ap.error('--flags and --variants are mutually exclusive')
    preflight.require()
    import autodecomp as A
    import rabbitizer
    f = next(x for x in A.load_inventory() if x['addr'] == int(a.addr, 16))
    src = Path(a.source).read_text()
    flags, language = source_recipe(f['addr'], a.source, shlex.split(a.flags) if a.flags is not None else None, a.variants)
    d, flags, toks, note = A.try_source(f, src, flags, language=language)
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
