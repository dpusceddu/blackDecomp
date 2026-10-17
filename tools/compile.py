#!/usr/bin/env python3
"""Run an SN GCC EE compiler in the build backend (never on this host).

Usage: compile.py COMPILER [flags] -c source.c|.cpp|.s -o output.o
Reads .local/config.json; that file is private and never committed.
Inputs are sent to the build backend; only standalone sources are
supported. Outputs must go under build/ or .local/.
"""
import base64, json, shlex, subprocess, sys, uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def run_batch(request):
    """Run the batch with the build backend configured for this checkout."""
    raise SystemExit('Build backend failed; check the build backend configuration.')


def main():
    args = sys.argv[1:]
    if not args:
        raise SystemExit(__doc__)
    compiler, args = args[0], args[1:]
    files, outputs, mapped = {}, {}, []
    i = 0
    while i < len(args):
        arg = args[i]
        if arg == '-o':
            i += 1
            dest = Path(args[i]).resolve()
            if not any(dest.is_relative_to(ROOT / d) for d in ('build', '.local')):
                raise SystemExit('Keep outputs under build/ or .local/.')
            if dest.suffix not in {'.o', '.s', '.i'}:
                raise SystemExit('Output must be .o, .s or .i')
            outputs['output' + dest.suffix] = dest
            mapped += ['-o', 'output' + dest.suffix]
        elif not arg.startswith('-') and Path(arg).is_file():
            src = Path(arg).resolve()
            if src.suffix not in {'.c', '.cpp', '.cc', '.cxx', '.s'}:
                raise SystemExit('Only standalone source inputs are supported.')
            name = 'input%d%s' % (len(files), src.suffix)
            files[name] = base64.b64encode(src.read_bytes()).decode()
            mapped.append(name)
        else:
            if arg.startswith('@'):
                raise SystemExit('Use explicit arguments.')
            mapped.append(arg)
        i += 1
    request = {'compiler': compiler, 'args': mapped, 'files': files}
    reply = run_batch(request)
    sys.stdout.write(reply['stdout'])
    sys.stderr.write(reply['stderr'])
    for name, dest in outputs.items():
        if name in reply['artifacts']:
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(base64.b64decode(reply['artifacts'][name], validate=True))
    return reply['returncode']


if __name__ == '__main__':
    sys.exit(main())
