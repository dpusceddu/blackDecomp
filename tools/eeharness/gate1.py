#!/usr/bin/env python3
"""Run and summarize the functional EE-harness gate against private fixtures.

This gate checks instruction behavior, decode coverage and the source controls.
It does not certify cycle accuracy, hardware replay or game-function equivalence.
It requires existing harness executables; native compilation belongs in the
build backend and is never an implicit validation step.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf
from compiled_check import SUITES


def require(condition,message):
    if not condition:
        raise ValueError(message)


def run(command,allowed=(0,)):
    result = subprocess.run([str(x) for x in command],cwd=ROOT,capture_output=True,text=True)
    require(result.returncode in allowed,'command failed: '+' '.join(str(x) for x in command)+'\n'+result.stdout+result.stderr)
    return result.stdout.strip()


def read_report(name,harness_hash):
    report = json.loads((ROOT/'build/eeharness'/name).read_text())
    require(report['harness_sha256'] == harness_hash,'stale executable binding in '+name)
    return report


def compiled_results(report,logs):
    # These exact words exercise sequences the manuals leave undefined/reserved.
    # They are required to stop, and never counted as output agreements.
    stops = {
        'ee-branchdelay':(0x1002ac,0x11080004,0x11080006,'control transfer in a delay slot'),
        'ee_fpu-branchdelay':(0x1002ac,0x45010004,0x45010006,'control transfer in a delay slot'),
        'vu0_macro-transfer':(0x10046c,0x4a0002ff,0x48c8b800,'VU control command is not implemented'),
    }
    require({row['suite'] for row in report['suites']} == set(SUITES),'compiled fixture set is incomplete')
    agreements,diagnostic_stops,instructions = [],[],0
    for row in report['suites']:
        name = row['suite']
        if name not in stops:
            require(row['agreement'],name+' output did not agree')
            match = re.fullmatch(r'fixture returned after (\d+) instructions; (\d+) distinct PCs',row['diagnostics'])
            require(match is not None,name+' did not report a complete interpreted return')
            instructions += int(match[1]); agreements.append(name)
            continue
        pc,previous,word,error = stops[name]
        require(not row['agreement'] and row['returncode'] == 1 and row['diagnostics'] == f'fixture at {pc}: {error}',
                name+' did not stop at the reviewed undefined/reserved operation')
        elf = Elf((logs/(name+'.elf')).read_bytes()); text = elf.section('.text')
        actual = struct.unpack_from('<II',elf.content(text),pc-text['addr']-4)
        require(actual == (previous,word),name+' reviewed stop has different instruction words')
        output = (ROOT/'build/eeharness'/(name+'.actual')).read_bytes()
        require((logs/(name+'.expected')).read_bytes().startswith(output),name+' diverged before its reviewed stop')
        diagnostic_stops.append(dict(suite=name,pc=hex(pc),word=hex(word),reason=error))
    return dict(complete_programs=len(agreements),instructions=instructions,diagnostic_stops=diagnostic_stops)


def check(args):
    for binary in (args.harness, *(args.harness.parent/name for name in
                                  ('ee_semantics','vu_semantics','cop0_semantics'))):
        require(binary.is_file(), 'existing harness executable required: '+str(binary)+
                '; compile only through the build backend')
    run(['ctest','--test-dir',args.harness.parent,'--output-on-failure'])
    assertions = {}
    for name,minimum in [('ee_semantics',1000),('vu_semantics',385),('cop0_semantics',121)]:
        output = run([args.harness.parent/name])
        match = re.match(r'OK (\d+) ',output)
        require(match is not None and int(match[1]) >= minimum,name+' is missing required assertions')
        assertions[name] = int(match[1])
    # Source controls compile only in the build backend. Stop here on any
    # failure; do not dispatch other checks after a worker connection failure.
    run([sys.executable,ROOT/'tools/eeharness/selfcheck.py','--harness',args.harness])
    scripts = [
        ('audit.py',[]),('integer_check.py',['--logs',args.logs]),
        ('fpu_check.py',['--logs',args.logs]),('vu_check.py',['--logs',args.logs]),
        ('micro_check.py',['--logs',args.logs]),('micro_check.py',['--logs',args.logs,'--via-ee']),
        ('compiled_check.py',['--logs',args.logs,'--budget','100000000']),
        ('retail_micro_check.py',[]),
    ]
    def dispatch(item):
        name,options = item
        return name,run([sys.executable,ROOT/'tools/eeharness'/name,'--harness',args.harness,*options],
                        (0,1) if name == 'compiled_check.py' else (0,))
    with ThreadPoolExecutor(max_workers=3) as pool:
        for name,output in pool.map(dispatch,scripts):
            print(name+': '+output.splitlines()[0],flush=True)
    fingerprint = hashlib.sha256(args.harness.read_bytes()).hexdigest()
    controls = read_report('selfcheck.json',fingerprint)
    require(controls['exact_control_executions'] >= 1408 and len(controls['floating_controls']) >= 12,
            'exact integer/float source controls are incomplete')
    require(controls['source_mutation'] == [dict(source_constant=1,result='agreement'),
                                          dict(source_constant=2,result='mutation detected')],
            'compiled source mutation control did not pass')
    audit = read_report('decode-audit.json',fingerprint)
    require(audit['words'] == 678866 and audit['execution_supported_words'] == audit['words'] and
            not audit['decoder_mismatch_count'] and not audit['unsupported_opcodes'],'retail EE decode/support audit failed')
    require(audit['rabbitizer_invalid_count'] == 4 and all(row['word'] == '0xff00ff' for row in audit['rabbitizer_invalid']),
            'retail invalid-word inventory changed and needs review')
    require(sum(row['pairs'] for row in audit['vu_uploads']) == 842 and
            all(not row['decoder_mismatches'] and not row['unsupported'] for row in audit['vu_uploads']),
            'retail VU0 decoder audit failed')
    numerical = {}
    for name,key,minimum in [('integer-check.json','cases',3728),('vu-check.json','cases',106),
                             ('micro-check.json','register_observations',1103),('micro-ee-check.json','register_observations',1103)]:
        row = read_report(name,fingerprint)
        require(row[key] >= minimum and not row['mismatches'],'instruction fixture failure in '+name)
        numerical[name] = row[key]
    fp = read_report('fpu-check.json',fingerprint)['published_logs']
    require(fp['cases'] >= 908 and fp['status_cases'] >= 7 and not fp['mismatches'],'COP1 numerical/status fixtures failed')
    numerical['fpu-check.json'] = fp['cases']
    compiled = compiled_results(read_report('compiled-check.json',fingerprint),args.logs)
    require(compiled['complete_programs'] == 20,'complete compiled fixture inventory changed')
    retail = read_report('retail-micro-check.json',fingerprint)['cases']
    require(len(retail) == 42 and all(row['repeat_agreement'] and row['stop'] == 'returned' for row in retail),
            'synthetic retail micro execution/replay check failed')
    matching = []
    for slug,boot in [('SLUS_213.76','SLUS_213.76'),('SLES_540.30','SLES_540.30'),('SLES_538.86','SLES_538.86'),
                      ('SLKA_253.72','SLKA_253.72'),('SLPM_663.54','SLPM_663.54')]:
        run([sys.executable,ROOT/'tools/check_elf.py',slug,ROOT/'build'/slug/(boot+'.elf')])
        matching.append(slug)
    source = {str(path.relative_to(ROOT)):hashlib.sha256(path.read_bytes()).hexdigest()
              for path in sorted((ROOT/'tools/eeharness').iterdir())
              if path.is_file() and (path.suffix in ('.cpp','.hpp','.py') or path.name == 'CMakeLists.txt')}
    control = ROOT/'tests/toolchain/eeharness_control.c'
    source[str(control.relative_to(ROOT))] = hashlib.sha256(control.read_bytes()).hexdigest()
    return dict(gate=1,status='passed',scope='Functional instruction semantics, decoder audit and source differential controls.',
                harness_sha256=fingerprint,source_sha256=source,semantic_assertions=assertions,
                instruction_observations=numerical,exact_source_executions=controls['exact_control_executions'],
                compiled=compiled,synthetic_retail_micro_runs=len(retail),matching_variants=matching,
                limits=['No console cycle-accuracy claim: EE uses a deterministic issue clock with VU hazards/interlocks.',
                        'Hardware, DMA, syscall, IOP and VU1 endpoints are recorded stubs.',
                        'Reserved/undefined behavior and execution faults do not qualify as successful equivalence tests.',
                        'No real-state coverage or game-function equivalence is established by Gate 1.'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs',type=Path,required=True)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/gate-1.json')
    args = parser.parse_args()
    require(args.output.resolve().is_relative_to((ROOT/'build').resolve()),'reports must stay under ignored build/')
    try:
        report = check(args)
    except (ValueError,OSError,KeyError) as error:
        report = dict(gate=1,status='failed',error=str(error))
    args.output.parent.mkdir(parents=True,exist_ok=True)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print('Gate 1: '+report['status'].upper())
    if report['status'] != 'passed':
        print(report['error'],file=sys.stderr)
        return 1
    print('Functional gate only; limits and evidence are recorded in '+str(args.output.resolve().relative_to(ROOT)))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
