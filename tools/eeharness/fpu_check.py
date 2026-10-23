#!/usr/bin/env python3
"""Check complete COP1 instructions against published numerical result logs.

The external logs/oracle are optional private inputs, never linked into the
interpreter. An oracle check establishes model agreement, not hardware proof.
"""
import argparse
import hashlib
import json
from pathlib import Path
import random
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
TOKEN = r'(?:[0-9a-fA-F]{8}/[^ ,()]+|CF_[A-Z0-9_]+)'
FUNCTIONS = dict(add=0, sub=1, mul=2, div=3, sqrt=4, abs=5, mov=6, neg=7,
                 rsqrt=0x16, adda=0x18, suba=0x19, mula=0x1a, madd=0x1c,
                 msub=0x1d, madda=0x1e, msuba=0x1f, max=0x28, min=0x29,
                 eq=0x32, f=0x30, lt=0x34, le=0x36)
ACCUMULATOR = {'adda', 'suba', 'mula', 'madda', 'msuba'}


def hardware_cases(directory):
    constants = dict(re.findall(r'(CF_\w+)\[\d+\]\s*=\s*\{(0x[0-9a-fA-F]+)',
                                (directory / 'fpu-shared.h').read_text()))
    def bits(value):
        return int(constants[value], 16) if value.startswith('CF_') else int(value.split('/')[0], 16)
    for name in ['arithmetic', 'muldiv', 'sqrt', 'compare', 'convert']:
        path = directory / ('fpu-'+name+'.expected')
        for number, line in enumerate(path.read_text().splitlines(), 1):
            if not line.startswith('  '):
                continue
            instruction = line.strip().split()[0]
            if instruction not in FUNCTIONS and instruction not in ('cvt.s.w', 'cvt.w.s'):
                raise ValueError('unknown result-log operation: '+line)
            head = re.escape(instruction)
            unary = re.match(r'  '+head+r' ('+TOKEN+r'): ([0-9a-fA-F]{8})/', line)
            binary = re.match(r'  '+head+r' ('+TOKEN+r'), ('+TOKEN+r'): ([0-9a-fA-F]{8})/', line)
            mac = re.match(r'  '+head+r' \(('+TOKEN+r')\) ('+TOKEN+r'), ('+TOKEN+r'): ([0-9a-fA-F]{8})/', line)
            compare = re.match(r'  '+head+r' ('+TOKEN+r'), ('+TOKEN+r'): (true|false)', line)
            acc = 0
            if unary:
                a, expected = bits(unary[1]), int(unary[2], 16)
                b = a if instruction == 'sqrt' else 0
            elif binary:
                a, b, expected = bits(binary[1]), bits(binary[2]), int(binary[3], 16)
            elif mac:
                acc = bits(mac[1])
                # The original test prepares ACC using ADDA(input,-0).
                if not acc & 0x7f800000:
                    acc &= 0x80000000
                a, b, expected = bits(mac[2]), bits(mac[3]), int(mac[4], 16)
            elif compare:
                a, b, expected = bits(compare[1]), bits(compare[2]), int(compare[3] == 'true')
            else:
                raise ValueError('unparsed result-log case: '+line)
            if instruction == 'cvt.s.w':
                word = 0x468020a0
            elif instruction == 'cvt.w.s':
                word = 0x460020a4
            else:
                word = 0x46000000 | 4 << 11 | 2 << 6 | FUNCTIONS[instruction]
                if instruction == 'sqrt':
                    word = 0x46050084
                elif binary or mac or compare:
                    word |= 5 << 16
                if instruction in ACCUMULATOR or compare:
                    word &= ~(31 << 6)
            yield dict(file=path.name, line=number, instruction=instruction,
                       word=word, a=a, b=b, accumulator=acc, expected=expected,
                       result='condition' if compare else 'accumulator' if instruction in ACCUMULATOR else 'register')
    flag_path = directory/'fpu-fcr.expected'
    flag_text = flag_path.read_text()
    # Inputs from the corresponding published fcr test; expected flags remain
    # external data. These seven situations are narrower than full flag coverage.
    flag_inputs = [
        ('sqrt(-1)', 'sqrt', 0, 0xbf800000),
        ('Divide zero by zero', 'div', 0, 0),
        ('Divide one by zero', 'div', 0x3f800000, 0),
        ('NAN math', 'add', 0x7f800001, 0x7f800001),
        ('Overflow', 'mul', 0x7f7fffff, 0x7f7fffff),
        ('Underflow', 'div', 0x00800000, 0x40400000),
        ('Inexact', 'div', 0x3f800000, 0x4040ffff)
    ]
    for title, operation, a, b in flag_inputs:
        match = re.search(re.escape(title)+r':\n  fcr0: [0-9a-f]+, fcr31: ([0-9a-f]+)',flag_text)
        if not match:
            raise ValueError('missing published flag case: '+title)
        word = 0x46052080 | FUNCTIONS[operation]
        if operation == 'sqrt':
            word = 0x46050084
        yield dict(file=flag_path.name,line=flag_text[:match.start()].count('\n')+1,
                   instruction=operation,word=word,a=a,b=b,accumulator=0,
                   expected=int(match[1],16),result='status')


