#!/usr/bin/env python3
"""Link check for the isolated MIPS binutils: SN-compiled probe + GNU-assembled object, trivial linker script.
Usage: .venv/bin/python tests/link/check.py   (needs the toolchain; prints the linked image's layout)"""
import subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
py = sys.executable
obj = ROOT / 'build/probe/c-link.o'
subprocess.run([py, str(ROOT / 'tools/compile.py'), 'ee-gcc2.95.3-136', '-O2', '-G0', '-snas', '-c',
                str(ROOT / 'tests/toolchain/trivial.c'), '-o', str(obj)], check=True)
sys.exit(subprocess.run([py, str(ROOT / 'tools/sandbox.py'), str(ROOT / 'tests/link/job.py'),
                         '--file', 'extern.s=' + str(ROOT / 'tests/link/extern.s'),
                         '--file', 'probe.ld=' + str(ROOT / 'tests/link/probe.ld'), '--file', 'c.o=' + str(obj)]).returncode)
