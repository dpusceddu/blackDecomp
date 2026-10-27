#!/usr/bin/env python3
"""Give one assembly function a source file of its own: the way to put a function in a file with other flags or another language.

Usage: split_function.py func_XXXXXXXX|ADDRESS [--cpp] [--flags "-O1 -G0 -snas"] [--compiler NAME] [--dry-run]
Every file has one compiler recipe. Use this tool only for a genuinely different
compiler, flags or language. Ordinary matching edits stay in their existing file.
This tool transfers an assembly function's INCLUDE_ASM line and its
stretch of the range in config/SLUS_213.76/splits.yaml) and creates a small file next to it, `tu_<address>.c` (`.cpp` with
--cpp), that owns only that function, with the INCLUDE_ASM line, an entry with the given flags and compiler, and prints the next
steps. Then `python3 tools/decompile.py func_XXXXXXXX --write` puts a draft in the new file and `ninja` checks it. Only functions
that are still plain INCLUDE_ASM lines can be moved (move a draft or a definition by hand and fix the range with the same
rule). `ninja` keeps printing OK throughout: nothing but the owner of the function changes.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import argparse, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline')]
import ownership
import splits as S
import tu_files
import units as U

ROOT = S.ROOT
SLUG = S.DEFAULT_SLUG
HEADER = '#include "include_asm.h"\n#include "ps2/prelude.h"\n\n'


def parse_target(text):
    import re
    m = re.fullmatch(r'(?:func_|0x)?([0-9A-Fa-f]{1,8})', text.strip())
    if not m:
        raise SystemExit('expected func_XXXXXXXX or an address, got %r' % text)
    return int(m.group(1), 16)


def split_function(addr, cpp=False, flags=None, compiler=None, dry_run=False):
    """Move the function to a file of its own; returns (new path, old path)."""
    splits = S.load_splits(SLUG)
    split, kind, line, path = ownership.locate(addr, splits, S.load_symbols(SLUG))
    name = 'func_%08X' % addr
    if split is None:
        raise SystemExit('%s: no file owns it (is it a function start of the image?)' % name)
    if kind != 'assembly':
        raise SystemExit('%s: only plain INCLUDE_ASM functions can be moved, this one is %s in %s:%s' % (
            name, {'draft': 'a draft', 'source': 'recovered'}.get(kind, 'not found'), split.src, line))
    ends = dict(U.function_table(SLUG))
    if addr not in ends:
        raise SystemExit('%s is not a function start' % name)
    new = tu_files.unique_path(addr, '.cpp' if cpp else '.c')
    new = (Path(split.src).parent / Path(new).name).as_posix()
    if (ROOT / new).exists():
        raise SystemExit('%s exists already' % new)
    if dry_run:
        return new, split.src
    tu_files.release_function(addr, SLUG)
    entry = {'src': new, 'range': [addr, ends[addr]]}
    if compiler and compiler != S.DEFAULT_COMPILER:
        entry['compiler'] = compiler
    if flags:
        entry['flags'] = flags
    split_file = S.config_dir(SLUG) / 'splits.yaml'
    head, entries, tail = S.split_entries(split_file.read_text())
    S.write_entries(split_file, head, entries + [entry], tail)
    (ROOT / new).write_text(HEADER + tu_files.marker(addr, new) + '\n')
    return new, split.src


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('function', help='func_XXXXXXXX or an address (0x...)')
    ap.add_argument('--cpp', action='store_true', help='make the new file C++ (.cpp)')
    ap.add_argument('--flags', help='compiler flags of the new file, for example "-O1 -G0 -snas" (default: the project defaults)')
    ap.add_argument('--compiler', help='compiler of the new file (default %s)' % S.DEFAULT_COMPILER)
    ap.add_argument('--dry-run', action='store_true', help='only say what would happen')
    a = ap.parse_args(argv)
    addr = parse_target(a.function)
    new, old = split_function(addr, a.cpp, a.flags.split() if a.flags else None, a.compiler, a.dry_run)
    verb = 'would move' if a.dry_run else 'moved'
    print('func_%08X %s from %s to %s' % (addr, verb, old, new))
    if not a.dry_run:
        print('next: python3 tools/decompile.py func_%08X --write   (a draft into %s), then ninja' % (addr, new))
    return 0


if __name__ == '__main__':
    sys.exit(main())
