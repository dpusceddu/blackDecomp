#!/usr/bin/env python3
"""Replay authored VU0 instruction fixtures against published hardware logs.

Instruction encodings follow the Sony manual. Fixtures reproduce the tested
operations, without compiling or linking another emulator or SDK program.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
NOP_UPPER, NOP_LOWER = 0x2ff, 0x8000033c


def upper(function, dest=0, fs=0, ft=0, mask=15):
    return mask<<21 | ft<<16 | fs<<11 | dest<<6 | function


def lower_extended(function, fs=0, ft=0, mask=0):
    return 0x80000000 | mask<<21 | ft<<16 | fs<<11 | function


class Program:
    def __init__(self):
        self.lines = ['case']
        self.pairs = []
        self.expected = []

    def vf(self, reg, words):
        self.lines.append('vf %x %s' % (reg,' '.join('%x'%v for v in words)))

    def vi(self, reg, value):
        self.lines.append('vi %x %x' % (reg,value))

    def data(self, address, value):
        self.lines.append('data %x %x' % (address,value))

    def pair(self, hi=NOP_UPPER, lo=NOP_LOWER):
        self.pairs.append((lo,hi))

    def observe(self, bank, reg, expected, label, basis='published value'):
        self.expected.append(dict(bank=bank,reg=reg,expected=expected,label=label,basis=basis))

    def stream(self,via_ee=False):
        for pc,(lo,hi) in enumerate(self.pairs+[(NOP_LOWER,NOP_UPPER|0x40000000),(NOP_LOWER,NOP_UPPER)]):
            self.lines.append('pair %x %x %x' % (pc*8,lo,hi))
        self.lines.append(('run-ee' if via_ee else 'run')+' 0 10000')
        for row in self.expected:
            self.lines.append('print%s %x' % (row['bank'],row['reg']))
        return '\n'.join(self.lines)+'\n'


def log_vectors(path):
    groups, title = {}, None
    for line in path.read_text().splitlines():
        if line and not line.startswith(' ') and line.endswith(':'):
            title = line[:-1]; groups[title] = []
        match = re.match(r'  VF\d+: (.*)',line)
        if match:
            words = re.findall(r'\b([0-9a-f]{8})/',match[1])
            if len(words) != 4:
                raise ValueError('unparsed VU vector result: '+line)
            groups[title].append([int(word,16) for word in words])
    return groups


def divider_program(operation, variant):
    p = Program()
    p.vi(22,0x3f800000)
    p.vf(16,[0,0,0,0x40800000]); p.vf(17,[0,0,0,0x41800000])
    def divide(reg):
        function = {'DIV':0x3bc,'SQRT':0x3bd,'RSQRT':0x3be}[operation]
        return lower_extended(function,0,reg,(0 if operation == 'SQRT' else 3) | 3<<2)
    def mulq(reg):
        return upper(0x1c,reg,0,0)
    wait = lower_extended(0x3bf)
    if variant == 'single waitq':
        p.pair(mulq(1),divide(16)); p.pair(mulq(2),wait); p.pair(mulq(3))
    elif variant == 'multiple waitq':
        p.pair(mulq(1),divide(16)); p.pair(mulq(2),wait); p.pair(mulq(3))
        p.pair(mulq(4),divide(17)); p.pair(mulq(5),wait); p.pair(mulq(6))
    elif variant == 'single delayed':
        p.pair(lo=divide(16))
        for reg in range(1,15):
            p.pair(mulq(reg))
    elif variant in ('multiple delayed (1)','multiple delayed (2)'):
        p.pair(lo=divide(16))
        if variant.endswith('(2)'):
            p.pair(mulq(1))
        p.pair(lo=divide(17))
        for reg in range(2 if variant.endswith('(2)') else 1,15):
            p.pair(mulq(reg))
    else:
        p.pair(lo=divide(16))
        madd = upper(0x29,30,23,0)
        if variant == 'stalled with branch':
            # The fixture's branch is false (VI0 < 0), with its mandatory slot.
            p.pair(madd,0x58000000 | 0x7fe); p.pair()
        else:
            p.pair(madd)
            delay = int(re.search(r'\((\d+)\)',variant)[1])
            for _ in range(delay):
                p.pair(mulq(0))
        p.pair(upper(0x1ff,0,30,30))
        for reg in range(1,15):
            p.pair(mulq(reg))
    return p


def divider_cases(directory):
    groups = log_vectors(directory/'vu-lower-fdivdelay.expected')
    for title,vectors in groups.items():
        operation, variant = title.split(' ',1)
        p = divider_program(operation,variant)
        for reg,vector in enumerate(vectors,1):
            p.observe('vf',reg,vector,title+' VF%d'%reg)
        yield p


def clip_cases(directory):
    text = (directory/'vu-upper-clip.expected').read_text()
    constants = dict(FULL_POS=[0x40000000]*4,FULL_NEG=[0xc0000000]*4,
                     HALF_POS=[0x40000000,0xc0000000,0x40000000,0xc0000000],
                     HALF_NEG=[0xc0000000,0x40000000,0xc0000000,0x40000000],
                     ZERO=[0]*4,NEGZERO=[0x80000000]*4,NEGONE=[0xbf800000]*4,
                     MIN=[0xffffffff]*4,MAX=[0x7fffffff]*4)
    inputs = [('FULL_POS','NEGONE'),('FULL_NEG','NEGONE'),('HALF_POS','NEGONE'),('HALF_NEG','NEGONE'),
              ('HALF_NEG','ZERO'),('HALF_NEG','NEGZERO'),('ZERO','NEGZERO'),('NEGZERO','ZERO'),
              ('FULL_POS','FULL_POS'),('HALF_NEG','HALF_NEG'),('MIN','ZERO'),('MAX','ZERO'),('ZERO','MIN'),('ZERO','MAX')]
    results = re.findall(r'Basic test: (.*?) -> ([0-9a-f]{4})',text)
    if len(results) != len(inputs):
        raise ValueError('unexpected published CLIP basic case count')
    for (a,b),(label,expected) in zip(inputs,results):
        p = Program(); p.vf(1,constants[a]); p.vf(2,constants[b])
        p.pair(upper(0x1ff,0,1,2))
        for _ in range(3):
            p.pair()
        p.pair(lo=0x38010000)
        p.observe('vi',1,[int(expected,16)],'CLIP '+label)
        yield p
    p = Program()
    for reg,name in enumerate(['FULL_POS','FULL_NEG','HALF_POS','HALF_NEG'],1):
        p.vf(reg,constants[name])
        p.pair(upper(0x1ff,0,reg,0),0x38000000|reg<<16)
    for reg in range(5,11):
        p.pair(lo=0x38000000|reg<<16)
    expected = re.search(r'Multi test:\n(.*?)Multi test 2:',text,re.S)[1]
    values = [int(value,16) for value in expected.split()]
    for reg,value in enumerate(values,1):
        p.observe('vi',reg,[value],'CLIP history VI%d'%reg)
    yield p
    p = Program()
    for reg,name in enumerate(['FULL_POS','FULL_NEG','HALF_POS','HALF_NEG','NEGONE'],1):
        p.vf(reg,constants[name])
    for reg in [1,2,3,4]:
        p.pair(upper(0x1ff,0,reg,0))
        p.pair(upper(0x1ff,0,reg,5),0x38000000 | (reg-2)<<16 if reg >= 3 else NOP_LOWER)
    p.pair(); p.pair(lo=0x38030000); p.pair(); p.pair(lo=0x38040000)
    values = [int(value,16) for value in re.search(r'Multi test 2:\n(.*?)-- TEST END',text,re.S)[1].split()]
    for reg,value in enumerate(values,1):
        p.observe('vi',reg,[value],'CLIP interleaved VI%d'%reg)
    yield p


def triace_case(directory):
    words = re.findall(r'\b([0-9a-f]{8})/',(directory/'vu-games-triace.expected').read_text())
    if len(words) != 12:
        raise ValueError('unexpected Tri-Ace log shape')
    p = Program(); p.vf(1,[0xb063b75b,0x8701ce82,0x46fcc888,0x793cc535])
    immediate = [0x42fecccd,0x42546666,0x43d80d3e,0xc7f079b3,0x43a0da10,0x43a02666,0x43546e14,0x42f23333,0x3dd3dd98]
    p.pair(NOP_UPPER|0x80000000,immediate[0])
    for lane in range(4):
        p.pair(upper(0x1e,2,1,0,8>>lane)|0x80000000,immediate[lane*2+1])
        p.pair(upper(0x22,3,2,0,8>>lane)|0x80000000,immediate[lane*2+2])
    for reg in range(1,4):
        # The published VU log prints x/y/z/w.
        p.observe('vf',reg,[int(w,16) for w in words[(reg-1)*4:reg*4]],'Tri-Ace VF%d'%reg)
    return p


def branch_cases(directory):
    text = (directory/'vu-lower-branch.expected').read_text()
    rows = re.findall(r'  (.*?) -> targetReg: ([0-9a-f]+) returnReg: ([0-9a-f]+) resultReg: ([0-9a-f]+)',text)
    for alias,(name,target,link,result) in enumerate(rows):
        p = Program()
        def iaddi(dest,imm):
            return 0x80000032 | dest<<16 | (imm&31)<<6
        p.pair(lo=iaddi(3,0)); p.pair(lo=iaddi(1,6))
        p.pair(lo=0x4a000000 | (1 if alias else 2)<<16 | 1<<11); p.pair()
        p.pair(lo=0x40000002); p.pair(); p.pair(lo=iaddi(3,1)); p.pair()
        for reg,value in [(1,target),(1 if alias else 2,link),(3,result)]:
            p.observe('vi',reg,[int(value,16)],name+' VI%d'%reg)
        yield p


def integer_cases(directory):
    rows = re.findall(r'^  (\w+) (.+?): ([0-9a-f]{4})(.*)$',
                      (directory/'vu-lower-integer.expected').read_text(),re.M)
    if len(rows) != 151:
        raise ValueError('unexpected published VU integer case count')
    constants = dict(CVI_ZERO=0,CVI_ONE=1,CVI_NEGONE=0xffffffff,CVI_S16_MAX=0x7fff,
                     CVI_S16_MIN=0xffff8000,CVI_S32_MAX=0x7fffffff,CVI_S32_MIN=0x80000000,
                     CVI_S64_MAX=0xffffffff,CVI_S64_MIN=0,CVI_GARBAGE1=0x1337,CVI_GARBAGE2=0xdeadbeef)

    def immediate(op,dest,source,value):
        # The 15-bit immediate has its upper four bits in the dest field.
        return op<<25 | ((value>>11)&15)<<21 | dest<<16 | source<<11 | (value&0x7ff)

    def prepare(p,reg,label):
        if label in constants:
            p.data(reg*16,constants[label])
            p.pair(lo=0x09000000 | reg<<16 | reg)  # ILW.x VIreg,reg(VI0)
        else:
            value = int(label)
            # Reproduce the published fixture's actual construction, including
            # its negative-operand quirk. Labels are not raw register contents.
            if value == 0x8000:
                p.pair(lo=lower_extended(0x32 | 31<<6,0,reg))
                p.pair(lo=immediate(9,reg,reg,0x7fff))
            else:
                p.pair(lo=immediate(9 if value&0x8000 else 8,reg,0,value&0x7fff))

    def operation(name,dest,source=2,target=3):
        if name == 'iaddi':
            return lower_extended(0x32 | (target&31)<<6,source,dest)
        if name in ('iaddiu','isubiu'):
            return immediate(8 if name == 'iaddiu' else 9,dest,source,target)
        return lower_extended({'iadd':0x30,'isub':0x31,'iand':0x34,'ior':0x35}[name] | dest<<6,source,target)

    for name,operands,result,flags in rows:
        p = Program()
        p.vi(1,0x1337)
        # The published cases report preservation, rather than fixed flag values.
        preserved = {16:0xa95,17:0x8421,18:0x123456}
        for reg,value in preserved.items():
            p.vi(reg,value)
        if operands == '-> $0':
            prepare(p,2,'57005')
            prepare(p,3,'29489')
            p.pair(lo=operation(name,0,target=7 if name == 'iaddi' else 0x7331 if name.endswith('iu') else 3))
            p.pair(lo=lower_extended(0x35 | 1<<6))  # IOR VI1,VI0,VI0
        else:
            a,b = operands.split(', ')
            prepare(p,2,a)
            if name in ('iaddi','iaddiu','isubiu'):
                p.pair(lo=operation(name,1,target=int(b)))
            else:
                prepare(p,3,b)
                p.pair(lo=operation(name,1))
        p.observe('vi',1,[int(result,16)],name+' '+operands)
        if flags == ' (no flag changes)':
            for reg,value in preserved.items():
                p.observe('vi',reg,[value],name+' preserves VI%d'%reg,'published preservation with authored flags')
        elif flags:
            raise ValueError('unparsed published integer flags: '+flags)
        yield p


def random_cases(directory):
    text = (directory/'vu-lower-random.expected').read_text()
    sections = re.split(r'^(RINIT|RXOR|RNEXT):\s*$',text,flags=re.M)
    constants = dict(CVF_ZEROONE=[0x3f800000,0x3fffffff,0,0xffffffff],
                     CVF_GARBAGE=[0x01234567,0x89abcdef,0xfedcba98,0x76543210])
    for title,body in zip(sections[1::2],sections[2::2]):
        if title in ('RINIT','RXOR'):
            p = Program(); p.vf(16,constants['CVF_GARBAGE'])
            if title == 'RXOR':
                p.pair(lo=lower_extended(0x43e))
            for lane in range(4):
                p.pair(lo=lower_extended(0x43e if title == 'RINIT' else 0x43f,16,mask=lane))
                p.pair(lo=lower_extended(0x43d,ft=lane+1,mask=15))
            rows = re.findall(r'^  ((?:[0-9a-f]{8}/[^\s]+\s*){4})$',body,re.M)
            if len(rows) != 4:
                raise ValueError('unexpected published random-register row count')
            for reg,row in enumerate(rows,1):
                p.observe('vf',reg,[int(w,16) for w in re.findall(r'([0-9a-f]{8})/',row)],title+' VF%d'%reg)
            yield p
        else:
            groups = re.findall(r'  (CVF_\w+)\[VU::FIELD_([XYZW])\]:\s*\n((?:    [1-4]:[^\n]+\n){4})',body)
            if len(groups) != 8:
                raise ValueError('unexpected published RNEXT case count')
            for name,component,rows in groups:
                p = Program(); p.vf(16,constants[name])
                p.pair(lo=lower_extended(0x43e,16,mask='XYZW'.index(component)))
                for reg,row in enumerate(rows.splitlines(),1):
                    p.pair(lo=lower_extended(0x43c,ft=reg,mask=15))
                    p.observe('vf',reg,[int(w,16) for w in re.findall(r'([0-9a-f]{8})/',row)],'RNEXT '+name+'.'+component+' VF%d'%reg)
                yield p


def multiplier_cases(directory):
    path = directory/'vu-fobes-mul.expected'
    if not path.exists():
        return
    rows = re.findall(r'([xyzw])->[^\n(]*\(([0-9a-fA-F]{8})\) to [^\n(]*\(([0-9a-fA-F]{8})\)',path.read_text())
    if not rows:
        raise ValueError('no published VU multiplier cases found')
    for component,before,after in rows:
        p = Program(); lane = 'xyzw'.index(component)
        p.vf(1,[0x3f800000]*4); p.vf(2,[int(before,16)]*4)
        p.pair(upper(0x2a,3,1,2,8>>lane))
        expected = [0]*4; expected[lane] = int(after,16)
        p.observe('vf',3,expected,'published VU MUL 1 * '+before+' .'+component)
        yield p


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs',type=Path,required=True)
    parser.add_argument('--via-ee',action='store_true',help='launch and synchronize every fixture through EE instructions')
    parser.add_argument('--output',type=Path)
    args = parser.parse_args()
    if args.output is None:
        args.output = ROOT/('build/eeharness/micro-ee-check.json' if args.via_ee else 'build/eeharness/micro-check.json')
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    programs = [*divider_cases(args.logs),*clip_cases(args.logs),triace_case(args.logs),*branch_cases(args.logs),
                *integer_cases(args.logs),*random_cases(args.logs),*multiplier_cases(args.logs)]
    data = ''.join(p.stream(args.via_ee) for p in programs).encode()
    result = subprocess.run([str(args.harness),'vu'],input=data,capture_output=True)
    if result.returncode:
        raise SystemExit(result.stderr.decode())
    cases = [case for p in programs for case in p.expected]
    rows = result.stdout.splitlines()
    if len(rows) != len(cases):
        raise ValueError('incomplete micro result stream')
    mismatches = []
    for case,row in zip(cases,rows):
        actual = [int(value,16) for value in row.split()]
        if actual != case['expected']:
            mismatches.append(dict(**case,actual=actual))
    files = ['vu-lower-fdivdelay.expected','vu-upper-clip.expected','vu-games-triace.expected','vu-lower-branch.expected',
             'vu-lower-integer.expected','vu-lower-random.expected']
    if (args.logs/'vu-fobes-mul.expected').exists():
        files.append('vu-fobes-mul.expected')
    report = dict(programs=len(programs),register_observations=len(cases),mismatches=mismatches,
                  published_values=sum(c['basis'] == 'published value' for c in cases),
                  authored_flag_preservation=sum(c['basis'] != 'published value' for c in cases),
                  execution_mode='EE VCALLMS and QMFC2.i' if args.via_ee else 'standalone micro engine',
                  harness_sha256=hashlib.sha256(args.harness.read_bytes()).hexdigest(),
                  inputs_sha256={name:hashlib.sha256((args.logs/name).read_bytes()).hexdigest() for name in files},
                  gate_1='not evaluated by this individual check',scope='Published VU FDIV timing, clip history, immediate arithmetic, JALR alias, integer and optional multiplier observations; common RNG semantics replay VU1 observations on VU0. Integer no-change flags use authored initial flags. Not complete flag/timing coverage.')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print('VU0 micro (%s): %d programs, %d register observations, %d mismatches.' %
          (report['execution_mode'],len(programs),len(cases),len(mismatches)))
    for case in mismatches[:12]:
        print(case['label'],case['expected'],case['actual'])
    print('Individual check only; run gate1.py for the combined functional gate.')
    return bool(mismatches)


if __name__ == '__main__':
    raise SystemExit(main())
