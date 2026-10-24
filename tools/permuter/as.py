#!/usr/bin/env python3
"""Assemble the target of decomp-permuter with the EE assembler of the pinned toolchain.

Usage: as.py INPUT.s -o OUTPUT.o        (run from the repository root; permuter_settings.toml makes import.py call it)
The split assembly of a function (asm/SLUS_213.76/nonmatchings/func_XXXXXXXX.s) includes include/macro.inc; the job runs
through tools/build/backend.py like every other toolchain job.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import base64, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import backend

JOB = '''
import os, subprocess, sys
AS = os.environ.get('BLACK_TOOLCHAINS', '/toolchains') + '/compilers/ee-gcc2.96/ee/bin/as'
p = subprocess.run([AS, '-I', 'include', '-o', 'output.o', 'input.s'], capture_output=True, text=True)
sys.stdout.write(p.stdout + p.stderr)
sys.exit(p.returncode)
'''


def main(args):
    if len(args) != 3 or args[1] != '-o':
        raise SystemExit(__doc__)
    source, output = Path(args[0]), Path(args[2])
    encode = lambda path: base64.b64encode(path.read_bytes()).decode()
    reply = backend.run_script(dict(files={'input.s': encode(source), 'include/macro.inc': encode(ROOT / 'include/macro.inc')},
                                    script=JOB, out=['output.o'], timeout=120))
    sys.stdout.write(reply['out'])
    sys.stderr.write(reply['err'])
    if reply['rc'] == 0 and 'output.o' in reply['artifacts']:
        output.write_bytes(base64.b64decode(reply['artifacts']['output.o']))
        return 0
    return reply['rc'] or 1


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
