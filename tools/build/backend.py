"""Where the toolchain jobs run: the built-in local backend (default) or an optional plugin module.

Every tool that needs a compiler, assembler or linker sends a batch of work through this module and never starts a
toolchain program itself. The local backend runs the batch on this machine with the pinned toolchain installed by
tools/toolchain.py (wibo, the Docker image or a Linux host). A contributor who wants to run the toolchain elsewhere
can point the ignored file .local/config.json at a Python file that implements the same interface:

  {"backend_plugin": "path/to/plugin.py"}        path relative to the repository root, or absolute

The plugin is loaded once per process; it receives the parsed contents of .local/config.json, so it may read its own keys
there. BLACK_BACKEND=local forces the local backend. Functions of the module:

  run_script(request, config) -> reply           required. Run one job script with the toolchain.
      request  {files: {name: base64}, script: str, out: [name], timeout: seconds}
      reply    {rc, out, err, artifacts: {name: base64}}
      The script runs in a scratch directory with its files unpacked as WORK/job/NAME, the compiler catalog in
      $BLACK_TOOLCHAINS and the MIPS binutils on PATH. backend.WRAPPER is the program that does this; a plugin can
      send it to a machine that has the toolchain and feed it the request as JSON on stdin (it prints the reply).
      One call carries a whole batch of compiles, so per-call latency does not matter.
  compile_standalone(request, config) -> reply   optional. One standalone compile for tools/compile.py.
      request  {compiler, args, files: {name: base64}}   reply  {returncode, stdout, stderr, artifacts}
  service(action, name, files, script, timeout, config) -> reply    optional. Long-running detached jobs for
      tools/pipeline/permuter_service.py (actions start, submit, status, fetch, stop); the reply of fetch has an `archive` (bytes).

A failure of the backend itself is reported by raising SystemExit('Build backend failed; ...'): the tools stop on that
message instead of treating it as a compile error.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import base64, importlib.util, json, os, shutil, subprocess, sys, tempfile
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[2]
CONFIG = ROOT / '.local' / 'config.json'
FAILURE = 'Build backend failed; run tools/toolchain.py check (or see the backend plugin named in .local/config.json).'

# Runs a job script (see run_script). Reads the request as JSON on stdin and prints the reply as JSON.
WRAPPER = r'''
import base64, json, sys, os, subprocess
req = json.load(sys.stdin)
WORK = os.environ.get('BLACK_WORK', '/work')
if os.environ.get('BLACK_PATH_PREFIX'):   # local backend: wibo and the MIPS binutils come from the local toolchain
    env = dict(os.environ, PATH=os.environ['BLACK_PATH_PREFIX'] + os.pathsep + os.environ.get('PATH', ''))
else:
    B = '/toolchains/binutils/root/usr'  # catalog layout: mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm,...}
    env = dict(os.environ, PATH=B + '/bin:' + os.environ.get('PATH', ''), LD_LIBRARY_PATH=B + '/lib/x86_64-linux-gnu')
os.makedirs(WORK + '/job', exist_ok=True); os.chdir(WORK + '/job')
for n, d in req['files'].items():
    os.makedirs(os.path.dirname(n) or '.', exist_ok=True)
    open(n, 'wb').write(base64.b64decode(d))
open(WORK + '/job/_script.py', 'w').write(req['script'])
p = subprocess.run([sys.executable, WORK + '/job/_script.py'], capture_output=True, timeout=req['timeout'], env=env)
art = {}
for n in req['out']:
    if os.path.isfile(n):
        art[n] = base64.b64encode(open(n, 'rb').read()).decode()
print(json.dumps(dict(rc=p.returncode, out=p.stdout.decode('utf8', 'replace'),
                      err=p.stderr.decode('utf8', 'replace'), artifacts=art)))
'''


def config():
    try:
        return json.loads(CONFIG.read_text())
    except (OSError, ValueError):
        return {}


_plugin = []


def plugin():
    """The loaded plugin module, or None for the local backend."""
    if os.environ.get('BLACK_BACKEND') == 'local':
        return None
    if os.environ.get('BLACK_BACKEND') not in (None, '', 'plugin'):
        raise SystemExit("BLACK_BACKEND must be 'local' or 'plugin'")
    path = config().get('backend_plugin')
    if not path:
        if os.environ.get('BLACK_BACKEND') == 'plugin':
            raise SystemExit('BLACK_BACKEND=plugin needs "backend_plugin" in .local/config.json')
        return None
    if not _plugin:
        file = Path(path)
        file = file if file.is_absolute() else ROOT / file
        if not file.is_file():
            raise SystemExit('backend_plugin %s (.local/config.json) does not exist' % path)
        sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
        spec = importlib.util.spec_from_file_location('black_backend_plugin', file)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        if not callable(getattr(module, 'run_script', None)):
            raise SystemExit('backend plugin %s must define run_script(request, config)' % path)
        _plugin.append(module)
    return _plugin[0]


def name():
    """'local' or the plugin's NAME (default 'plugin')."""
    module = plugin()
    return 'local' if module is None else getattr(module, 'NAME', 'plugin')


