#!/usr/bin/env python3
"""Run a build job script with the compilers, assembler and binutils of the selected backend.

Usage: sandbox.py SCRIPT.py [--file NAME=PATH ...] [--out NAME=PATH ...] [--timeout SECONDS]
The backend (tools/build/backend.py) is the local one by default: the script runs on this machine with the toolchain that
`tools/toolchain.py install` downloads (BLACK_TOOLCHAINS points at it, BLACK_WORK is a scratch directory). An optional
plugin named in the ignored .local/config.json can run it elsewhere. The script sees the compiler catalog under
$BLACK_TOOLCHAINS and the MIPS binutils (`mipsel-linux-gnu-ld`, `-objcopy`, ...) on PATH; the EE assembler is
$BLACK_TOOLCHAINS/compilers/ee-gcc2.96/ee/bin/as. Each --file is copied to $BLACK_WORK/job/NAME first (read it from
the script); each --out copies that file back to PATH afterwards. The script's stdout/stderr are relayed.
"""
import argparse, base64, sys
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
import backend


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('script', type=Path)
    ap.add_argument('--file', action='append', default=[])
    ap.add_argument('--out', action='append', default=[])
    ap.add_argument('--timeout', type=int, default=300)
    a = ap.parse_args()
    files = {}
    for f in a.file:
        name, path = f.split('=', 1)
        files[name] = base64.b64encode(Path(path).read_bytes()).decode()
    outs = dict(o.split('=', 1) for o in a.out)
    reply = backend.run_script(dict(files=files, script=a.script.read_text(), out=list(outs), timeout=a.timeout))
    return finish(reply, outs)


def finish(reply, outs):
    sys.stdout.write(reply['out'])
    sys.stderr.write(reply['err'])
    for name, dest in outs.items():
        if name in reply['artifacts']:
            Path(dest).parent.mkdir(parents=True, exist_ok=True)
            Path(dest).write_bytes(base64.b64decode(reply['artifacts'][name]))
    return reply['rc']


if __name__ == '__main__':
    sys.exit(main())
