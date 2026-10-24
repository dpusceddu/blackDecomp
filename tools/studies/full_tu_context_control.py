#!/usr/bin/env python3
"""Verify that real unfinished TU context cannot leak through sorted text inputs.

Compile a caller alone and with an unfinished callee using SN 1.36. Bind that
callee to a separate assembly-backed control returning a different value. The
unfiltered context must change the linked text; the section filter must restore
exact baseline text. All SDK execution uses the build backend.
"""
import argparse
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import autodecomp as A

WORKER = r'''
import json
import subprocess
import sys
sys.path.insert(0, '.')
from elfobj import undefine_dropped, unplaced_allocated_sections
from elfinfo import Elf
results = {}
for case in ('baseline', 'leaking-context', 'filtered-context'):
    raw = open('baseline.o' if case == 'baseline' else 'context.o', 'rb').read()
    keep = {'.text.kept'}
    edited, _ = undefine_dropped(raw, keep)
    open(case + '.o', 'wb').write(edited)
    names = {'.text.kept': '.text.0000'}
    if case == 'filtered-context':
        names.update(unplaced_allocated_sections(raw, keep))
    command = ['mipsel-linux-gnu-objcopy']
    for old, new in names.items():
        command += ['--rename-section', old + '=' + new]
    subprocess.run(command + [case + '.o'], check=True)
    open('control.ld', 'w').write(
        'SECTIONS { . = 0x100000; .text : { *(SORT_BY_NAME(.text.*)) } /DISCARD/ : { *(*) } }')
    result = subprocess.run(['mipsel-linux-gnu-ld', '-EL', '-T', 'control.ld',
                             case + '.o', 'original.o', '-o', case + '.elf'],
                            capture_output=True, text=True)
    if result.returncode:
        raise RuntimeError(result.stderr)
    elf = Elf(open(case + '.elf', 'rb').read())
    results[case] = elf.content(elf.section('.text'))
assert results['baseline'] == results['filtered-context']
assert results['baseline'] != results['leaking-context']
json.dump(dict(text_bytes={name: len(data) for name, data in results.items()},
               filtered_matches_baseline=True, unfiltered_context_changes_image=True),
          open('results.json', 'w'))
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path,
                        default=ROOT / 'build/handbook-controls/context-link-control')
    args = parser.parse_args()
    output = args.output.resolve()
    if not output.is_relative_to(ROOT / 'build'):
        parser.error('compiler outputs must stay under ignored build/')
    output.mkdir(parents=True, exist_ok=True)
    sources = {
        'baseline': 'extern int pending(void); int kept(void) {return pending();}\n',
        'context': 'extern int pending(void); int kept(void) {return pending();} int pending(void) {return 23;}\n',
        'original': 'int pending(void) {return 7;}\n',
    }
    flags = ['-O0', '-G0', '-snas', '-ffunction-sections']
    for key, (rc, message, obj) in A.worker_compile(
            [(key, source, flags) for key, source in sources.items()],
            tag='full-tu-context-link-control').items():
        if rc:
            raise RuntimeError(key + ': ' + message)
        (output / (key + '.o')).write_bytes(obj)
    script = output / 'worker.py'
    script.write_text(WORKER)
    command = [sys.executable, str(ROOT / 'tools/sandbox.py'), str(script),
               '--file', 'elfobj.py=' + str(ROOT / 'tools/elfobj.py'),
               '--file', 'elfinfo.py=' + str(ROOT / 'tools/elfinfo.py'),
               '--out', 'results.json=' + str(output / 'results.json')]
    for key in sources:
        command += ['--file', key + '.o=' + str(output / (key + '.o'))]
    subprocess.run(command, cwd=ROOT, check=True)
    print((output / 'results.json').read_text())


if __name__ == '__main__':
    main()
