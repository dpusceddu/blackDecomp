#!/usr/bin/env python3
"""Worker-compile isolated VU shapes and compare register-renamed retail windows.

This checks complete VF alias relationships inside each arithmetic window, not
physical allocation around its caller. The shared-context verifier separately
scores real source consumers and checks full-image equality. Inputs remain local.
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path[:0] = [str(_Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]  # the core tools
import argparse
import json
import re
import struct
from pathlib import Path

import autodecomp
from elfinfo import Elf

ROOT = Path(__file__).resolve().parents[2]
VF = re.compile(r'\$vf(\d+)')


def instructions(words, address=0):
    import rabbitizer
    out=[]
    for i,w in enumerate(words):
        line=rabbitizer.Instruction(w,address+4*i,rabbitizer.InstrCategory.R5900).disassemble()
        if line.startswith('.word') and '# vsqrt' in line:
            line=line.split('#',1)[1].split('#',1)[0].strip()
        out.append(line)
    return out


def vector_window(lines):
    # Transfers and memory accesses are compiler-generated transport, not part of
    # a macro's arithmetic block. vnop/Q waits are deliberately retained.
    return [re.sub(r'\s+', ' ', line.strip()) for line in lines
            if line.lstrip().startswith('v')]


def renamed(lines):
    names = {}
    def rename(match):
        number = int(match[1])
        if not number:
            return '$vf0'
        return '$v' + str(names.setdefault(number, len(names)+1))
    return [VF.sub(rename,line) for line in lines]


def verify(config):
    source = (ROOT/'tests/toolchain/vu0_math.cpp').read_text()
    flags = ['-x','c++','-O2','-G0','-snas','-ffunction-sections','-mvu0-use-vf0-vf31']
    rc,message,obj = autodecomp.worker_compile([('vu0-math-controls',source,flags)],tag='vu0-math-controls')['vu0-math-controls']
    if rc:
        raise ValueError('isolated controls did not compile: '+message)
    elf = Elf(obj)
    symbols = {s['name']:s for s in elf.symbols() if s['shndx']}
    inventory = autodecomp.load_inventory()
    rows=[]
    for operation in config['operations']:
        symbol = symbols[operation['fixture']]
        data = elf.content(elf.sections[symbol['shndx']])[symbol['value']:symbol['value']+symbol['size']]
        window = vector_window(instructions([v[0] for v in struct.iter_unpack('<I',data)]))
        expected = renamed(window)
        if not expected:
            raise ValueError('fixture has no arithmetic: '+operation['name'])
        examples=[]
        for function in inventory:
            lines=instructions(function['words'],function['addr'])
            # A fixture's block must be contiguous in retail; ordinary scalar
            # instructions are not discarded from candidate retail windows.
            for i in range(len(lines)-len(window)+1):
                candidate=lines[i:i+len(window)]
                if len(vector_window(candidate))==len(window) and renamed(vector_window(candidate))==expected:
                    examples.append(dict(function=hex(function['addr']),address=hex(function['addr']+4*i)))
        if not examples:
            raise ValueError('no retail alias/dataflow match: '+operation['name'])
        controls=operation.get('real_controls',[])
        if operation['status']=='verified' and len(set(controls))<2:
            raise ValueError('verified operation lacks two real consumers: '+operation['name'])
        rows.append(dict(name=operation['name'],status=operation['status'],
                         isolation='register-renamed dataflow equality',arithmetic_instructions=len(window),
                         retail_occurrences=len(examples),examples=examples,real_controls=controls))
    return dict(flags=flags,operations=rows,
                limitations=['Isolation compares VF alias/dataflow under register renaming; physical caller allocation is separate.',
                             'The shared-context verifier checks exact real consumers and full image identity.',
                             'No flag-state or microprogram contract is inferred from these controls.'])


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',default='build/math-study/isolated-controls.json')
    args=parser.parse_args()
    config=json.loads((ROOT/'config/vu0_math.json').read_text())
    try:
        result=verify(config)
    except (ValueError,KeyError) as error:
        raise SystemExit(str(error))
    output=ROOT/args.output
    if not output.resolve().is_relative_to((ROOT/'build').resolve()):
        raise SystemExit('verification output must stay under build/')
    output.parent.mkdir(parents=True,exist_ok=True)
    output.write_text(json.dumps(result,indent=2)+'\n')
    print('OK isolated VU0 shapes: %d; verified operations: %d' %
          (len(result['operations']),sum(o['status']=='verified' for o in result['operations'])))


if __name__=='__main__':
    main()
