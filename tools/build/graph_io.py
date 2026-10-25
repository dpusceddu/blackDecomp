#!/usr/bin/env python3
"""Record generator files or enforce a Ninja edge's declared generated-file reads and writes."""
import argparse
import ast
from functools import lru_cache
import json
import os
from pathlib import Path
import runpy
import stat
import sys

ROOT = Path(__file__).resolve().parents[2]
GENERATED = ('build/', 'asm/', 'data/')


def write_text(path, text):
    path = Path(path)
    sys.audit('black.output', str(path))
    path.parent.mkdir(parents=True, exist_ok=True)
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def write_bytes(path, data):
    path=Path(path)
    sys.audit('black.output',str(path))
    path.parent.mkdir(parents=True,exist_ok=True)
    if not path.exists() or path.read_bytes()!=data:
        path.write_bytes(data)


def relative(path):
    if not isinstance(path, (str, bytes, os.PathLike)):
        return None
    name = os.fsdecode(path)
    full = os.path.abspath(name)
    prefix = str(ROOT) + os.sep
    return full[len(prefix):] if full.startswith(prefix) else None


def generated(path):
    # SDK installation is an external prerequisite, not a generated game input.
    return path.startswith(GENERATED) and not path.startswith('build/toolchain/')


@lru_cache(None)
def python_inputs(script):
    """Project Python imports, including imports on diagnostic/error paths."""
    directories = [ROOT/'tools'/d for d in ('', 'build', 'pipeline', 'maint', 'permuter')]
    pending, seen = [script], set()
    while pending:
        name = pending.pop()
        if name in seen or not (ROOT/name).is_file():
            continue
        seen.add(name)
        tree = ast.parse((ROOT/name).read_text())
        for node in ast.walk(tree):
            modules = [a.name for a in node.names] if isinstance(node, ast.Import) else [node.module] if isinstance(node, ast.ImportFrom) else []
            for module in modules:
                if not module:
                    continue
                for directory in directories:
                    candidate = directory/(module.split('.')[0]+'.py')
                    if candidate.is_file():
                        pending.append(candidate.relative_to(ROOT).as_posix())
                        break
    return sorted(seen)


class Accesses:
    def __init__(self):
        self.reads, self.writes = set(), set()
        self.active = True

    def hook(self, event, args):
        if not self.active:
            return
        if event == 'black.output':
            path = relative(args[0])
            if path:
                self.writes.add(path)
            return
        if event != 'open':
            return
        path = relative(args[0])
        if path is None or '__pycache__/' in path or path.endswith('.pyc'):
            return
        mode, flags = args[1:3]
        writing = bool(flags & (os.O_WRONLY | os.O_RDWR | os.O_CREAT | os.O_TRUNC | os.O_APPEND))
        if writing:
            self.writes.add(path)
        elif path not in self.writes:
            self.reads.add(path)

    def finish(self, script):
        self.active = False
        if script is not None:
            self.reads.update(python_inputs(script))
        for module in list(sys.modules.values()):
            name = getattr(module, '__file__', None)
            if name:
                name = relative(name)
                if name and name.endswith('.py') and '__pycache__/' not in name:
                    self.reads.add(name)
        return dict(reads=sorted(p for p in self.reads-self.writes if (ROOT/p).is_file()), writes=sorted(self.writes))


def execute(command, log=None):
    os.environ['BLACK_NINJA'] = '1'
    sys.argv = command
    if command[0] == '-m':
        module = command[1]
        sys.argv = command[1:]
        runpy.run_module(module, run_name='__main__')
    else:
        sys.path.insert(0, str((ROOT/command[0]).parent))
        runpy.run_path(command[0], run_name='__main__')


def invalidate(spec, path, recording):
    """A failed command must not leave apparently up-to-date generated outputs."""
    names=[path] if recording else spec['writes']
    for name in names:
        if generated(name):
            (ROOT/name).unlink(missing_ok=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=['record', 'check'])
    parser.add_argument('spec')
    parser.add_argument('--log')
    parser.add_argument('command', nargs=argparse.REMAINDER)
    a = parser.parse_args()
    command = a.command[1:] if a.command[:1] == ['--'] else a.command
    spec = json.loads(Path(a.spec).read_text()) if a.mode == 'check' else None
    if a.mode=='record':os.environ['BLACK_NINJA_RECORD']=a.spec
    access = Accesses()
    sys.addaudithook(access.hook)
    original_stat=os.stat
    def observed_stat(path,*args,**kwargs):
        result=original_stat(path,*args,**kwargs)
        name=relative(path)
        if access.active and name and generated(name) and stat.S_ISREG(result.st_mode):
            access.reads.add(name)
        return result
    os.stat=observed_stat
    saved = sys.stdout
    try:
        if a.log:
            sys.stdout = open(a.log, 'w')
        try:
            execute(command)
        except SystemExit as error:
            if error.code not in (None, 0):
                invalidate(spec,a.spec,a.mode=='record')
                raise
        except BaseException:
            invalidate(spec,a.spec,a.mode=='record')
            raise
    finally:
        if sys.stdout is not saved:
            sys.stdout.close()
            sys.stdout = saved
        access.active = False
        os.stat=original_stat
    io = access.finish(command[0] if a.mode=='record' else None) if command[0] != '-m' else dict(reads=sorted(access.reads-access.writes),writes=sorted(access.writes))
    if a.mode == 'record':
        io['command'] = command
        io['writes'] = sorted(set(io['writes']) | {a.spec})
        io['reads'] = sorted(set(io['reads'])-set(io['writes']))
        write_text(a.spec, json.dumps(io, indent=1)+'\n')
    else:
        problems = []
        for key in ('reads', 'writes'):
            allowed = set(spec[key])
            # Reading an output while constructing it (normalization/restat)
            # is internal to the producing edge, not a self dependency.
            if key == 'reads':
                allowed.update(spec['writes'])
            else:
                allowed.update(spec.get('managed_outputs',[]))
            for name in io[key]:
                if generated(name) and name not in allowed:
                    problems.append('undeclared %s: %s' % (key, name))
        if problems:
            invalidate(spec,a.spec,False)
            raise SystemExit('\n'.join(problems))


if __name__ == '__main__':
    main()
