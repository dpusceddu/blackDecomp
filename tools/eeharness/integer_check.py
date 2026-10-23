#!/usr/bin/env python3
"""Replay independently encoded integer/MMI operations against private hardware logs.

Reads published constants and expected results, not another interpreter's code.
No SDK executable or assembler is used on the host. Reports remain ignored.
"""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import re
import subprocess

import rabbitizer

ROOT = Path(__file__).resolve().parents[2]
ZERO = [0]*4


def scalar(value,packed=True):
    value &= 0xffffffff
    sign = 0xffffffff if value&0x80000000 else 0
    return [value,sign,value,sign] if packed else [value,sign,0,0]


def constants(path):
    result = {}
    for name,body in re.findall(r'\b(C_\w+)\[4\]\s*=\s*\{([^}]+)\}',path.read_text()):
        values = [int(value.strip(),0) for value in body.split(',') if value.strip()]
        if len(values) != 4:
            raise ValueError('unexpected input constant '+name)
        result[name] = values
    if not result:
        raise ValueError('no input constants found')
    return result


def opcode_words():
    rabbitizer.config.pseudos_enablePseudos = False
    result = {}
    for function in range(64):
        for shift in range(32):
            word = 0x70000000 | shift<<6 | function
            insn = rabbitizer.Instruction(word,0,rabbitizer.InstrCategory.R5900)
            if insn.isValid():
                result.setdefault(insn.getOpcodeName(),word)
    for word in list(range(64))+[op<<26 for op in range(1,64)]:
        insn = rabbitizer.Instruction(word,0,rabbitizer.InstrCategory.R5900)
        if insn.isValid():
            result.setdefault(insn.getOpcodeName(),word)
    result['sll'] = 0
    return result


def basic_cases(directory,values,opcodes):
    immediate = {'psllh','psllw','psrah','psraw','psrlh','psrlw'}
    variable = {'psllvw','psravw','psrlvw'}
    for name in ['arithmetic','compare','logic','shuffle']:
        filename = 'ee_simd-'+name+'.expected'
        for number,line in enumerate((directory/filename).read_text().splitlines(),1):
            if not line.startswith('  '):
                continue
            match = re.fullmatch(r'  (\w+) (.*?): ((?:[0-9a-f]{8} ){3}[0-9a-f]{8})',line)
            if not match:
                raise ValueError('unparsed result '+line)
            operation,operands,expected = match.groups()
            word = opcodes[operation]
            zero = operands == '-> $0'
            args = ['C_GARBAGE1'] if zero else operands.split(', ')
            source = values[args[0]] if args[0].startswith('C_') else scalar(int(args[0],0))
            dest = values['C_GARBAGE1'] if args[0].startswith('C_') else scalar(0x1337)
            second = ZERO
            if operation in immediate:
                word |= 4<<16 | (5 if zero else int(args[1],0))<<6
            elif len(args) == 1:
                word |= 4 << (21 if operation == 'plzcw' else 16)
            else:
                second = values[args[1]] if args[1].startswith('C_') else scalar(int(args[1],0))
                word |= (5<<21 | 4<<16) if operation in variable else (4<<21 | 5<<16)
            if not zero:
                word |= 2<<11
            # A zero-destination fixture explicitly reads the hardwired GPR0.
            yield dict(file=filename,line=number,operation=operation,word=word,observe=0 if zero else 2,
                       a=source,b=second,dest=dest,hi=ZERO,lo=ZERO,shift=0,
                       expected=dict(gpr=list(reversed([int(v,16) for v in expected.split()]))))


