#!/usr/bin/env python3
"""Retrieve GCC pass dumps with the pinned local compiler for source-shape diagnosis.

Usage: compiler_dumps.py SOURCE [--flags '-O2 -G0 -snas'] [--output build/dumps/CASE]
The source is copied into the output directory. Project headers are read in place.
Objects, generated assembly and RTL remain ignored; run in the documented Linux build environment.
"""
import argparse
import sys
import os
import shutil
import tempfile
from pathlib import Path
import uuid

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools'/d) for d in ('', 'build', 'pipeline')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('--flags', default='-O2 -G0 -snas')
    parser.add_argument('--compiler', default='ee-gcc2.95.3-136')
    parser.add_argument('--output', type=Path)
    args = parser.parse_args()
    if not args.compiler.startswith(('ee-gcc2.95', 'ee-gcc2.9-')):
        parser.error('GCC 2.9x dump options require an EE GCC compiler')
    destination = (args.output or ROOT / 'build/compiler-dumps' / (args.source.stem + '-' + uuid.uuid4().hex[:8])).resolve()
    if not any(destination.is_relative_to(ROOT / folder) for folder in ('build', '.local')):
        parser.error('keep compiler dumps under build/ or .local/')
    import shlex
    source = args.source.read_text()
    flags = shlex.split(args.flags)
    if args.source.suffix in ('.cpp', '.cc', '.cxx') and '-x' not in flags:
        flags = ['-x', 'c++'] + flags
    from object_compile import compile_file
    destination.mkdir(parents=True,exist_ok=True)
    source_path = destination / ('source'+args.source.suffix)
    source_path.write_text(source)
    flags += ['-I',str(args.source.resolve().parent),'-I',str(ROOT/'include'),'-da','-fdump-unnumbered']
    # GCC 2.95 writes pass dumps into its working directory. Keep concurrent
    # diagnoses separate and retain the dumps even when compilation fails.
    previous = Path.cwd()
    with tempfile.TemporaryDirectory(prefix='passes-', dir=destination) as temporary:
        work = Path(temporary)
        if (ROOT/'asm').exists():
            (work/'asm').symlink_to(ROOT/'asm', target_is_directory=True)
        (work/'include').symlink_to(ROOT/'include', target_is_directory=True)
        try:
            os.chdir(work)
            compile_file(args.compiler,flags,str(source_path),str(destination/'candidate.o'))
        finally:
            os.chdir(previous)
            for path in work.iterdir():
                if path.is_file() and not path.is_symlink():
                    shutil.move(str(path),str(destination/path.name))
    print('Dumps:', destination.relative_to(ROOT))


if __name__ == '__main__':
    main()
