#!/usr/bin/env python3
"""Retrieve GCC pass dumps through the build backend for source-shape diagnosis.

Usage: compiler_dumps.py SOURCE [--flags '-O2 -G0 -snas'] [--output build/dumps/CASE]
The source and quoted include closure are snapshotted. Objects, generated assembly
and RTL remain in ignored output; no SDK executable runs in this host process.
"""
import argparse
import io
import json
from pathlib import Path
import subprocess
import sys
import tarfile
import uuid

ROOT = Path(__file__).resolve().parents[1]

WORKER = r'''
import json, os, pathlib, subprocess, sys, tarfile
with tarfile.open('inputs.tgz') as archive:
    archive.extractall('.')
request = json.load(open('request.json'))
sys.path.insert(0, 'tools')
from assembler import compile_with_assembler
from elfobj import normalize_object
root = pathlib.Path('/toolchains/compilers') / request['compiler']
env = dict(os.environ, TMPDIR='/work', WINEDEBUG='-all')
if (root / 'bin/ee-gcc.exe').is_file():
    backend = next(p for p in sorted((root / 'lib/gcc-lib/ee').iterdir())
                   if p.is_dir() and not p.name.startswith('.'))
    env['WIBO_PATH'] = str(backend)
    prefix = ['wibo', str(root / 'bin/ee-gcc.exe'), '-B' + str(backend) + '/']
else:
    prefix = [str(root / 'bin/ee-gcc'), '-B' + str(root / 'bin/ee-')]
flags = request['flags'] + ['-I', 'include', '-da', '-fdump-unnumbered']
result = compile_with_assembler(prefix, flags, request['source'], 'candidate.o', env, 300)
if result.returncode:
    print((result.stdout + result.stderr)[-4000:])
    raise SystemExit(result.returncode)
obj = pathlib.Path('candidate.o')
obj.write_bytes(normalize_object(obj.read_bytes()))
files = [p for p in pathlib.Path('.').iterdir() if p.is_file()
         and (p.name.startswith('source.') or p.name.startswith('candidate.'))]
with tarfile.open('dumps.tgz', 'w:gz') as archive:
    for path in files:
        archive.add(path)
print(json.dumps({'compiler': request['compiler'], 'flags': flags,
                  'files': [{'name': p.name, 'bytes': p.stat().st_size} for p in sorted(files)]}))
'''


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
    import autodecomp
    source = args.source.read_text()
    flags = shlex.split(args.flags)
    if args.source.suffix in ('.cpp', '.cc', '.cxx') and '-x' not in flags:
        flags = ['-x', 'c++'] + flags
    name = 'source' + args.source.suffix
    files = autodecomp.compile_dependencies(source)
    files.update({name: source.encode(),
                  'request.json': json.dumps(dict(compiler=args.compiler, flags=flags, source=name)).encode()})
    for tool in ('assembler.py', 'elfobj.py'):
        files['tools/' + tool] = (ROOT / 'tools' / tool).read_bytes()
    data = io.BytesIO()
    with tarfile.open(fileobj=data, mode='w:gz') as archive:
        for path, content in sorted(files.items()):
            item = tarfile.TarInfo(path)
            item.size = len(content)
            archive.addfile(item, io.BytesIO(content))
    destination.mkdir(parents=True, exist_ok=True)
    (destination / 'inputs.tgz').write_bytes(data.getvalue())
    (destination / 'worker.py').write_text(WORKER)
    subprocess.run([sys.executable, str(ROOT / 'tools/sandbox.py'), str(destination / 'worker.py'),
                    '--timeout', '360', '--file', 'inputs.tgz=' + str(destination / 'inputs.tgz'),
                    '--out', 'dumps.tgz=' + str(destination / 'dumps.tgz')], check=True)
    with tarfile.open(destination / 'dumps.tgz') as archive:
        for item in archive:
            if not item.isfile() or Path(item.name).name != item.name:
                raise ValueError('unexpected compiler dump path')
            (destination / item.name).write_bytes(archive.extractfile(item).read())
    print('Dumps:', destination.relative_to(ROOT))


if __name__ == '__main__':
    main()
