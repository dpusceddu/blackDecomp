#!/usr/bin/env python3
"""Assemble and compile what changed, then link, in one call to the build toolchain .

Usage: build_objects.py SLUG
Reads build/<GAME_ID>/objects.json and link.ld (tools/build/make_ld.py). Every object (one per function, shared constant run,
splat data file, or compiled unit) is cached by the hash of its inputs in build/<GAME_ID>/cache/, so only changed
sources are assembled or compiled. One build call receives the changed sources plus the cached objects, builds
the missing ones, links everything with mainline GNU ld, and returns linked.elf, link.map and the new objects.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import hashlib, io, json, subprocess, sys, tarfile, time
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / d) for d in ('', 'build', 'pipeline', 'maint')]
from units import dependencies, non_matching
from build_telemetry import record as record_build

ROOT = Path(__file__).resolve().parents[2]
VERSION = 'v1'  # bump to invalidate the cache when the build recipe changes


def sha(*parts):
    h = hashlib.sha256()
    for p in parts:
        h.update(p if isinstance(p, bytes) else str(p).encode())
        h.update(b'\0')
    return h.hexdigest()[:24]


def main():
    slug = sys.argv[1]
    shared = ROOT / 'build' / slug              # split assembly and the object cache are shared by both builds
    build = ROOT / 'build' / (slug + '-nm' if non_matching() else slug)   # link script, plan, ELF: build/<GAME_ID>-nm/ for --non-matching
    build.mkdir(parents=True, exist_ok=True)
    cache = shared / 'cache'
    cache.mkdir(exist_ok=True)
    t0 = time.time()
    objects = json.loads((build / 'objects.json').read_text())
    files = {}   # archive name -> path
    plan = dict(assemble=[], compile=[], rename=[], pack='newobjs.tgz', out='linked.elf')
    keys, have = {}, 0
    compile_only = '--compile-only' in sys.argv   # build the missing source units, do not link
    macros = (ROOT / 'include/macro.inc').read_bytes()
    for o in objects:
        name = o['name']
        if o['kind'] == 'asm':
            src = ROOT / o['src']
            data = src.read_bytes()
            extra = b''
            for line in data.split(b'\n'):
                if line.startswith(b'.incbin'):
                    blob = Path(line.decode().split('"')[1])
                    extra += (ROOT / blob).read_bytes()
            key = sha('as', VERSION, data, extra, macros)
            deps = [Path(o['src'])] + ([Path(line.decode().split('"')[1]) for line in data.split(b'\n')
                                        if line.startswith(b'.incbin')])
            job = [o['src'], 'obj/%s.o' % name]
        else:
            deps = dependencies(o['src'])
            key = sha('cc', VERSION, o['compiler'], json.dumps(o['flags']), *[(ROOT / d).read_bytes() for d in deps])
            if any(f.startswith('--assembler=') for f in o['flags']):
                key = sha(key, (ROOT / 'tools/build/assembler.py').read_bytes())
            job = dict(src=o['src'], obj='obj/%s.o' % name, compiler=o['compiler'],
                       args=list(o['flags']) + ['-I', 'include'])
        keys[name] = key
        # compile_only: `prepare` validates natural tail padding against the next real input section, which needs
        # the assembled objects too. They are cached by the first pass (a clean build assembles them here, once);
        # the link only packs and renames them.
        if o.get('rename') and not compile_only:
            plan['rename'].append(dict(obj='obj/%s.o' % name, sections=o['rename'], redefine=o.get('redefine', {}), trim=o.get('trim', {})))
        cached = cache / (key + '.o')
        if cached.exists():
            if not compile_only:
                files['obj/%s.o' % name] = cached
            have += 1
        else:
            for d in deps:
                files[d.as_posix()] = ROOT / d
            plan['assemble' if o['kind'] == 'asm' else 'compile'].append(job)
    deps_all = sorted({d.as_posix() for o in objects if o['kind'] == 'cc' for d in dependencies(o['src'])})
    if compile_only:
        (build / 'compile.d').write_text('%s/compiled.stamp: %s\n' % (build.relative_to(ROOT).as_posix(), ' '.join(deps_all)))
    else:
        (build / 'link.d').write_text('%s/linked.elf: %s\n' % (build.relative_to(ROOT).as_posix(), ' '.join(deps_all)))
    files['include/macro.inc'] = ROOT / 'include/macro.inc'
    files['link.ld'] = build / 'link.ld'
    files['tools/elfobj.py'] = ROOT / 'tools/build/elfobj.py'          # the job (build_job.py) imports them from its own tools/
    files['tools/assembler.py'] = ROOT / 'tools/build/assembler.py'
    if not compile_only:
        plan['link'] = ['-m', 'elf32ltsmip', '-nostdlib', '-static', '-z', 'norelro', '-z', 'noseparate-code',
                        '--no-warn-rwx-segments', '-T', 'link.ld', '-Map', 'linked.map', '-o', 'linked.elf'] + \
                       ['obj/%s.o' % o['name'] for o in objects]
    # the linker script lists objects in section order; ld takes the file order from the script, the command line
    # only has to name every file.
    buf = io.BytesIO()
    with tarfile.open(fileobj=buf, mode='w:gz', compresslevel=1) as tar:
        for arc, p in sorted(files.items()):
            tar.add(p, arcname=arc)
    (build / 'inputs.tgz').write_bytes(buf.getvalue())
    (build / 'plan.json').write_text(json.dumps(plan))
    t1 = time.time()
    (build / 'linked.elf').unlink(missing_ok=True)
    cmd = [sys.executable, str(ROOT / 'tools/build/sandbox.py'), str(ROOT / 'tools/build/build_job.py'), '--timeout', '1800',
           '--file', 'inputs.tgz=' + str(build / 'inputs.tgz'), '--file', 'plan.json=' + str(build / 'plan.json'),
           '--out', 'linked.elf=' + str(build / 'linked.elf'), '--out', 'linked.map=' + str(build / 'link.map'),
           '--out', 'newobjs.tgz=' + str(build / 'newobjs.tgz'), '--out', 'results.json=' + str(build / 'results.json')]
    (build / 'newobjs.tgz').unlink(missing_ok=True)
    (build / 'results.json').unlink(missing_ok=True)
    call_id = record_build(build, 'compile-only' if compile_only else 'link', 'submitted',
                           compile_jobs=len(plan['compile']), assemble_jobs=len(plan['assemble']),
                           cached_objects=have, pack_seconds=t1 - t0)
    r = subprocess.run(cmd, capture_output=True, text=True)
    if non_matching() and compile_only:
        rc = r.returncode          # compile errors are expected: the fallback below decides
    record_build(build, 'compile-only' if compile_only else 'link', 'completed', call_id,
                 worker_rc=r.returncode, worker_seconds=time.time() - t1,
                 has_results=(build / 'results.json').exists())
    rc = r.returncode
    sys.stdout.write(r.stdout[-20000:])
    sys.stderr.write(r.stderr[-5000:])
    (build / 'link.log').write_text(r.stdout + r.stderr)
    (build / 'objects_cache.json').write_text(json.dumps({n: 'cache/%s.o' % k for n, k in keys.items()}))
    new = 0
    if (build / 'newobjs.tgz').exists():
        with tarfile.open(build / 'newobjs.tgz') as tar:
            for m in tar.getmembers():
                name = m.name[len('obj/'):-len('.o')]
                if name in keys and m.isfile():
                    (cache / (keys[name] + '.o')).write_bytes(tar.extractfile(m).read())
                    new += 1
    if non_matching() and compile_only and (build / 'results.json').exists():
        # a draft that does not compile keeps its translation unit as it is in the matching build (docs/build.md)
        results = json.loads((build / 'results.json').read_text())
        fallback_path = build / 'nm_fallback.json'
        fallback = set(json.loads(fallback_path.read_text())) if fallback_path.exists() else set()
        failed = {o['name'][len('units/'):] for o in objects if o['kind'] == 'cc' and results.get(o['src'], {}).get('rc')}
        if failed - fallback:
            fallback_path.write_text(json.dumps(sorted(fallback | failed)))
            print('non-matching: %d translation units keep their matching version (compile errors)' % len(failed - fallback))
            return 75      # the caller regenerates the units and runs again
    if rc == 0 and not compile_only and not non_matching():   # drop cached objects nothing refers to any more
        live = {k + '.o' for k in keys.values()}
        stale = [p for p in cache.iterdir() if p.name not in live]
        if len(stale) > 500:
            for p in stale:
                p.unlink()
    print('build: %d objects cached, %d built; pack %.1fs, worker %.1fs, rc=%d' % (
        have, new, t1 - t0, time.time() - t1, rc))
    return rc


if __name__ == '__main__':
    sys.exit(main())
