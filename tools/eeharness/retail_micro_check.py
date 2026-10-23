#!/usr/bin/env python3
"""Bounded VCALLMS execution of existing retail VU0 uploads on synthetic inputs.

This checks execution support and replay determinism, not correctness against a
hardware oracle, game-state coverage, or equivalence of any recovered function.
No input game bytes or generated instruction streams leave ignored directories.
"""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from elfinfo import Elf
from vu0_micro import UPLOADS


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--elf',type=Path,default=ROOT/'orig/usa-retail/files/SLUS_213.76')
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/retail-micro-check.json')
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    elf = Elf(args.elf.read_bytes()); text,micro = elf.section('.text'),elf.section('.vutext')
    calls = collections.defaultdict(set)
    for i,(word,) in enumerate(struct.iter_unpack('<I',elf.content(text))):
        if word&0xfe00003f != 0x4a000038:
            continue
        pc = text['addr']+i*4
        for upload in UPLOADS:
            if upload['callers'][0] <= pc < upload['callers'][1]:
                calls[upload['name']].add((word>>6&0x7fff)*8)
    cases = []
    for upload in UPLOADS:
        pairs = []
        for address,dest,size in upload['payloads']:
            payload = elf.content(micro)[address-micro['addr']:address-micro['addr']+size]
            if len(payload) != size:
                raise ValueError('retail upload extends outside .vutext')
            pairs += [(dest+i*8,lo,hi) for i,(lo,hi) in enumerate(struct.iter_unpack('<II',payload))]
        for entry in sorted(calls[upload['name']]):
            for seed in [0,1]:
                lines = ['case']
                lines += ['vi %x %x'%(r,seed) for r in range(1,16)]
                lines += ['vf %x %s'%(r,' '.join(['3f800000' if seed else '0']*4)) for r in range(1,32)]
                lines += ['pair %x %x %x'%pair for pair in pairs]
                lines += ['run-ee-try %x 10000'%entry]
                stream = ('\n'.join(lines)+'\n').encode()
                a = subprocess.run([str(args.harness),'vu'],input=stream,capture_output=True,check=True).stdout
                b = subprocess.run([str(args.harness),'vu'],input=stream,capture_output=True,check=True).stdout
                rows = a.decode().splitlines()
                tag,stop,issued,distinct = rows[0].split()
                if tag != 'result':
                    raise ValueError('unexpected retail micro diagnostic')
                cases.append(dict(upload=upload['name'],entry=hex(entry),seed=seed,stop=stop,
                                  issued_pairs=int(issued),distinct_pairs=int(distinct),repeat_agreement=a == b and 'replay equal' in rows,
                                  diagnostics=rows[1:]))
    report = dict(cases=cases,reference_sha256=hashlib.sha256(elf.data).hexdigest(),
                  harness_sha256=hashlib.sha256(args.harness.read_bytes()).hexdigest(),gate_1='not evaluated by this individual check',
                  scope='Synthetic-input execution and repeatability only; no hardware result oracle or gameplay coverage.')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    counts = collections.Counter(case['stop'] for case in cases)
    print('Retail VU0:',len(cases),'synthetic runs,',dict(counts),'; repeats agree:',all(c['repeat_agreement'] for c in cases))
    for case in cases:
        if case['stop'] != 'returned':
            print(case['upload'],case['entry'],case['seed'],case['stop'],case['diagnostics'])
    return any(not c['repeat_agreement'] or c['stop'] == 'fault' for c in cases)


if __name__ == '__main__':
    raise SystemExit(main())
