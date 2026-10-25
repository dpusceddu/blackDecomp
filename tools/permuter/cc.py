#!/usr/bin/env python3
"""Per-file compile command for decomp-permuter's import.py, using splits.yaml.

Usage: cc.py --file src/<library>/<unit>.c INPUT.c -o OUTPUT.o
Run in Linux, WSL, or the project container. The input is permuter's preprocessed
candidate; compiler, flags and assembler remain those of the selected source file.
"""
import argparse
from pathlib import Path
import sys
sys.path[:0] = [str(Path(__file__).resolve().parents[1]/d) for d in ('','build')]
from splits import load_splits, group_splits
from object_compile import compile_file


def recipe(source):
    return next(group[0] for group in group_splits(load_splits()) if group[0].src == source)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--file', required=True, help='owning source file in splits.yaml')
    ap.add_argument('-o', required=True)
    ap.add_argument('input')
    a, extra = ap.parse_known_args()
    split = recipe(a.file)
    flags = split.compile_flags()
    if Path(a.file).suffix == '.cpp' and '-x' not in flags:
        flags = ['-x','c++']+flags
    compile_file(split.compiler,flags+extra+['-I','include'],a.input,a.o)


if __name__=='__main__':
    main()