def scalar_cases(directory,values,opcodes):
    filename = 'ee-alu.expected'
    fixed = {'sll','srl','sra','dsll','dsll32','dsrl','dsrl32','dsra','dsra32'}
    variable = {'sllv','srlv','srav','dsllv','dsrlv','dsrav'}
    for number,line in enumerate((directory/filename).read_text().splitlines(),1):
        if not line.startswith('  '):
            continue
        operation,operands,output = re.fullmatch(r'  (\w+) (.*?): (.*)',line).groups()
        word = opcodes[operation]
        zero = operands == '-> $0'
        args = ['C_GARBAGE1'] if zero else operands.split(', ')
        def value(arg):
            return values[arg] if arg.startswith('C_') else scalar(int(arg,0),False)
        a,b = value(args[0]),ZERO
        dest = values['C_GARBAGE1'] if args[0].startswith('C_') else scalar(0x1337,False)
        rd = 0 if zero else 2
        if operation == 'lui':
            word |= rd<<16 | (0xdead if zero else int(args[0],0))&0xffff
        elif operation in fixed:
            word |= 4<<16 | rd<<11 | (5 if zero else int(args[1],0))<<6
        elif word>>26: # immediate arithmetic/logical
            word |= 4<<21 | rd<<16 | (0xdead if zero else int(args[1],0))&0xffff
        else:
            b = a if zero else value(args[1])
            word |= ((5<<21 | 4<<16) if operation in variable else (4<<21 | 5<<16)) | rd<<11
        expected = dict(gpr_low64=list(reversed([int(v,16) for v in output.split()]))[:2],
                        preserved_upper=ZERO[:2] if zero else dest[2:])
        # Scalar published fixtures leave the upper destination half in its
        # compiler-assigned prior state. Validate the reported low 64 bits and
        # separately verify preservation of our explicitly supplied upper half.
        yield dict(file=filename,line=number,operation=operation,word=word,observe=rd,
                   a=a,b=b,dest=dest,hi=ZERO,lo=ZERO,shift=0,expected=expected)


def muldiv_cases(directory,values,opcodes,region='ee_simd'):
    packed = region == 'ee_simd'
    filename = region+'-muldiv.expected'
    source = (directory/(region+'-muldiv.cpp')).read_text()
    for name,body in re.findall(r'\b(C_\w+)\[4\]\s*=\s*\{([^}]+)\}',source):
        values[name] = [int(v.strip(),0) for v in body.split(',') if v.strip()]
    initial = {}
    def pair(low,high):
        a,b = int(low,16),int(high,16)
        return [a&0xffffffff,a>>32,b&0xffffffff,b>>32]
    for name,body in re.findall(r'\b(C_HILO\w*)\s*=\s*\{([^}]+)\}',source):
        h,l,h1,l1 = [v.strip() for v in body.split(',')]
        initial[name] = dict(hi=pair(h,h1),lo=pair(l,l1))
    for number,line in enumerate((directory/filename).read_text().splitlines(),1):
        if not line.startswith('  '):
            continue
        operation,operands,output = re.fullmatch(r'  ([\w.]+) (.*?): (.*)',line).groups()
        zero = operands == '-> $0'
        rhl = re.fullmatch(r'(.*?) \((C_HILO\w*)\)',operands)
        expected = {}
        if 'H:' in output:
            general,highlow = output.split('H:')
            h,h1,l,l1 = re.fullmatch(r' ([0-9a-f]+) ([0-9a-f]+) L: ([0-9a-f]+) ([0-9a-f]+)',highlow).groups()
            expected.update(hi=pair(h,h1),lo=pair(l,l1))
        else:
            general = output
        if general.strip():
            expected['gpr'] = list(reversed([int(v,16) for v in general.split()]))
        args = ['C_GARBAGE1'] if zero else (rhl[1] if rhl else operands).split(', ')
        def value(arg):
            return values[arg] if arg.startswith('C_') else scalar(int(arg,0),packed)
        a,b = value(args[0]),value(args[1]) if len(args)>1 else ZERO
        dest = values['C_GARBAGE1'] if args[0].startswith('C_') else scalar(0x1337,packed)
        word = opcodes[operation]
        observe = 0 if zero else 2
        if rhl or (not packed and len(args) == 1 and not zero):
            dest = a
            word |= 2 << (21 if operation.startswith(('pmt','mt')) else 11)
        elif not zero:
            word |= 4<<21 | 5<<16
            if not operation.startswith(('pdiv','div')):
                word |= 2<<11
        if not packed and 'gpr' in expected:
            expected['gpr_low64'] = expected.pop('gpr')[:2]
            expected['preserved_upper'] = ZERO[:2] if zero else dest[2:]
        yield dict(file=filename,line=number,operation=operation,word=word,observe=observe,
                   a=a,b=b,dest=dest,**initial[rhl[2] if rhl else 'C_HILO'],shift=0,expected=expected)


