#!/usr/bin/env python3
"""Run one of the pinned EE compilers on a standalone source file.

Usage: compile.py COMPILER [flags] -c source.c|.cpp|.s -o output.o
The local backend (default) uses the toolchain installed by tools/toolchain.py. Only standalone sources are
supported. Outputs must go under build/ or .local/.
Objects get one header fix (tools/elfobj.py: symbol order and sh_info) so that mainline GNU ld accepts SN-assembled output.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import base64, json, os, shlex, subprocess, sys, tempfile, uuid
from pathlib import Path, PurePosixPath

sys.path.insert(0, str(Path(__file__).resolve().parent))
import backend
from elfobj import normalize_object

ROOT = Path(__file__).resolve().parents[1]


def main():
    args = sys.argv[1:]
    if not args:
        raise SystemExit(__doc__)
    compiler, args = args[0], args[1:]
    if any(a.startswith('--assembler=') for a in args):
        # Use exactly the same isolated -S/assembler recipe as candidate and
        # production builds. The normal standalone driver path stays unchanged.
        import autodecomp
        if '-c' not in args or '-o' not in args or args.index('-o') + 1 == len(args):
            raise SystemExit('Alternate assemblers require -c SOURCE -o OUTPUT.o')
        output_index = args.index('-o')
        inputs = [a for i, a in enumerate(args) if i != output_index + 1
                  and Path(a).suffix in ('.c', '.cpp', '.cc', '.cxx') and Path(a).is_file()]
        if len(inputs) != 1:
            raise SystemExit('Alternate assemblers require one C or C++ source')
        source = inputs[0]
        dest = Path(args[output_index + 1]).resolve()
        if dest.suffix != '.o' or not any(dest.is_relative_to(ROOT / d) for d in ('build', '.local')):
            raise SystemExit('Keep object outputs under build/ or .local/.')
        flags = [a for i, a in enumerate(args) if a != source and a != '-c'
                 and i not in (output_index, output_index + 1)]
        if Path(source).suffix in ('.cpp', '.cc', '.cxx') and '-x' not in flags:
            flags = ['-x', 'c++'] + flags
        rc, message, obj = autodecomp.worker_compile([
            ('standalone', Path(source).read_text(), ['--cc=' + compiler] + flags)
        ], tag='standalone-assembler')['standalone']
        if message:
            print(message, file=sys.stderr)
        if not rc:
            dest.parent.mkdir(parents=True, exist_ok=True)
            dest.write_bytes(obj)
        return rc
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
    reply = run_local(request)
    sys.stdout.write(reply['stdout'])
    sys.stderr.write(reply['stderr'])
    for name, dest in outputs.items():
        if name in reply['artifacts']:
            dest.parent.mkdir(parents=True, exist_ok=True)
            data = base64.b64decode(reply['artifacts'][name], validate=True)
            dest.write_bytes(normalize_object(data) if dest.suffix == '.o' else data)  # header fix for GNU ld
    return reply['returncode']


def run_local(request):
    """Run the compiler from the local toolchain in a scratch directory; same reply shape as the build backend."""
    import toolchain
    toolchain.require()
    base = toolchain.root()
    compiler = request['compiler']
    root = base / 'compilers' / compiler
    if not root.is_dir():
        raise SystemExit('compiler %s is not installed; it is not part of the local toolchain' % compiler)
    with tempfile.TemporaryDirectory(prefix='black-compile-') as directory:
        work = Path(directory)
        for name, data in request['files'].items():
            path = PurePosixPath(name)
            if path.is_absolute() or '..' in path.parts:
                raise ValueError('Unsafe input path')
            (work / name).write_bytes(base64.b64decode(data, validate=True))
        env = dict(os.environ, TMPDIR=str(work), WINEDEBUG='-all')
        env['PATH'] = str(base / 'bin') + os.pathsep + env.get('PATH', '')
        flags = request['args']
        if compiler.startswith('mwcps2-'):
            command = ['wibo', str(root / 'mwccps2.exe'), *flags]
        elif (root / 'bin/ee-gcc.exe').is_file():
            backend_dir = next(d for d in sorted((root / 'lib/gcc-lib/ee').iterdir()) if d.is_dir() and d.name[0] != '.')
            env['WIBO_PATH'] = str(backend_dir)
            command = ['wibo', str(root / 'bin/ee-gcc.exe'), '-B' + str(backend_dir) + '/', *flags]
        else:
            command = [str(root / 'bin/ee-gcc'), '-B' + str(root / 'bin/ee-'), *flags]
        done = subprocess.run(command, cwd=work, env=env, capture_output=True, timeout=120)
        artifacts = {}
        for path in work.rglob('*'):
            if path.is_file() and not path.is_symlink() and path.suffix in {'.o', '.s', '.i'}:
                artifacts[path.relative_to(work).as_posix()] = base64.b64encode(path.read_bytes()).decode()
    return {'returncode': done.returncode, 'stdout': done.stdout.decode(errors='replace'),
            'stderr': done.stderr.decode(errors='replace'), 'artifacts': artifacts}


if __name__ == '__main__':
    sys.exit(main())
