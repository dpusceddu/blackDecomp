#!/usr/bin/env python3
"""Assemble the split sources and link them, inside the build backend (never on this host).

Usage: build_objects.py WORK
Packs the post-processed assembly (build/<slug>/asm), splat's data assembly (asm/<slug>/data), the macro include,
the binary blobs (data/<slug>) and the linker script, runs tools/build_job.py through tools/sandbox.py
(EE assembler 2.10 per file, mainline MIPS ld once; offline), and writes build/<slug>/linked.elf and link.map.
"""
import io, json, subprocess, sys, tarfile, time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    slug = sys.argv[1]  # the work name (asm/, build/ and data/ directory names)
    build = ROOT / 'build' / slug
    t0 = time.time()
    srcs = sorted(build.glob('asm/text.*.s')) + sorted((ROOT / 'asm' / slug / 'data').glob('*.s'))
    extra = [ROOT / 'include/macro.inc', build / 'link.ld'] + sorted((ROOT / 'data' / slug).glob('*.bin'))
    buf = io.BytesIO()
    with tarfile.open(fileobj=buf, mode='w:gz') as tar:
        for p in srcs + extra:
            tar.add(p, arcname=p.relative_to(ROOT).as_posix())
    (build / 'inputs.tgz').write_bytes(buf.getvalue())
    plan = dict(assemble=[], out='linked.elf')
    objs = (build / 'objects.txt').read_text().split()
    by_obj = {}
    for p in srcs:
        rel = p.relative_to(build / 'asm') if p.is_relative_to(build / 'asm') else p.relative_to(ROOT / 'asm' / slug)
        by_obj['build/%s/obj/%s.o' % (slug, rel.with_suffix('').as_posix())] = p.relative_to(ROOT).as_posix()
    missing = [o for o in objs if o not in by_obj]
    if missing:
        raise SystemExit('no source for objects: %s' % missing[:3])
    plan['assemble'] = [[by_obj[o], o] for o in objs]
    plan['link'] = ['-m', 'elf32ltsmip', '-nostdlib', '-static', '-z', 'norelro', '-z', 'noseparate-code',
                    '--no-warn-rwx-segments', '-T', 'build/%s/link.ld' % slug, '-Map', 'linked.map',
                    '-o', 'linked.elf'] + objs
    (build / 'plan.json').write_text(json.dumps(plan))
    cmd = [sys.executable, str(ROOT / 'tools/sandbox.py'), str(ROOT / 'tools/build_job.py'), '--timeout', '900',
           '--file', 'inputs.tgz=' + str(build / 'inputs.tgz'), '--file', 'plan.json=' + str(build / 'plan.json'),
           '--out', 'linked.elf=' + str(build / 'linked.elf'), '--out', 'linked.map=' + str(build / 'link.map')]
    (build / 'linked.elf').unlink(missing_ok=True)
    rc = subprocess.run(cmd).returncode
    print('assemble+link: %.1fs, rc=%d' % (time.time() - t0, rc))
    return rc


if __name__ == '__main__':
    sys.exit(main())
