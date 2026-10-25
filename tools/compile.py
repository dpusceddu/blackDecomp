#!/usr/bin/env python3
"""Compile one source with a pinned local compiler (Linux x86-64).

Usage: compile.py COMPILER [flags] -c SOURCE -o build/OUTPUT.o
Also accepts -S or -E. Flags and assembler choices use the ordinary object compiler.
"""
from pathlib import Path
import sys
sys.path[:0] = [str(Path(__file__).resolve().parent/d) for d in ('','build')]
from object_compile import compile_file


def main():
    args = sys.argv[1:]
    if not args or args[0] in ('-h','--help'):
        print(__doc__)
        return
    compiler, args = args[0], args[1:]
    if '-o' not in args:
        raise SystemExit('expected -o OUTPUT')
    at = args.index('-o')
    output = Path(args[at+1])
    flags = args[:at]+args[at+2:]
    sources = [f for f in flags if Path(f).suffix in ('.c','.cpp','.cc','.cxx','.s') and Path(f).is_file()]
    if len(sources)!=1:
        raise SystemExit('expected exactly one source input')
    source = sources[0]
    flags = [f for f in flags if f not in (source,'-c')]
    output.parent.mkdir(parents=True,exist_ok=True)
    compile_file(compiler,flags,source,str(output))


if __name__=='__main__':
    main()
