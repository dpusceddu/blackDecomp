#!/usr/bin/env python3
"""Run a Python script inside the same build backend that tools/compile.py uses.

Usage: sandbox.py SCRIPT.py [--file NAME=PATH ...] [--out NAME=PATH ...]
The script runs as `python3` in the container with the private toolchain catalog mounted read-only at
/toolchains and a scratch /work. PATH includes the catalog's MIPS binutils (`mipsel-linux-gnu-ld`, `-objcopy`,
`-readelf`, `-objdump`, ...); the EE assembler is /toolchains/compilers/ee-gcc2.96/ee/bin/as. Each --file is copied to /work/NAME first (read it from the script);
each --out copies /work/NAME back to PATH afterwards. The script's stdout/stderr are relayed. The
network is disabled; nothing persists. Reads .local/config.json (private).
The service_request() API provides detached jobs with the same isolation and a
durable named /work volume; tools/permuter_service.py owns that lifecycle.
"""
import argparse, base64, json, re, shlex, subprocess, sys, uuid
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
WRAPPER = r'''
import base64, json, sys, os, subprocess
req = json.load(sys.stdin)
B = '/toolchains/binutils/root/usr'  # catalog: mipsel-linux-gnu-{ld,objcopy,readelf,objdump,nm,...}
env = dict(os.environ, PATH=B + '/bin:' + os.environ.get('PATH', ''), LD_LIBRARY_PATH=B + '/lib/x86_64-linux-gnu')
os.makedirs('/work/job', exist_ok=True); os.chdir('/work/job')
for n, d in req['files'].items():
    os.makedirs(os.path.dirname(n) or '.', exist_ok=True)
    open(n, 'wb').write(base64.b64decode(d))
open('/work/job/_script.py', 'w').write(req['script'])
p = subprocess.run([sys.executable, '/work/job/_script.py'], capture_output=True, timeout=req['timeout'], env=env)
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
    req = dict(files=files, script=a.script.read_text(), out=list(outs), timeout=a.timeout)
    reply = run_batch(req)
    sys.stdout.write(reply['out'])
    sys.stderr.write(reply['err'])
    for name, dest in outs.items():
        if name in reply['artifacts']:
            Path(dest).parent.mkdir(parents=True, exist_ok=True)
            Path(dest).write_bytes(base64.b64decode(reply['artifacts'][name]))
    return reply['rc']


if __name__ == '__main__':
    sys.exit(main())
