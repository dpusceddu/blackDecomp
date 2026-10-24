"""Job for tools/objdiff.py (runs through tools/sandbox.py): build the target and base objects objdiff compares.

Reads plan.json and inputs.tgz (sent by objdiff.py):
  units: [{name, base_in, redefine, functions: [{symbol, size, asm}]}]
For each unit it writes
  target/<name>.o   the original machine code of the unit's functions: the split assembly of each function, assembled
                    with the EE assembler, symbols named func_XXXXXXXX with their original sizes
  base/<name>.o     the object compiled from source, its symbols renamed to the same func_/D_ names (objcopy)
and packs both directories into out.tgz.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, os, subprocess, sys, tarfile
from concurrent.futures import ThreadPoolExecutor

TOOLCHAINS = os.environ.get('BLACK_TOOLCHAINS', '/toolchains')
BINUTILS = os.environ.get('BLACK_BINUTILS_PREFIX', 'mipsel-linux-gnu-')
AS = TOOLCHAINS + '/compilers/ee-gcc2.96/ee/bin/as'
tarfile.open('inputs.tgz').extractall('.')
plan = json.load(open('plan.json'))
os.makedirs('target', exist_ok=True)
os.makedirs('base', exist_ok=True)


def build(unit):
    name = unit['name']
    lines = []
    for f in unit['functions']:
        lines.append('.include "%s"' % f['asm'])
        lines.append('.type %s, @function' % f['label'])
        lines.append('.size %s, %d' % (f['label'], f['size']))
    source = 'target/%s.s' % name
    os.makedirs(os.path.dirname(source), exist_ok=True)
    open(source, 'w').write('\n'.join(lines) + '\n')
    p = subprocess.run([AS, '-I', 'include', '-o', 'target/%s.o' % name, source], capture_output=True, text=True)
    errors = (p.stdout + p.stderr).strip()
    if not unit['base_in']:
        return name, p.returncode, errors
    os.makedirs(os.path.dirname('base/%s.o' % name), exist_ok=True)
    mapping = 'base/%s.syms' % name
    open(mapping, 'w').write(''.join('%s %s\n' % kv for kv in unit['redefine'].items()))
    q = subprocess.run([BINUTILS + 'objcopy', '--redefine-syms', mapping, unit['base_in'], 'base/%s.o' % name],
                       capture_output=True, text=True)
    return name, p.returncode or q.returncode, errors + (q.stderr or '').strip()


failed = 0
with ThreadPoolExecutor(2) as pool:
    for name, rc, message in pool.map(build, plan['units']):
        if rc:
            failed += 1
            print('FAILED %s\n%s' % (name, message[:600]))
with tarfile.open('out.tgz', 'w:gz', compresslevel=1) as tar:
    for unit in plan['units']:
        for path in ('target/%s.o' % unit['name'], 'base/%s.o' % unit['name']):
            if os.path.exists(path):
                tar.add(path)
print('%d units, %d failed' % (len(plan['units']), failed))
sys.exit(1 if failed else 0)
