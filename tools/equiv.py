#!/usr/bin/env python3
"""Differentially execute compiled candidates on every available recorded input.

Candidates use SN 1.36 in the build backend. The matching build is
untouched. Private candidate ELFs, input states and detailed coverage stay in
build/eeharness/pilot/. Agreement is evidence on tested inputs, not proof.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import re
import struct
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools/eeharness'))
from elfinfo import Elf
from elfobj import undefine_dropped
from units import load_units


def digest(data):
    return hashlib.sha256(data).hexdigest()


def claim(plan):
    """Keep matching placement unchanged while assigning candidate ownership."""
    from units_verify import save
    units=load_units();by_address={f['addr']:(u,f) for u in units for f in u['functions']}
    extra=None
    for row in plan:
        if not (ROOT/row['source']).resolve().is_relative_to(ROOT/'src'):
            continue
        if row['address'] in by_address:
            unit,function=by_address[row['address']]
        else:
            if extra is None:
                extra=dict(name='equivalence_pilot',source=row['source'],flags=['-O2','-G0','-snas','-ffunction-sections'],functions=[])
                units.append(extra)
            unit=extra;function=dict(addr=row['address'],symbol=f'func_{row["address"]:08X}',size=row['size'],status='asm',reason='differential-draft')
            unit['functions'].append(function)
        unit['owner']='phase3-pilot';unit['claim']='equivalence-pilot'
        function['nonmatching']=dict(source=row['source'],symbol=row['symbol'],returns=row['returns'])
        if function['status']!='source':function.setdefault('evidence',dict(tier='draft'))
    save(units)


def record_evidence(report):
    from units_verify import save
    units=load_units();by_address={f['addr']:f for u in units for f in u['functions']}
    count=0
    for row in report['functions']:
        if row['status']!='eligible':continue
        function=by_address[row['address']]
        # An existing byte-matched implementation always retains the exact tier.
        if function['status']=='source':continue
        expected=dict(source=row['source'],symbol=row['symbol'],returns=row['returns'])
        if function.get('nonmatching')!=expected:
            raise ValueError('claim the current candidate contract before recording evidence')
        function['evidence']=dict(tier='equivalent',meaning='agreement on tested states; not a proof',
            recorded_states=row['recorded'],fuzzed_states=row['fuzzed'],coverage=row['coverage'],
            coverage_threshold=report['coverage_threshold'],source_sha256=row['source_sha256'],
            candidate_sha256=row['candidate_sha256'],harness_sha256=report['harness_sha256'],
            reference_sha256=report['reference_sha256'],compiler='ee-gcc2.95.3-136',flags=row['flags'],
            input_manifest_sha256=report['input_manifest_sha256'],
            report='build/eeharness/pilot/pilot.json')
        count+=1
    save(units)
    return count


def run(command, **kwargs):
    result = subprocess.run([str(x) for x in command],cwd=ROOT,capture_output=True,text=True,**kwargs)
    if result.returncode:
        raise RuntimeError((result.stdout+result.stderr).strip())
    return result.stdout


def flatten(path, active=()):
    """Standalone compiler wrapper accepts no implicit host include directory."""
    path = Path(path).resolve()
    if path in active:
        raise ValueError('recursive quoted include')
    def include(match):
        name = match[1]
        for base in (path.parent,ROOT/'include'):
            child = base/name
            if child.is_file():
                return flatten(child,(*active,path))
        raise ValueError('missing quoted include '+name)
    return re.sub(r'^\s*#\s*include\s+"([^"\n]+)"[^\n]*',include,path.read_text(),flags=re.M)


def bindings():
    result = {}
    for line in (ROOT/'config/symbols.txt').read_text().splitlines():
        parts = line.split('\t')
        if len(parts)>=4 and parts[0].startswith('0x'):
            result[parts[3]] = int(parts[0],16)
    placement = json.loads((ROOT/'build/SLUS_213.76/placement.json').read_text())
    result.update({f['name']:f['addr'] for f in placement['functions']})
    for unit in load_units():
        result.update(unit['externs'])
        result.update({f['symbol']:f['addr'] for f in unit['functions'] if f.get('symbol')})
    for path in (ROOT/'.local/import').glob('*_bindings.json'):
        for values in json.loads(path.read_text()).values():
            result.update({name:int(value,0) if isinstance(value,str) else value for name,value in values.items()})
    return result


def reference_gp(elf):
    """Keep overlay GPREL relocations relative to the running reference image."""
    section = elf.section('.reginfo')
    if section is None or section['type'] != 0x70000006:
        raise ValueError('reference ELF needs MIPS .reginfo for its original GP')
    data = elf.content(section)
    if len(data) != 24:
        raise ValueError('reference ELF has invalid MIPS .reginfo size')
    gp = struct.unpack_from('<I', data, 20)[0]
    if not gp:
        raise ValueError('reference ELF has no original GP')
    return gp


def overlay_linker_script(symbol, section, undefined, resolved, gp):
    """Bind original data/callees and GP while placing candidate code elsewhere."""
    script = '\n'.join(f'{name} = 0x{resolved[name]:x};' for name in sorted(set(undefined)))
    script += f'\n_gp = 0x{gp:x};\nENTRY({symbol})\nSECTIONS {{\n . = 0x08000000;\n .text : {{ input.o({section}) }}\n'
    return script + ' .rodata : { input.o(.rodata .rodata.* .lit4 .lit4.*) }\n /DISCARD/ : { *(*) }\n}\n'


def prepare(plan, output):
    """Compile each source once, then link only the chosen body plus constants.

    Every other known definition is rebound to the original image. Unknown
    out-of-line helpers or writable candidate storage fail linking/validation.
    """
    names = bindings()
    gp = reference_gp(Elf((ROOT/'orig/SLUS_213.76/SLUS_213.76').read_bytes()))
    compiled, results = {},[]
    for row in plan:
        row = dict(row)
        source = ROOT/row['source']
        text = flatten(source)
        flags = row.get('flags',['-O2','-G0','-snas','-ffunction-sections'])
        key = digest((text+'\0'+' '.join(flags)).encode())
        folder = output/'objects'/key[:20]
        folder.mkdir(parents=True,exist_ok=True)
        flat = folder/('candidate'+source.suffix)
        obj = folder/'candidate.o'
        if key not in compiled:
            flat.write_text(text)
            if not obj.exists():
                try:
                    run([sys.executable,'tools/compile.py','ee-gcc2.95.3-136',*flags,'-c',flat,'-o',obj])
                except RuntimeError as error:
                    # Infrastructure failures are fatal; do not bypass isolation.
                    if any(x in str(error) for x in ('Build backend failed','Connection refused','Connection reset')):
                        raise
                    compiled[key] = str(error)
                else:
                    compiled[key] = None
            else:
                compiled[key] = None
        row['source_sha256']=digest(text.encode())
        row['flags']=flags
        if compiled[key]:
            row['prepare_error']=compiled[key];results.append(row);continue
        elf = Elf(obj.read_bytes())
        symbol = next((s for s in elf.symbols() if s['name']==row['symbol'] and s['shndx'] not in (0,0xfff1)),None)
        if not symbol:
            row['prepare_error']='candidate symbol is not defined';results.append(row);continue
        section = elf.sections[symbol['shndx']]
        if not section['name'].startswith('.text.'):
            row['prepare_error']='candidate needs a per-function text section';results.append(row);continue
        selected = {section['name']} | {s['name'] for s in elf.sections if s['name'].startswith(('.rodata','.lit4'))}
        edited,_ = undefine_dropped(obj.read_bytes(),selected)
        stem = output/f"function-{row['address']:08x}"
        stem.with_suffix('.o').write_bytes(edited)
        # Undefined symbols must have a known original address. Do not guess.
        parsed=Elf(edited);symbols=parsed.symbols();used=set()
        for rel in parsed.sections:
            if rel['type']==9 and parsed.sections[rel['info']]['name'] in selected:
                used.update(info>>8 for _,info in struct.iter_unpack('<II',parsed.content(rel)))
        undefined=[s['name'] for i,s in enumerate(symbols) if i in used and s['name'] and s['shndx']==0 and s['bind']]
        resolved = dict(names,**row.get('externs',{}))
        for name in undefined:
            match = re.fullmatch(r'(?:func_|D_)([0-9A-Fa-f]{8})',name)
            if match:
                resolved[name]=int(match[1],16)
        unknown = sorted(set(undefined)-resolved.keys())
        if unknown:
            row['prepare_error']='unknown original bindings: '+', '.join(unknown)
            results.append(row);continue
        script = overlay_linker_script(row['symbol'], section['name'], undefined, resolved, gp)
        stem.with_suffix('.ld').write_text(script)
        row.update(object=str(stem.with_suffix('.o').relative_to(ROOT)),linker=str(stem.with_suffix('.ld').relative_to(ROOT)),
                   elf=str(stem.with_suffix('.elf').relative_to(ROOT)),candidate=0x08000000+symbol['value'],candidate_size=symbol['size'])
        results.append(row)
    # One offline linking job for the complete batch, through the supported wrapper.
    jobs = [r for r in results if 'prepare_error' not in r]
    script = output/'link_candidates.py'
    script.write_text('import json, subprocess\nresults=[]\n'+
        '\n'.join(f"p=subprocess.run(['mipsel-linux-gnu-ld','-EL','-T','{i}.ld','{i}.o','-o','{i}.elf'],capture_output=True,text=True)\nresults.append(dict(index={i},rc=p.returncode,error=p.stderr))" for i,_ in enumerate(jobs))+
        "\njson.dump(results,open('links.json','w'))\n")
    # Scripts refer to input.o. Keep source object spelling fixed using a private
    # linker script per job, and use the numbered object path in that script.
    args = [sys.executable,'tools/sandbox.py',script,'--out',f'links.json={output/"links.json"}']
    for i,row in enumerate(jobs):
        ld = ROOT/row['linker'];ld.write_text(ld.read_text().replace('input.o',f'{i}.o'))
        args += ['--file',f'{i}.ld={ld}','--file',f'{i}.o={ROOT/row["object"]}','--out',f'{i}.elf={ROOT/row["elf"]}']
    if jobs:
        run(args)
        links=json.loads((output/'links.json').read_text())
        for row,link in zip(jobs,links):
            if link['rc']:
                row['prepare_error']=link['error']
            else:
                row['candidate_sha256']=digest((ROOT/row['elf']).read_bytes())
    return results


def coverage(words, address, pcs, edges):
    """Static direct CFG; unresolved indirect jumps make qualification fail.

    Calls return to PC+8. Branch delay words belong to their predecessor block;
    branch-likely annulment is reflected in the observed instruction coverage.
    Only CFG-reachable words form the denominator; alignment is excluded.
    """
    end=address+4*len(words)
    leaders={address}; successors={}; conditional=[]; unresolved=[]
    for i,w in enumerate(words):
        pc=address+4*i;op=w>>26;rs=w>>21&31;rt=w>>16&31;fn=w&63
        target=pc+4+struct.unpack('<h',struct.pack('<H',w&65535))[0]*4
        branch=op in (4,5,6,7,20,21,22,23) or (op==1 and rt in (0,1,2,3,16,17,18,19)) or (op in (16,17,18) and rs==8)
        if branch:
            # BAL is a call, not an intra-function edge to another function.
            if op==1 and rt in (16,17,18,19):
                successors[pc]=[pc+8]
            elif op==4 and rs==rt:
                successors[pc]=[target]
            else:
                successors[pc]=[target,pc+8];conditional.append((pc,target,pc+8,op in (20,21,22,23) or (op==1 and rt in (2,3)) or (op in (16,17,18) and rt&2)))
        elif op in (2,3):
            successors[pc]=[pc+8] if op==3 else [((pc+4)&0xf0000000)|((w&0x3ffffff)<<2)]
        elif op==0 and fn in (8,9):
            successors[pc]=[pc+8] if fn==9 else []
            if fn==8 and rs!=31:
                unresolved.append(pc)
        if pc in successors:
            leaders.update(x for x in successors[pc] if address<=x<end)
    reached=set();todo=[address]
    while todo:
        pc=todo.pop()
        if pc in reached or pc<address or pc>=end:continue
        reached.add(pc)
        if pc in successors:
            if pc+4<end:reached.add(pc+4)
            todo.extend(successors[pc])
        else:todo.append(pc+4)
    leaders &= reached
    observed=set(pcs)&reached;observed_edges=set(map(tuple,edges))
    branch_outcomes=0
    for pc,target,fall,likely in conditional:
        if pc not in reached:continue
        branch_outcomes+=int((pc+4,target) in observed_edges)
        branch_outcomes+=int((pc,fall) in observed_edges if likely else (pc+4,fall) in observed_edges)
    total_outcomes=2*sum(pc in reached for pc,*_ in conditional)
    return dict(basic_blocks=len(leaders),covered_basic_blocks=len(leaders&observed),
                block_fraction=len(leaders&observed)/len(leaders) if leaders else 0,
                instructions=len(reached),covered_instructions=len(observed),
                instruction_fraction=len(observed)/len(reached) if reached else 0,
                branch_outcomes=total_outcomes,covered_branch_outcomes=branch_outcomes,
                unresolved_indirect_jumps=[hex(pc) for pc in unresolved if pc in reached])


def execute(rows,args):
    gate=json.loads((args.captures/'gate-2.json').read_text())
    usable=[r for r in rows if 'prepare_error' not in r]
    manifest=args.output/'manifest.txt'
    manifest.write_text(''.join(f'{r["address"]:x} {r["address"]+r["size"]:x} {r["candidate"]:x} {r["returns"]} "{ROOT/r["elf"]}"\n' for r in usable))
    harness_hash=digest(args.harness.read_bytes());manifest_hash=digest(manifest.read_bytes())
    aggregates={r['address']:dict(recorded=0,fuzzed=0,passed=0,failed=0,pcs=set(),edges=set(),failures=[]) for r in rows}
    def process(item):
        corpus=args.captures/item['corpus'];snapshot=args.captures/item['snapshot']
        patch=corpus.with_suffix('.fuzz.txt')
        if not patch.exists():
            patch=args.output/'empty-patches.txt';patch.touch()
        with corpus.open('rb') as stream:
            corpus_hash=hashlib.file_digest(stream,'sha256').hexdigest()
        signature=dict(harness=harness_hash,manifest=manifest_hash,snapshot=digest(snapshot.read_bytes()),corpus_sha256=corpus_hash,
                       corpus_size=corpus.stat().st_size,corpus_mtime=corpus.stat().st_mtime_ns,
                       patches=digest(patch.read_bytes()),budget=args.budget)
        cache=args.output/(corpus.stem+'.differential.json')
        if cache.exists() and json.loads(cache.read_text()).get('signature')==signature:
            return corpus.name,json.loads(cache.read_text())['results']
        text=run([args.harness,'differential',snapshot,corpus,manifest,patch,args.budget])
        results=json.loads(text)
        cache.write_text(json.dumps(dict(signature=signature,results=results),indent=2)+'\n')
        return corpus.name,results
    jobs=[run for state in gate['inputs'] for run in state['runs'] if run.get('corpus')]
    if usable:
        with ThreadPoolExecutor(max_workers=args.jobs) as pool:
            for future in as_completed([pool.submit(process,item) for item in jobs]):
                name,results=future.result()
                for result in results:
                    agg=aggregates[result['address']]
                    for key in ('recorded','fuzzed','passed','failed'):agg[key]+=result[key]
                    agg['pcs'].update(result['pcs']);agg['edges'].update(map(tuple,result['edges']))
                    if result['failed']:agg['failures'].append(dict(corpus=name,index=result['first_failure_index'],error=result['first_error']))
                print(f'{name}: {sum(r["recorded"] for r in results)} recorded, {sum(r["fuzzed"] for r in results)} fuzzed, {sum(r["failed"] for r in results)} disagreements/incomplete',flush=True)
    elf=Elf((ROOT/'orig/SLUS_213.76/SLUS_213.76').read_bytes());section=elf.section('.text');data=elf.content(section)
    report=[]
    for row in rows:
        agg=aggregates[row['address']]
        expected=next(f['recorded_states'] for f in gate['functions'] if f['address']==row['address'])
        if not row.get('prepare_error') and agg['recorded']!=expected:
            raise ValueError('tested recorded-state count differs from the complete captured corpus')
        words=struct.unpack_from('<%dI'%(row['size']//4),data,row['address']-section['addr'])
        cov=coverage(words,row['address'],agg.pop('pcs'),agg.pop('edges'))
        qualified=(not row.get('prepare_error') and agg['recorded']>=20 and not agg['failed'] and cov['block_fraction']>=args.coverage and not cov['unresolved_indirect_jumps'])
        # Raw generated drafts are useful diagnostics, but a reviewed readable
        # source and reviewed return ABI are required before evidence promotion.
        status='eligible' if qualified and row.get('readable_reviewed') and row.get('abi_reviewed') and (ROOT/row['source']).resolve().is_relative_to(ROOT/'src') and Path(row['source']).suffix in ('.cpp','.cc','.cxx') and not row.get('existing_exact') else 'draft'
        report.append(dict(**row,**agg,coverage=cov,status=status,execution_and_coverage_pass=qualified))
    receipts=[]
    for item in jobs:
        path=args.output/(Path(item['corpus']).stem+'.differential.json')
        if usable:
            receipts.append(dict(corpus=item['corpus'],signature=json.loads(path.read_text())['signature']))
    eligible=[r for r in report if r['status']=='eligible']
    final=dict(scope='Function pilot only; no full-program ELF or Gate 3 frame claim.',
               agreement_meaning='Identical observable behavior on the tested recorded/fuzzed states, with measured original coverage; not a proof.',
               harness_sha256=harness_hash,reference_sha256=digest(elf.data),coverage_threshold=args.coverage,
               input_manifest_sha256=digest(json.dumps(receipts,sort_keys=True).encode()),input_receipts=receipts,
               selected=len(rows),large_game_functions=sum(r['size']>1024 for r in rows),
               eligible=len(eligible),eligible_large_game_functions=sum(r['size']>1024 for r in eligible),
               function_pilot_status='passed' if len(eligible)>=50 and sum(r['size']>1024 for r in eligible)>=10 else 'not_passed',functions=report,
               limits=['Candidate image uses immutable interpreter-only mappings; deployable ELF layout is separate.',
                       'All call argument banks and auxiliary FPU/VU outputs are compared conservatively.',
                       'Only actually allocated stack bytes below entry SP are excluded; caller stack remains observed.',
                       'Generated drafts and unreviewed return ABIs cannot receive equivalent status.',
                       'Interrupts and device behavior retain the existing recorded stub profile.'])
    (args.output/'pilot.json').write_text(json.dumps(final,indent=2)+'\n')
    return final


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('plan',type=Path,help='JSON list of source/address/size/symbol/returns candidate contracts')
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/pilot')
    parser.add_argument('--captures',type=Path,default=ROOT/'build/eeharness/phase2')
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/release/eeharness')
    parser.add_argument('--coverage',type=float,default=.9)
    parser.add_argument('--budget',type=int,default=1000000)
    parser.add_argument('--jobs',type=int,default=2)
    parser.add_argument('--prepare-only',action='store_true')
    parser.add_argument('--claim-only',action='store_true')
    parser.add_argument('--record-evidence',action='store_true',help='write qualifying evidence through the units serializer')
    args=parser.parse_args()
    args.output=args.output.resolve()
    if not args.output.is_relative_to(ROOT/'build') or args.coverage<.9 or args.coverage>1 or args.budget<1 or args.jobs<1:
        parser.error('use ignored build output, positive budgets/jobs and coverage >= 0.9')
    args.output.mkdir(parents=True,exist_ok=True)
    plan=json.loads(args.plan.read_text())
    inventory={f['address']:f for f in json.loads((args.captures/'gate-2.json').read_text())['functions']}
    seen=set()
    for row in plan:
        original=inventory.get(row['address'])
        if not original or row['address'] in seen or row['size']!=original['size'] or row['size']%4:
            parser.error('candidate spans must match unique original function boundaries')
        if not (ROOT/row['source']).resolve().is_relative_to(ROOT):
            parser.error('candidate sources must stay in the repository')
        if row['returns'] not in ('void','i32','i64','i128','f32'):
            parser.error('an explicit supported return ABI is required')
        seen.add(row['address'])
    if args.claim_only:
        claim(plan);return
    rows=prepare(plan,args.output)
    (args.output/'prepared.json').write_text(json.dumps(rows,indent=2)+'\n')
    print(f'Prepared {sum("prepare_error" not in r for r in rows)}/{len(rows)} candidates.',flush=True)
    if not args.prepare_only:
        final=execute(rows,args)
        if args.record_evidence:print(f'Recorded evidence for {record_evidence(final)} functions.')
        print(f'Pilot: {final["eligible"]}/{final["selected"]} eligible; {final["large_game_functions"]} selected over 1 KB.')


if __name__=='__main__':
    main()