def run_script(request):
    module = plugin()
    if module is None:
        return _run_script_local(request)
    return module.run_script(request, config())


def compile_standalone(request):
    module = plugin()
    if module is None:
        return _compile_local(request)
    if not callable(getattr(module, 'compile_standalone', None)):
        raise SystemExit('The backend plugin has no compile_standalone(); use trysrc.py or autodecomp.py, which batch through run_script.')
    return module.compile_standalone(request, config())


def service(action, name, files=None, script=None, timeout=180):
    """Detached long-running jobs (permuter_service.py). Needs a plugin that offers service()."""
    module = plugin()
    if module is None or not callable(getattr(module, 'service', None)):
        raise SystemExit('Detached search jobs need a backend plugin that provides service() (see tools/build/backend.py).')
    return module.service(action, name, files or {}, script, timeout, config())


def _run_script_local(request):
    """Run the wrapper on this machine with the downloaded toolchain; BLACK_WORK is a scratch directory."""
    import toolchain
    toolchain.require()
    work = tempfile.mkdtemp(prefix='black-work-')
    try:
        env = dict(os.environ, BLACK_WORK=work, **toolchain.job_environment())
        r = subprocess.run([sys.executable, '-c', WRAPPER], input=json.dumps(request).encode(), capture_output=True,
                           env=env, timeout=request['timeout'] + 60)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    if r.returncode:
        sys.stderr.write(r.stderr.decode(errors='replace'))
        raise SystemExit('Build backend failed: the local build job did not run.')
    return json.loads(r.stdout)


def _compile_local(request):
    """Run one compiler from the local toolchain in a scratch directory."""
    import toolchain
    from assembler import short_path
    toolchain.require()
    base = toolchain.root()
    compiler = request['compiler']
    root = base / 'compilers' / compiler
    if not root.is_dir():
        raise SystemExit('compiler %s is not installed; it is not part of the local toolchain' % compiler)
    with tempfile.TemporaryDirectory(prefix='black-compile-') as directory:
        work = Path(directory)
        for file, data in request['files'].items():
            path = PurePosixPath(file)
            if path.is_absolute() or '..' in path.parts:
                raise ValueError('Unsafe input path')
            (work / file).write_bytes(base64.b64decode(data, validate=True))
        env = dict(os.environ, TMPDIR=str(work), WINEDEBUG='-all')
        env['PATH'] = str(base / 'bin') + os.pathsep + env.get('PATH', '')
        flags = request['args']
        if compiler.startswith('mwcps2-'):
            command = ['wibo', str(root / 'mwccps2.exe'), *flags]
        elif (root / 'bin/ee-gcc.exe').is_file():
            backend_dir = next(d for d in sorted((root / 'lib/gcc-lib/ee').iterdir()) if d.is_dir() and d.name[0] != '.')
            backend_dir = Path(short_path(backend_dir))     # Ps2EeAs.exe crashes when its own path is long
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
