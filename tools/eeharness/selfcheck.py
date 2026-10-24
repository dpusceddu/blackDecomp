#!/usr/bin/env python3
"""Replay exact source controls and detect a worker-compiled source mutation.

This is a Phase 1 harness self-check with synthetic register states. It cannot
qualify any function as equivalent or substitute for gameplay state coverage.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
from units import load_units


def command(args):
    return subprocess.run([str(arg) for arg in args], cwd=ROOT, check=True,
                          text=True, capture_output=True).stdout.strip()


def simple_control(words):
    if not words or words[0] != 0x03e00008:
        return False
    # JR RA with one side-effect-free immediate instruction in its delay slot.
    # These controls intentionally avoid dereferencing arbitrary synthetic args.
    delay = words[1]
    return delay == 0 or (delay >> 26 in (9, 0xd, 0xf) and (delay >> 21 & 31) == 0)


def check(harness):
    command(['ninja'])
    original_path = ROOT / 'orig/SLUS_213.76/SLUS_213.76'
    source_path = ROOT / 'build/SLUS_213.76/SLUS_213.76.elf'
    command([sys.executable, 'tools/check_elf.py', 'SLUS_213.76', source_path])
    original = Elf(original_path.read_bytes())
    text = original.section('.text')
    data = original.content(text)
    functions = [f for u in load_units(variant='SLUS_213.76') for f in u['functions']
                 if f.get('status') == 'source' and 8 <= f.get('size',0) <= 80]
    controls = []
    for f in sorted(functions, key=lambda f: f['addr']):
        words = struct.unpack_from('<%dI' % (f['size']//4), data, f['addr'] - text['addr'])
        if f['size'] == 8 and simple_control(words):
            controls.append(f['addr'])
    controls = controls[:32]
    if len(controls) < 8:
        raise ValueError('insufficient registered exact-source controls')
    floating = []
    for f in sorted(functions,key=lambda f:f['addr']):
        words = struct.unpack_from('<%dI' % (f['size']//4),data,f['addr']-text['addr'])
        if (any(word>>26 == 0x11 for word in words) and 0x03e00008 in words and
                all(word>>26 in (0,0x11,9,0xd,0xf) for word in words)):
            floating.append(f['addr'])
    controls += floating
    comparison = command([harness, 'compare', original_path, source_path, *map(hex, controls)])

    # The existing exact source at this address returns 1. Recompile an authored
    # C control normally and with a changed source constant, without editing a TU.
    address = 0x106058
    if not any(f['addr'] == address for f in functions):
        raise ValueError('registered exact negative-control target is unavailable')
    work = ROOT / 'build/eeharness/selfcheck'
    work.mkdir(parents=True, exist_ok=True)
    outcomes = []
    for value in (1, 2):
        obj_path = work / ('constant-%d.o' % value)
        command([sys.executable, 'tools/compile.py', 'ee-gcc2.95.3-136', '-O2', '-G0', '-snas',
                 '-DEE_CONTROL_VALUE=%d' % value, '-c', 'tests/toolchain/eeharness_control.c', '-o', obj_path])
        obj = Elf(obj_path.read_bytes())
        symbols = [s for s in obj.symbols() if s['name'] == 'eeharness_constant' and s['shndx']]
        if len(symbols) != 1 or symbols[0]['size'] != 8:
            raise ValueError('unexpected compiled control shape')
        symbol = symbols[0]
        section = obj.sections[symbol['shndx']]
        if any(s['type'] in (4, 9) and s['info'] == section['index'] and s['size'] for s in obj.sections):
            raise ValueError('control must have no relocations')
        body = obj.content(section)[symbol['value']:symbol['value']+symbol['size']]
        offset = text['offset'] + address - text['addr']
        if value == 1 and original.data[offset:offset+8] != body:
            raise ValueError('positive control did not byte-match the original')
        candidate = bytearray(original.data)
        candidate[offset:offset+len(body)] = body
        path = work / ('constant-%d.elf' % value)
        path.write_bytes(candidate)
        result = subprocess.run([str(harness), 'compare', str(original_path), str(path), hex(address)],
                                capture_output=True, text=True)
        if value == 1 and result.returncode:
            raise ValueError('exact compiled source diverged: '+result.stderr)
        if value == 2 and (result.returncode != 1 or 'DIFFERENCE' not in result.stderr):
            raise ValueError('source mutation was not detected: '+result.stdout+result.stderr)
        outcomes.append(dict(source_constant=value, result='agreement' if value == 1 else 'mutation detected'))
    return dict(controls=[hex(x) for x in controls], states_per_control=32,
                harness_sha256=hashlib.sha256(harness.read_bytes()).hexdigest(),
                floating_controls=[hex(x) for x in floating],
                exact_control_executions=len(controls)*32, source_mutation=outcomes,
                reference_sha256=hashlib.sha256(original.data).hexdigest(),
                comparison=comparison, input_kind='synthetic harness controls', gate_1='not evaluated by this individual check')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness', type=Path, default=ROOT / 'build/eeharness/host/eeharness')
    args = parser.parse_args()
    try:
        report = check(args.harness)
        path = ROOT / 'build/eeharness/selfcheck.json'
        path.write_text(json.dumps(report, indent=2)+'\n')
        print(report['comparison'])
        print('OK worker-compiled exact control and deliberately mutated source: mutation detected.')
        print('Individual check only; run gate1.py for the combined functional gate.')
    except (ValueError, subprocess.CalledProcessError) as error:
        print(str(error), file=sys.stderr)
        if isinstance(error, subprocess.CalledProcessError):
            print(error.stderr, file=sys.stderr)
        return 1
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