def check_logs(harness, directory):
    cases = list(hardware_cases(directory))
    data = ''.join('{word:x} {a:x} {b:x} {accumulator:x} 1000001 0\n'.format(**case)
                   for case in cases).encode()
    result = subprocess.run([str(harness), 'cop1'], input=data, capture_output=True, check=True)
    rows = result.stdout.splitlines()
    if len(rows) != len(cases):
        raise ValueError('incomplete COP1 result stream')
    mismatches = []
    for case, row in zip(cases, rows):
        register, acc, status, overflow = map(lambda x: int(x,16), row.split())
        actual = status if case['result'] == 'status' else bool(status & 0x800000) if case['result'] == 'condition' else acc if case['result'] == 'accumulator' else register
        if actual != case['expected']:
            mismatches.append(dict(**case, actual=actual, status=hex(status)))
    files = sorted(directory.glob('fpu-*.expected')) + [directory/'fpu-shared.h']
    return dict(cases=len(cases),status_cases=sum(case['result'] == 'status' for case in cases),
                mismatches=mismatches,
                input_sha256={p.name:hashlib.sha256(p.read_bytes()).hexdigest() for p in files},
                scope='Published ps2autotests numerical results, comparison conditions and seven FCR31 situations; not full flag coverage.')


def check_oracle(harness, oracle, count, seed):
    rng = random.Random(seed)
    edge = [0, 1, 0x7fffff, 0x800000, 0x800001, 0x3f000000, 0x3f7fffff,
            0x3f800000, 0x3f800001, 0x3fffffff, 0x40000000, 0x7f000000,
            0x7f7fffff, 0x7f800000, 0x7f800001, 0x7ffffffe, 0x7fffffff]
    edge += [x ^ 0x80000000 for x in edge]
    reports = []
    for operation in ['add', 'sub', 'mul', 'div', 'sqrt']:
        pairs = [(a,b) for a in edge for b in edge]
        pairs += [(rng.getrandbits(32),rng.getrandbits(32)) for _ in range(count)]
        data = ''.join(f'{operation} {a:x} {b:x}\n' for a,b in pairs).encode()
        ours = subprocess.run([str(harness), 'fp'], input=data, capture_output=True, check=True).stdout.splitlines()
        other = subprocess.run([str(oracle)], input=data, capture_output=True, check=True).stdout.splitlines()
        if len(ours) != len(pairs) or len(other) != len(pairs):
            raise ValueError('incomplete oracle result stream')
        differences = [dict(a=hex(a),b=hex(b),harness=x.decode(),oracle=y.decode())
                       for (a,b),x,y in zip(pairs,ours,other) if int(x,16) != int(y,16)]
        reports.append(dict(operation=operation,cases=len(pairs),mismatches=differences))
    return dict(operations=reports,seed=seed,oracle_sha256=hashlib.sha256(oracle.read_bytes()).hexdigest(),
                scope='Agreement with an independently executed research model, not fresh hardware execution.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness', type=Path, default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs', type=Path)
    parser.add_argument('--oracle', type=Path)
    parser.add_argument('--random-cases', type=int, default=20000)
    parser.add_argument('--seed', type=int, default=0x5900)
    parser.add_argument('--output', type=Path, default=ROOT/'build/eeharness/fpu-check.json')
    args = parser.parse_args()
    if not args.logs and not args.oracle:
        parser.error('provide published logs, an external oracle, or both')
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    if args.random_cases < 0:
        parser.error('random case count must be nonnegative')
    report = dict(gate_1='not evaluated by this individual check',harness_sha256=hashlib.sha256(args.harness.read_bytes()).hexdigest())
    if args.logs:
        report['published_logs'] = check_logs(args.harness,args.logs)
    if args.oracle:
        report['research_oracle'] = check_oracle(args.harness,args.oracle,args.random_cases,args.seed)
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    failed = False
    if args.logs:
        r = report['published_logs']
        print('Published numerical logs: %d cases, %d mismatches.' % (r['cases'],len(r['mismatches'])))
        failed |= bool(r['mismatches'])
    if args.oracle:
        for r in report['research_oracle']['operations']:
            print('Research oracle %s: %d cases, %d mismatches.' % (r['operation'],r['cases'],len(r['mismatches'])))
            failed |= bool(r['mismatches'])
    print('Individual check only; run gate1.py for the combined functional gate.')
    return failed


if __name__ == '__main__':
    raise SystemExit(main())