def funnel_cases(directory,values,opcodes):
    filename = 'ee_simd-funnel.expected'
    patterns = constants(directory/'ee_simd-funnel.cpp')
    for number,line in enumerate((directory/filename).read_text().splitlines(),1):
        match = re.fullmatch(r'  (mfsa|qdsrv) (.*?): (.*)',line)
        if not match:
            continue
        operation,operand,output = match.groups()
        expected = list(reversed([int(v,16) for v in output.split()]))
        amount = values[operand][0] if operand.startswith('C_') else int(operand,0)
        base = dict(file=filename,line=number,a=ZERO,b=ZERO,dest=scalar(0x1234abcd),hi=ZERO,lo=ZERO,observe=2)
        if operation == 'mfsa':
            yield dict(**base,operation='mfsa',word=0x28 | 2<<11,shift=amount&15,expected=dict(gpr_low64=expected[:2]))
            base['a'] = scalar(amount)
            yield dict(**base,operation='mtsa',word=0x29 | 4<<21,shift=0,expected=dict(shift=expected[0]))
        else:
            base.update(a=patterns['C_SHIFT_PATTERN1'],b=patterns['C_SHIFT_PATTERN2'])
            yield dict(**base,operation='qfsrv',word=opcodes['qfsrv'] | 4<<21 | 5<<16 | 2<<11,
                       shift=amount&15,expected=dict(gpr=expected))


def run(harness,cases):
    data = []
    for case in cases:
        words = [case['word'],case['observe'],case['shift']]
        for bank in ['a','b','dest','hi','lo']:
            words += case[bank]
        data.append(' '.join('%x'%word for word in words))
    result = subprocess.run([str(harness),'integer'],input=('\n'.join(data)+'\n').encode(),capture_output=True,check=True)
    rows = result.stdout.decode().splitlines()
    if len(rows) != len(cases):
        raise ValueError('incomplete integer result stream')
    mismatches = []
    for case,row in zip(cases,rows):
        if row.startswith('fault '):
            mismatches.append(dict(file=case['file'],line=case['line'],operation=case['operation'],fault=row))
            continue
        words = [int(value,16) for value in row.split()]
        if len(words) != 13:
            raise ValueError('malformed integer result stream')
        actual = dict(gpr=words[:4],hi=words[4:8],lo=words[8:12],shift=words[12])
        actual.update(gpr_low64=words[:2],preserved_upper=words[2:4])
        differences = {name:dict(expected=expected,actual=actual[name]) for name,expected in case['expected'].items() if expected != actual[name]}
        if differences:
            mismatches.append(dict(file=case['file'],line=case['line'],operation=case['operation'],differences=differences))
    return mismatches


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs',type=Path,required=True)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/integer-check.json')
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    values = constants(args.logs/'ee_simd-shared.h')
    opcodes = opcode_words()
    cases = [*basic_cases(args.logs,values,opcodes),*muldiv_cases(args.logs,values,opcodes),
             *scalar_cases(args.logs,values,opcodes),*muldiv_cases(args.logs,values,opcodes,'ee'),
             *funnel_cases(args.logs,values,opcodes)]
    mismatches = run(args.harness,cases)
    files = sorted({case['file'] for case in cases} | {'ee_simd-shared.h','ee_simd-muldiv.cpp','ee-muldiv.cpp','ee_simd-funnel.cpp'})
    report = dict(cases=len(cases),operations=dict(collections.Counter(case['operation'] for case in cases)),mismatches=mismatches,
                  harness_sha256=hashlib.sha256(args.harness.read_bytes()).hexdigest(),
                  inputs_sha256={name:hashlib.sha256((args.logs/name).read_bytes()).hexdigest() for name in files},
                  gate_1='not evaluated by this individual check',scope='Published scalar ALU/multiply/divide and MMI arithmetic, comparison, logic, shuffle and multiply/divide results; scalar observations cover low 64 bits plus explicit upper-half preservation.')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print('Integer/MMI: %d cases, %d operations, %d mismatches.' % (len(cases),len(report['operations']),len(mismatches)))
    for case in mismatches[:12]:
        print(case)
    print('Individual check only; run gate1.py for the combined functional gate.')
    return bool(mismatches)


if __name__ == '__main__':
    raise SystemExit(main())
