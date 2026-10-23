#!/usr/bin/env python3
"""Check VU0 integer macro operations against published hardware result logs."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]


def check(harness,directory):
    path = directory/'vu-vu0_macro-integer.expected'
    # Values loaded by the original fixture, narrowed by its VILWR instructions.
    constants = dict(ZERO=0,S16_MAX=0x7fff,S16_MIN=0x8000,S32_MAX=0xffff,S32_MIN=0,
                     S64_MAX=0xffff,S64_MIN=0,NEGONE=0xffff,ONE=1,GARBAGE1=0x1337,GARBAGE2=0xbeef)
    functions = dict(viadd=0x30,visub=0x31,viaddi=0x32,viand=0x34,vior=0x35)
    def value(text):
        return constants[text[4:]] if text.startswith('CVI_') else int(text)&0xffff
    cases = []
    for number,line in enumerate(path.read_text().splitlines(),1):
        if not line.startswith('  '):
            continue
        zero = re.fullmatch(r'  (\w+) -> \$0: ([0-9a-f]{4})',line)
        match = re.fullmatch(r'  (\w+) ([^ ,]+), ([^ ,]+): ([0-9a-f]{4}) \(no flag changes\)',line)
        if not zero and not match:
            raise ValueError('unparsed VU integer case: '+line)
        operation = (zero or match)[1]
        if operation not in functions:
            raise ValueError('unknown VU integer operation: '+operation)
        a,b = (0x1234,0x5678) if zero else (value(match[2]),value(match[3]))
        dest = 0 if zero else 1
        word = 0x4a000000 | 2<<11 | functions[operation]
        if operation == 'viaddi':
            word |= dest<<16 | (b&31)<<6
        else:
            word |= 3<<16 | dest<<6
        cases.append(dict(line=number,operation=operation,word=word,a=a,b=b,expected=int((zero or match)[2 if zero else 4],16),flags=not bool(zero)))
    data = ''.join('{word:x} {a:x} {b:x}\n'.format(**case) for case in cases).encode()
    rows = subprocess.run([str(harness),'vu-int'],input=data,capture_output=True,check=True).stdout.splitlines()
    if len(rows) != len(cases):
        raise ValueError('incomplete VU result stream')
    mismatches = []
    for case,row in zip(cases,rows):
        actual,status,mac,clip = [int(x,16) for x in row.split()]
        if actual != case['expected'] or (case['flags'] and (status,mac,clip) != (0x5a3,0xabcd,0x123456)):
            mismatches.append(dict(**case,actual=actual,status=status,mac=mac,clip=clip))
    return dict(cases=len(cases),flag_preservation_cases=sum(case['flags'] for case in cases),
                mismatches=mismatches,input_sha256=hashlib.sha256(path.read_bytes()).hexdigest(),
                scope='Published VU0 integer macro results and preservation of status/MAC/clip registers.',gate_1='not evaluated by this individual check')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs',type=Path,required=True)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/vu-check.json')
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    result = check(args.harness,args.logs)
    result['harness_sha256'] = hashlib.sha256(args.harness.read_bytes()).hexdigest()
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print('Published VU0 integer logs: %d cases, %d mismatches.' % (result['cases'],len(result['mismatches'])))
    print('Individual check only; run gate1.py for the combined functional gate.')
    return bool(result['mismatches'])


if __name__ == '__main__':
    raise SystemExit(main())
