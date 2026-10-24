#!/usr/bin/env python3
"""Run relocated exact and deliberately mutated C++ on twenty real inputs."""
import argparse
import hashlib
import json
from pathlib import Path
import sys

ROOT=Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import equiv
from units import load_units


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/release/eeharness')
    args=parser.parse_args()
    address=0x177b98
    if not any(f['addr']==address and f['status']=='source' for u in load_units() for f in u['functions']):
        raise ValueError('registered exact control is missing')
    captures=ROOT/'build/eeharness/phase2'
    selected=None
    for path in sorted(captures.glob('*.analysis.json')):
        row=json.loads(path.read_text())
        if row.get('counts',{}).get(str(address),0)>=20 and '-world.' in path.name:
            selected=row['run'];break
    if selected is None:raise ValueError('twenty recorded world-update control inputs are required')
    snapshot=captures/selected['snapshot'];corpus=captures/selected['corpus']
    output=ROOT/'build/eeharness/pilot/controls';output.mkdir(parents=True,exist_ok=True)
    empty=output/'empty.txt';empty.touch();results=[]
    for value in (1,2):
        work=output/str(value);work.mkdir(exist_ok=True)
        row=equiv.prepare([dict(address=address,size=8,symbol='pilot_constant',returns='i64',
            source='tests/toolchain/eeharness_pilot_control.cpp',
            flags=['-O2','-G0','-snas','-ffunction-sections','-fno-exceptions','-fno-rtti',f'-DEE_PILOT_VALUE={value}'])],work)[0]
        if row.get('prepare_error'):raise ValueError(row['prepare_error'])
        manifest=work/'manifest.txt'
        manifest.write_text(f'{address:x} {address+8:x} {row["candidate"]:x} i64 "{ROOT/row["elf"]}"\n')
        result=json.loads(equiv.run([args.harness,'differential',snapshot,corpus,manifest,empty,10000]))[0]
        expected_failures=0 if value==1 else result['recorded']
        if result['recorded']<20 or result['failed']!=expected_failures:
            raise ValueError('compiled differential control failed: '+str(result))
        results.append(dict(source_constant=value,candidate_sha256=row['candidate_sha256'],**result))
    with corpus.open('rb') as stream:corpus_hash=hashlib.file_digest(stream,'sha256').hexdigest()
    report=dict(harness_sha256=equiv.digest(args.harness.read_bytes()),snapshot_sha256=equiv.digest(snapshot.read_bytes()),
                corpus_sha256=corpus_hash,source_sha256=equiv.digest((ROOT/'tests/toolchain/eeharness_pilot_control.cpp').read_bytes()),
                results=results,scope='Exact and mutated controls only; no game-function promotion.')
    (output/'controls.json').write_text(json.dumps(report,indent=2)+'\n')
    print(f'OK compiled exact control: {results[0]["recorded"]} agreements; compiled mutation: {results[1]["failed"]} detected.')


if __name__=='__main__':main()
