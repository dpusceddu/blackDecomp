#!/usr/bin/env python3
"""Run a build job script with the compilers, assembler and binutils of the selected backend.

Usage: sandbox.py SCRIPT.py [--file NAME=PATH ...] [--out NAME=PATH ...]
Backends (see tools/backend.py): `local` (default) runs the script on this machine with the toolchain that
`tools/toolchain.py install` downloads (BLACK_TOOLCHAINS points at it, BLACK_WORK is a scratch directory); an optional plugin named in the ignored .local/config.json runs it elsewhere.
In both cases the script sees the compiler catalog under $BLACK_TOOLCHAINS (/toolchains in the container) and the
MIPS binutils (`mipsel-linux-gnu-ld`, `-objcopy`, ...) on PATH; the EE assembler is
$BLACK_TOOLCHAINS/compilers/ee-gcc2.96/ee/bin/as. Each --file is copied to $BLACK_WORK/job/NAME first (read it from
the script); each --out copies that file back to PATH afterwards. The script's stdout/stderr are relayed.
The backend plugin also offers service_request(): detached jobs with the same isolation and a durable named
volume, which tools/permuter_service.py uses.
"""
import argparse, base64, json, os, re, shlex, shutil, subprocess, sys, tempfile, uuid
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import backend

ROOT = Path(__file__).resolve().parents[1]
WRAPPER = r'''
import base64, json, sys, os, subprocess
req = json.load(sys.stdin)
WORK = os.environ.get('BLACK_WORK', '/work')
if os.environ.get('BLACK_PATH_PREFIX'):   # local backend: wibo and the MIPS binutils come from the local toolchain
    env = dict(os.environ, PATH=os.environ['BLACK_PATH_PREFIX'] + os.pathsep + os.environ.get('PATH', ''))
else:
    B = '/toolchains/binutils/root/usr'  # catalog: mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm,...}
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


def service_request(action, name, *, files=None, script=None, timeout=180):
    """Detached search jobs need a build backend that provides them."""
    raise SystemExit('Detached search jobs need a build backend that provides them.')


def run_batch(request):
    """Run the batch with the build backend configured for this checkout."""
    raise SystemExit('Build backend failed; check the build backend configuration.')


def main():
    ap = argparse.ArgumentParser()
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
    if backend.name() == 'local':
        reply = run_local(dict(files=files, script=a.script.read_text(), out=list(outs), timeout=a.timeout))
        return finish(reply, outs)
    req = dict(files=files, script=a.script.read_text(), out=list(outs), timeout=a.timeout)
    return finish(run_batch(req), outs)


def run_local(req):
    """Run the wrapper on this machine with the downloaded toolchain; BLACK_WORK is a scratch directory."""
    import toolchain
    toolchain.require()
    work = tempfile.mkdtemp(prefix='black-work-')
    try:
        env = dict(os.environ, BLACK_WORK=work, **toolchain.job_environment())
        r = subprocess.run([sys.executable, '-c', WRAPPER], input=json.dumps(req).encode(), capture_output=True,
                           env=env, timeout=req['timeout'] + 60)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    if r.returncode:
        sys.stderr.write(r.stderr.decode(errors='replace'))
        raise SystemExit('Build backend failed: the local build job did not run.')
    return json.loads(r.stdout)


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
