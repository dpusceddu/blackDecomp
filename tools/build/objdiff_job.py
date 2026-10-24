"""Job for tools/objdiff.py (runs through tools/build/sandbox.py): build the target and base objects objdiff compares.

Reads plan.json and inputs.tgz (sent by objdiff.py):
  units: [{name, base_in, redefine, sections, symbols, functions: [{symbol, size, asm}]}]
For each unit it writes
  target/<name>.o   the original machine code of the unit's functions: the split assembly of each function, assembled
                    with the EE assembler, symbols named func_XXXXXXXX with their original sizes (and the ELF flags of base/)
  base/<name>.o     the object compiled from source, its symbols and function sections renamed to the same func_/D_ names, and the unit's own
                    data named where the original code refers to it by address (objcopy)
and packs both directories into out.tgz.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import json, os, re, subprocess, sys, tarfile
from concurrent.futures import ThreadPoolExecutor

TOOLCHAINS = os.environ.get('BLACK_TOOLCHAINS', '/toolchains')
BINUTILS = os.environ.get('BLACK_BINUTILS_PREFIX', 'mipsel-linux-gnu-')
AS = TOOLCHAINS + '/compilers/ee-gcc2.96/ee/bin/as'
tarfile.open('inputs.tgz').extractall('.', **({'filter': 'data'} if hasattr(tarfile, 'data_filter') else {}))
sys.path.insert(0, 'tools')
import elfobj                                  # shipped in inputs.tgz
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
    renames = ['--rename-section=%s=%s' % kv for kv in (unit.get('sections') or {}).items()]
    adds = ['--add-symbol=%s=%s:%d,global,object' % (n, section, offset) for n, (section, offset) in sorted((unit.get('symbols') or {}).items())]
    q = subprocess.run([BINUTILS + 'objcopy', '--redefine-syms', mapping] + renames + adds + [unit['base_in'], 'base/%s.o' % name],
                       capture_output=True, text=True)
    if not q.returncode:
        base, target = open('base/%s.o' % name, 'rb').read(), open('target/%s.o' % name, 'rb').read()
        open('target/%s.o' % name, 'wb').write(elfobj.copy_header_flags(target, base))
        open('base/%s.o' % name, 'wb').write(elfobj.literal_as_gprel(base))
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
