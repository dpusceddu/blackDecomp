#!/usr/bin/env python3
"""Interpret compiled ps2autotests fixtures and compare their complete output.

Private ELF inputs stay outside the source tree. The only runtime replacement
is their standard stdout/stderr write endpoint; printf and tested code execute
inside the EE interpreter. This adapter is not a game-equivalence driver.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import difflib
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from elfinfo import Elf

SUITES = ['ee-alu','ee-muldiv','ee-branch','ee-branchdelay','ee-lsu','ee-lsudelay',
          'ee_simd-arithmetic','ee_simd-compare','ee_simd-funnel','ee_simd-logic','ee_simd-muldiv','ee_simd-shuffle']
SUITES += ['ee_fpu-'+name for name in ['arithmetic','branch','branchdelay','compare','convert','fcr','muldiv','sqrt','transfer']]
SUITES += ['vu0_macro-integer','vu0_macro-transfer']


def bindings(elf):
    text = elf.section('.text')
    words = list(struct.unpack('<%dI'%(text['size']//4),elf.content(text)))
    def index(address):
        result = (address-text['addr'])//4
        if address&3 or not 0 <= result < len(words):
            raise ValueError('fixture binding outside executable text')
        return result
    def target(i):
        return ((text['addr']+i*4+4)&0xf0000000) | (words[i]&0x3ffffff)<<2
    entry = struct.unpack_from('<I',elf.data,24)[0]
    # The pinned fixture CRT enables interrupts, calls initialization and main,
    # then jumps to its exit routine. Reject other startup shapes explicitly.
    window = range(index(entry),min(index(entry)+128,len(words)))
    enables = [i for i in window if words[i] == 0x42000038]
    if len(enables) != 1:
        raise ValueError('unrecognized fixture CRT interrupt-enable marker')
    calls = []
    for i in range(enables[0]+1,min(enables[0]+24,len(words))):
        if words[i]>>26 == 3:
            calls.append(target(i))
        if words[i]>>26 == 2:
            break
    if not calls:
        raise ValueError('fixture CRT has no main call')
    main = calls[-1]
    def first_call(address,limit):
        known = {0:0}
        for i in range(index(address),min(index(address)+limit,len(words))):
            word = words[i]; op,rs,rt = word>>26,word>>21&31,word>>16&31
            immediate = struct.unpack('<h',struct.pack('<H',word&0xffff))[0]
            if op == 3:
                return i,target(i)
            if op == 0 and word&63 == 9:
                if rs not in known:
                    raise ValueError('unresolved indirect fixture output call')
                return i,known[rs]
            if op == 0 and word&63 == 8:
                break
            if op == 15:
                known[rt] = (word&0xffff)<<16
            elif op in (9,13) and rs in known:
                known[rt] = ((known[rs]+immediate) if op == 9 else known[rs]|(word&0xffff))&0xffffffff
            elif op == 0x23 and rs in known:
                ptr = (known[rs]+immediate)&0xffffffff
                sections = [s for s in elf.sections if s['type'] == 1 and s['addr'] <= ptr and ptr+4 <= s['addr']+s['size']]
                if len(sections) != 1:
                    raise ValueError('fixture output pointer has no initialized ELF data')
                known[rt] = struct.unpack_from('<I',elf.content(sections[0]),ptr-sections[0]['addr'])[0]
        raise ValueError('fixture output helper has no resolved call')
    first,puts = first_call(main,24)
    fmt = None
    for word in words[index(main):first+2]:
        if word>>26 == 15 and word>>16&31 == 4:
            fmt = (word&0xffff)<<16
        if word>>26 == 9 and word>>21&31 == 4 and word>>16&31 == 4 and fmt is not None:
            fmt = (fmt+struct.unpack('<h',struct.pack('<H',word&0xffff))[0])&0xffffffff
    rodata = elf.section('.rodata'); offset = -1 if fmt is None else fmt-rodata['addr']
    marker = elf.content(rodata).find(b'-- TEST BEGIN')
    if fmt is None or not 0 <= offset < rodata['size'] or elf.content(rodata)[offset:].split(b'\0',1)[0].rstrip(b'\n') != b'-- TEST BEGIN':
        # Newer fixture CRTs call a thread wrapper. Resolve the test routine
        # from its unique initial marker, retaining its complete prologue.
        if marker < 0:
            raise ValueError('fixture main/output binding failed its test-marker check')
        marker_address = rodata['addr']+marker
        refs = []
        for i,word in enumerate(words):
            if word>>26 == 9 and word>>21&31 == 4 and word>>16&31 == 4 and word&0xffff == marker_address&0xffff:
                for prior in range(i-1,max(-1,i-13),-1):
                    if words[prior]>>26 == 15 and words[prior]>>16&31 == 4:
                        high = (words[prior]&0xffff)<<16
                        low = struct.unpack('<h',struct.pack('<H',word&0xffff))[0]
                        if (high+low)&0xffffffff == marker_address:
                            refs.append((prior,i))
                            break
        if len(refs) != 1:
            raise ValueError('fixture initial test marker is not uniquely bound')
        high,low = refs[0]
        frames = [i for i in range(max(0,low-32),low) if words[i]>>26 == 9 and words[i]>>21&31 == 29 and words[i]>>16&31 == 29 and words[i]&0x8000]
        if not frames:
            raise ValueError('fixture test marker has no complete function prologue')
        main = text['addr']+min(high,frames[-1])*4
        first,puts = first_call(main,32)
    _,putchar = first_call(puts,64)
    call,write = first_call(putchar,24)
    around = words[index(putchar):call+2]
    if 0x24040001 not in around or 0x24060001 not in around:
        raise ValueError('fixture output endpoint does not have fd=1 and length=1 bindings')
    index(write)
    gp = struct.unpack_from('<I',elf.content(elf.section('.reginfo')),20)[0]
    return dict(main=main,write=write,gp=gp)


def check(suite,args):
    binary,expected = args.logs/(suite+'.elf'),args.logs/(suite+'.expected')
    result = dict(suite=suite,elf_sha256=hashlib.sha256(binary.read_bytes()).hexdigest(),
                  expected_sha256=hashlib.sha256(expected.read_bytes()).hexdigest())
    try:
        addresses = bindings(Elf(binary.read_bytes()))
        result['bindings'] = {key:hex(value) for key,value in addresses.items()}
        run = subprocess.run([str(args.harness),'fixture',str(binary),*[hex(addresses[key]) for key in ['main','write','gp']],str(args.budget)],
                             capture_output=True,timeout=120)
        wanted = expected.read_bytes()
        output = args.output.parent/(suite+'.actual')
        output.write_bytes(run.stdout)
        result.update(returncode=run.returncode,agreement=run.returncode == 0 and run.stdout == wanted,
                      diagnostics=run.stderr.decode(errors='replace').strip(),output_bytes=len(run.stdout),
                      output_sha256=hashlib.sha256(run.stdout).hexdigest())
        if not result['agreement']:
            result['diff_preview'] = list(difflib.unified_diff(wanted.decode().splitlines(),run.stdout.decode(errors='replace').splitlines(),n=1))[:30]
    except (ValueError,subprocess.TimeoutExpired) as error:
        result.update(agreement=False,error=str(error))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--logs',type=Path,required=True)
    parser.add_argument('--suite',action='append',choices=SUITES)
    parser.add_argument('--jobs',type=int,default=3)
    parser.add_argument('--budget',type=int,default=20000000)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/compiled-check.json')
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to((ROOT/'build').resolve()):
        parser.error('reports must stay under ignored build/')
    if args.jobs < 1 or args.budget < 1:
        parser.error('jobs and execution budget must be positive')
    args.output.parent.mkdir(parents=True,exist_ok=True)
    results = []
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(check,suite,args) for suite in args.suite or SUITES]
        for future in as_completed(futures):
            result = future.result(); results.append(result)
            print(result['suite'], 'agreement' if result['agreement'] else 'REQUIRES REVIEW',result.get('diagnostics',result.get('error','')),flush=True)
    report = dict(suites=sorted(results,key=lambda row:row['suite']),gate_1='not evaluated by this individual check',
                  harness_sha256=hashlib.sha256(args.harness.read_bytes()).hexdigest(),
                  scope='Complete compiled instruction-fixture output with a recorded stdout/stderr adapter; no game evidence or function promotion.')
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    return any(not result['agreement'] for result in results)


if __name__ == '__main__':
    raise SystemExit(main())
