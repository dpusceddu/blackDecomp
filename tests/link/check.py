#!/usr/bin/env python3
"""Link an SN-compiled probe and a GNU-assembled object with the pinned local tools.

Usage: python3 tests/link/check.py   (Linux x86-64, installed toolchain; prints the linked layout)
"""
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT/'tools'/d) for d in ('', 'build')]
from object_compile import compile_file, environment

base, env = environment()
probe = ROOT/'build/probe'
probe.mkdir(parents=True, exist_ok=True)
with tempfile.TemporaryDirectory(prefix='link-', dir=probe) as directory:
    out = Path(directory)
    compile_file('ee-gcc2.95.3-136', ['-O2','-G0','-snas','-c'],
                 str(ROOT/'tests/toolchain/trivial.c'), str(out/'c.o'))
    subprocess.run([str(base/'compilers/ee-gcc2.96/ee/bin/as'), '-o', str(out/'extern.o'),
                    str(ROOT/'tests/link/extern.s')], env=env, check=True)
    prefix = env['BLACK_BINUTILS_PREFIX']
    subprocess.run([prefix+'ld','-m','elf32ltsmip','-T',str(ROOT/'tests/link/probe.ld'),
                    '-o',str(out/'probe.elf'),str(out/'extern.o'),str(out/'c.o')], env=env, check=True)
    for command in ([prefix+'readelf','-hS'], [prefix+'nm'], [prefix+'objdump','-d']):
        subprocess.run(command+[str(out/'probe.elf')], env=env, check=True)
