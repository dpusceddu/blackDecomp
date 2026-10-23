"""Worker-side job runner: assemble, compile, link and pack inside the isolated container (sent by build_objects.py).

Runs inside the build backend (sent by tools/build_objects.py through tools/sandbox.py).
Reads plan.json:
  assemble: [[src, obj], ...]     EE GNU assembler 2.10 (objects keep whatever the assembler writes)
  compile:  [{src, obj, compiler, args}, ...]   SN GCC under wibo; the object's symbol table is normalised for ld
  link:     [ld arguments]        mainline GNU ld, run once if present
  pack:     name of a tgz that receives every object assembled or compiled in this job
The inputs were unpacked from inputs.tgz (sources, cached objects under obj/, include/, the linker script).
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, os, struct, subprocess, sys, tarfile
from concurrent.futures import ThreadPoolExecutor

AS = '/toolchains/compilers/ee-gcc2.96/ee/bin/as'
CC = '/toolchains/compilers'
tarfile.open('inputs.tgz').extractall('.')
plan = json.load(open('plan.json'))
sys.path.insert(0, 'tools')


def expand_incbin(src):
    """The EE assembler has no .incbin: replace it by .word lines (blobs are multiples of 4 bytes)."""
    text = open(src).read()
    if '.incbin' not in text:
        return src
    out = []
    for line in text.split('\n'):
        if line.startswith('.incbin'):
            blob = open(line.split('"')[1], 'rb').read()
            assert len(blob) % 4 == 0
            words = struct.unpack('<%dI' % (len(blob) // 4), blob)
            out += ['.word ' + ', '.join('0x%08x' % w for w in words[i:i + 8]) for i in range(0, len(words), 8)]
        else:
            out.append(line)
    dst = src + '.expanded.s'
    open(dst, 'w').write('\n'.join(out) + '\n')
    return dst


def assemble(job):
    src, obj = job
    os.makedirs(os.path.dirname(obj), exist_ok=True)
    src = expand_incbin(src)
    p = subprocess.run([AS, '-I', 'include', '-o', obj, src], capture_output=True, text=True)
    return src, p.returncode, (p.stdout + p.stderr).strip()


def compile_one(job):
    from elfobj import normalize_object
    from assembler import compile_with_assembler
    root = '%s/%s' % (CC, job['compiler'])
    if job['compiler'].startswith('mwcps2-'):
        os.makedirs(os.path.dirname(job['obj']), exist_ok=True)
        cmd = ['wibo', root + '/mwccps2.exe'] + job['args'] + ['-c', job['src'], '-o', job['obj']]
        try:
            p = subprocess.run(cmd, env=dict(os.environ, TMPDIR='/work', WINEDEBUG='-all'),
                               capture_output=True, text=True, timeout=job.get('timeout', 300))
        except subprocess.TimeoutExpired:
            return job['src'], 124, 'compiler timeout'
        if p.returncode == 0 and os.path.exists(job['obj']):
            data = open(job['obj'], 'rb').read()
            open(job['obj'], 'wb').write(normalize_object(data))
        return job['src'], p.returncode, (p.stdout + p.stderr).strip()
    if not os.path.isfile(root + '/bin/ee-gcc.exe'):          # native Linux compilers (Sony 2.9 / 2.96)
        os.makedirs(os.path.dirname(job['obj']), exist_ok=True)
        env = dict(os.environ, TMPDIR='/work')
        prefix = [root + '/bin/ee-gcc', '-B' + root + '/bin/ee-']
        try:
            p = compile_with_assembler(prefix, job['args'], job['src'], job['obj'], env, job.get('timeout', 300))
        except subprocess.TimeoutExpired:
            return job['src'], 124, 'compiler timeout'
        if p.returncode == 0 and os.path.exists(job['obj']):
            data = open(job['obj'], 'rb').read()
            open(job['obj'], 'wb').write(normalize_object(data))
        msg = '\n'.join(l for l in (p.stdout + p.stderr).strip().split('\n') if 'file path prefix' not in l)
        return job['src'], p.returncode, msg
    versions = root + '/lib/gcc-lib/ee'
    backend = next(versions + '/' + v for v in sorted(os.listdir(versions))
                   if not v.startswith('.') and os.path.isdir(versions + '/' + v))
    env = dict(os.environ, TMPDIR='/work', WINEDEBUG='-all', WIBO_PATH=backend)
    os.makedirs(os.path.dirname(job['obj']), exist_ok=True)
    prefix = ['wibo', root + '/bin/ee-gcc.exe', '-B' + backend + '/']
    try:
        p = compile_with_assembler(prefix, job['args'], job['src'], job['obj'], env, job.get('timeout', 300))
    except subprocess.TimeoutExpired:       # a pathological candidate must not take the whole batch down
        return job['src'], 124, 'compiler timeout'
    if p.returncode == 0 and os.path.exists(job['obj']):
        data = open(job['obj'], 'rb').read()
        open(job['obj'], 'wb').write(normalize_object(data))
    return job['src'], p.returncode, (p.stdout + p.stderr).strip()


failed = 0
built = []
results = {}
with ThreadPoolExecutor(2) as pool:
    for src, rc, msg in pool.map(assemble, plan.get('assemble', [])):
        if rc or msg:
            print('AS %s rc=%d\n%s' % (src, rc, '\n'.join(msg.split('\n')[:40])))
        failed += bool(rc)
        results[src] = dict(rc=rc, msg=msg)
    for src, rc, msg in pool.map(compile_one, plan.get('compile', [])):
        if rc or msg:
            print('CC %s rc=%d\n%s' % (src, rc, '\n'.join(msg.split('\n')[:80])))
        failed += bool(rc)
        results[src] = dict(rc=rc, msg=msg)
json.dump(results, open('results.json', 'w'))
built = [o for _, o in plan.get('assemble', [])] + [j['obj'] for j in plan.get('compile', [])]
if plan.get('pack'):
    with tarfile.open(plan['pack'], 'w:gz', compresslevel=1) as tar:
        for o in built:
            if os.path.exists(o):
                tar.add(o)
if failed:
    print('%d jobs failed' % failed)
    sys.exit(1)
for r in plan.get('rename', []):   # give a unit's sections the sort key of the slot they take over
    from elfobj import undefine_dropped, trim_sections
    raw = open(r['obj'], 'rb').read()
    edited, n = undefine_dropped(raw, set(r['sections']))   # duplicates in sections that are not linked
    if r.get('trim'):
        edited = trim_sections(edited, r['trim'])
    open(r['obj'], 'wb').write(edited)
    args = ['mipsel-linux-gnu-objcopy']
    for old, new in r['sections'].items():
        args += ['--rename-section', '%s=%s' % (old, new)]
    for old, new in r.get('redefine', {}).items():
        args += ['--redefine-sym', '%s=%s' % (old, new)]
    p = subprocess.run(args + [r['obj']], capture_output=True, text=True)
    if p.returncode:
        print('objcopy %s: %s' % (r['obj'], p.stderr))
        sys.exit(1)
if plan.get('link'):
    p = subprocess.run(['mipsel-linux-gnu-ld'] + plan['link'], capture_output=True, text=True)
    print((p.stdout + p.stderr).strip()[:6000])
    sys.exit(p.returncode)
