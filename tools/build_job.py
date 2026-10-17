# Runs inside the build backend (sent by tools/build_objects.py through tools/sandbox.py).
# Reads plan.json: {"assemble": [[src, obj], ...], "link": [ld arguments], "out": "linked.elf"}; the sources
# were unpacked from inputs.tgz. Assembles with the EE GNU assembler 2.10, links with mainline GNU ld.
import json, os, struct, subprocess, sys, tarfile
from concurrent.futures import ThreadPoolExecutor

AS = '/toolchains/compilers/ee-gcc2.96/ee/bin/as'
tarfile.open('inputs.tgz').extractall('.')
plan = json.load(open('plan.json'))


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


failed = 0
with ThreadPoolExecutor(2) as pool:
    for src, rc, msg in pool.map(assemble, plan['assemble']):
        if rc or msg:
            print('AS %s rc=%d\n%s' % (src, rc, '\n'.join(msg.split('\n')[:40])))
        failed += bool(rc)
if failed:
    print('assembler failed on %d files' % failed)
    sys.exit(1)
p = subprocess.run(['mipsel-linux-gnu-ld'] + plan['link'], capture_output=True, text=True)
print((p.stdout + p.stderr).strip()[:6000])
sys.exit(p.returncode)
