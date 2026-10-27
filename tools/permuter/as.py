#!/usr/bin/env python3
"""Assemble a decomp-permuter target with its owning file's assembler from splits.yaml."""
import argparse
from pathlib import Path
import subprocess
import sys
import tempfile
sys.path[:0] = [str(Path(__file__).resolve().parents[1]/d) for d in ('','build')]
from cc import recipe
from object_compile import compile_file, environment
import assembler
from asm_syntax import translate
from elfobj import normalize_object, restore_gprel


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--file', required=True)
    ap.add_argument('input')
    ap.add_argument('-o', required=True)
    a = ap.parse_args()
    split = recipe(a.file)
    base, env = environment()
    choice, flags = assembler.selection(split.compile_flags())
    sn = '-snas' in flags or (choice or '').startswith('sn-')
    text, aliases = translate(Path(a.input).read_text(),sn=sn)
    # Permuter compares relocatable instructions; addend aliases remain symbolic.
    text = '\n'.join('%s = %s' % p for p in aliases.items())+'\n'+text
    with tempfile.TemporaryDirectory(prefix='black-permuter-as-') as directory:
        source = Path(directory)/'input.s'
        source.write_text(text)
        if choice:
            command = assembler.command(choice, flags, str(source), a.o, env=env)
        elif sn:
            root = base/'compilers'/split.compiler/'lib/gcc-lib/ee'
            backend = next(p for p in sorted(root.iterdir()) if p.is_dir() and not p.name.startswith('.'))
            command = [str(base/'bin/wibo'), assembler.short_path(backend/'Ps2EeAs.exe'), '-O2',
                       next((f for f in flags if f.startswith('-G')), '-G0'), '-mabi=eabi', '-I','include','-o',a.o,str(source)]
        else:
            # The SN bundles do not contain ee/bin/as. Let the same driver as
            # the source build select its default assembler and search paths.
            compile_file(split.compiler, flags + ['-I', 'include'], str(source), a.o)
            command = None
        if command is not None:
            subprocess.run(command,env=env,check=True)
    out = Path(a.o)
    out.write_bytes(restore_gprel(normalize_object(out.read_bytes())))


if __name__=='__main__':
    main()
