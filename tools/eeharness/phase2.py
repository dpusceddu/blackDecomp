#!/usr/bin/env python3
"""Capture real Black function inputs and measure Gate 2 without promoting source.

Private RAM, registers and entry corpora stay under ignored build/. The gate
counts original input entries, never fuzz mutations or repeated copies of a file.
"""
import argparse
import collections
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import inspect
import json
from pathlib import Path
import struct
import subprocess
import sys
import time
import zipfile

import corpus
import savestate

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools'))
from elfinfo import Elf
from progress import regions

# Ghidra: 0x264018 calls 0x102bd0 with *(0x40f0e0) in its main loop.
# The active state's virtual update is 0x105518. These root calls are explicitly
# bootstrapped from recovered call contracts, not captured at the original PC.
FRAME_ENTRY = 0x102bd0
ROOT_POINTER = 0x40f0e0
# Receiver globals and calls recovered together in 0x102bd0. Service labels
# avoid assigning an unproved class identity to the latter two managers.
FRAME_SERVICES = [('ui',0x20b2b0,0x40f544),
                  ('service-1d5b78',0x1d5b78,0x40f510),
                  ('service-10b018',0x10b018,0x40f4f0)]


def capture_catalog(fuzz_limit, path):
    """Natural-input-only capture needs no generated class or field catalog."""
    return None if fuzz_limit == 0 else json.loads(path.read_text())


def capture_fuzz(fuzz_limit, prefix, snapshot, catalog):
    """Keep the patch file empty when typed mutations were explicitly disabled."""
    if fuzz_limit:
        return corpus.make_fuzz(prefix.with_suffix('.eec'),snapshot.regions['eeMemory.bin'],catalog,
                                prefix.with_suffix('.fuzz'),fuzz_limit)
    prefix.with_suffix('.fuzz.txt').write_text('')
    prefix.with_suffix('.fuzz.json').write_text(json.dumps(dict(
        cases=[],observed_receivers={},scope='disabled; natural recorded inputs only'),indent=2)+'\n')
    return []


def main_thread_stack(snapshot):
    """Recover the boot thread's saved stack when captured on another thread.

    TCB/context offsets follow ps2tek's EE Threading layout. Require the game's
    actual entry, GP, bounded allocation and self-consistent saved SP. Root calls
    use space below the suspended context, leaving that context intact.
    """
    ram = snapshot.regions['eeMemory.bin']
    cpu = snapshot.registers['cpu']
    gp, saved_sp = cpu['gpr'][28][0],cpu['gpr'][29][0]
    word = lambda address:struct.unpack_from('<I',ram,address)[0]
    found, start = [],0
    while True:
        where = ram.find(struct.pack('<I',gp),start,0x100000)
        if where<0:
            break
        start = where+4
        if where<20 or where&3:
            continue
        tcb = where-20
        if word(tcb+48)!=0x100008 or word(tcb+8) not in (1,2,4,8,12,16):
            continue
        context, base, size = word(tcb+16),word(tcb+60),word(tcb+64)
        if not (0x100000<=base<=context and context+640<=base+size<=len(ram)):
            continue
        if context&15 or word(context+448)!=gp or word(context+464)!=context+640:
            continue
        found.append((tcb,context,base,size))
    if len(found)!=1:
        if saved_sp<0x100000:
            raise ValueError('cannot uniquely recover the game main-thread stack')
        return None
    tcb,context,base,size = found[0]
    if base<=saved_sp<=base+size:
        return None
    return dict(tcb=tcb,context=context,stack=context,allocated_base=base,allocated_size=size,
                captured_stack=saved_sp,basis='saved boot-thread TCB and 640-byte EE context')


def state_update_root(ram, root, known):
    """The dispatcher's live state virtual call: vptr +8, adjust +16, fn +20."""
    if not (0x100000<=root and root+0x21074<=len(ram)):
        return None
    receiver = struct.unpack_from('<I',ram,root+0x21070)[0]
    if not (0x100000<=receiver<=len(ram)-12):
        return None
    table = struct.unpack_from('<I',ram,receiver+8)[0]
    if not (0<table<=len(ram)-24):
        return None
    adjustment = struct.unpack_from('<h',ram,table+16)[0]
    entry = struct.unpack_from('<I',ram,table+20)[0]
    if entry not in known or not (0x100000<=receiver+adjustment<len(ram)):
        return None
    return entry,receiver+adjustment


def capture_run(args, functions, snapshot, catalog, prefix, entry, receiver, stack):
    bridge = prefix.with_suffix('.ees');expected = snapshot.replay_image()
    contract = dict(entry=entry,receiver=receiver,stack=stack['stack'] if stack else None,
                    entries='calls-and-cross-function-entries-v2')
    receipt_path = prefix.with_suffix('.capture.json')
    reusable = all(prefix.with_suffix(s).exists() for s in ('.ees','.eec','.run.json'))
    receipt = json.loads(receipt_path.read_text()) if receipt_path.exists() else None
    if receipt is not None:
        compatible = (receipt.get('execution_signature')==args.execution_signature or
                      ('execution_signature' not in receipt and receipt.get('harness_sha256')==args.harness_sha256))
        reusable = reusable and receipt['contract']==contract and compatible
    else:
        reusable = False
    analysis_path = prefix.with_suffix('.analysis.json')
    if reusable:
        if bridge.read_bytes()!=expected:
            raise ValueError('existing capture baseline differs from the supplied savestate')
        result = json.loads(prefix.with_suffix('.run.json').read_text())
        prior_budget = receipt['budget'] if receipt else 6000000
        if result['iterations_completed']<args.frames and (result['stop']==0 or args.budget>prior_budget):
            reusable = False
    if not reusable:
        bridge.write_bytes(expected)
        command = [args.harness,'replay',bridge,functions,args.budget,hex(entry),hex(receiver),
                   args.frames,prefix.with_suffix('.eec')]
        if stack:
            command.append(hex(stack['stack']))
        result = run_json(command,prefix.with_suffix('.run.json'))
        receipt_path.write_text(json.dumps(dict(contract=contract,harness_sha256=args.harness_sha256,
                                               execution_signature=args.execution_signature,
                                               frames=args.frames,budget=args.budget),indent=2)+'\n')
    stat = prefix.with_suffix('.eec').stat()
    signature = dict(analysis=args.analysis_signature,corpus_size=stat.st_size,corpus_mtime_ns=stat.st_mtime_ns)
    if reusable and analysis_path.exists() and not args.reuse_captures:
        cached = json.loads(analysis_path.read_text())
        if cached['signature'] == signature:
            return cached['run'],collections.Counter({int(a):n for a,n in cached['counts'].items()})
    observed = {int(a):n for a,n in result['entries'].items()}
    captured = collections.Counter()
    sample_ids = []
    for record in corpus.entries(prefix.with_suffix('.eec')):
        if record['function']:
            captured[record['function']] += 1
            if record['index'] in (0,100,1000):
                sample_ids.append(record['index'])
    if sum(captured.values()) != result['stored'] or any(n!=min(observed.get(a,0),20) for a,n in captured.items()):
        raise ValueError('persisted entry counts differ from observed execution')
    replay_checks = [run_json([args.harness,'replay-entry',bridge,prefix.with_suffix('.eec'),i,200000],
                             prefix.with_suffix(f'.replay-{i}.json')) for i in sample_ids]
    fuzz = capture_fuzz(args.fuzz_limit,prefix,snapshot,catalog)
    fuzz_results = run_json([args.harness,'replay-fuzz',bridge,prefix.with_suffix('.eec'),
                            prefix.with_suffix('.fuzz.txt'),100000],prefix.with_suffix('.fuzz-results.json')) if fuzz else []
    run = dict(entry=hex(entry),receiver=hex(receiver),execution=result,bootstrap_stack=stack,
                corpus=prefix.with_suffix('.eec').name,snapshot=bridge.name,
                ordered_events=prefix.with_suffix('.eec').name+'.events.gz' if prefix.with_suffix('.eec.events.gz').exists() else None,
                entry_states=sum(captured.values()),functions_reached=len(captured),
                replay_checks=replay_checks,fuzz_cases=len(fuzz),
                fuzz_returns=sum(r['stop']==0 for r in fuzz_results),
                fuzz_faults=sum(r['stop']==2 for r in fuzz_results),fuzz_budget_stops=sum(r['stop']==1 for r in fuzz_results))
    analysis_path.write_text(json.dumps(dict(signature=signature,run=run,counts=captured),indent=2)+'\n')
    return run,captured


def run_json(command, output):
    with output.open('w') as stream:
        subprocess.run([str(x) for x in command],stdout=stream,check=True,cwd=ROOT)
    return json.loads(output.read_text())


def inventory():
    functions = json.loads((ROOT/'build/usa-retail/placement.json').read_text())['functions']
    labels,_ = regions([f['addr'] for f in functions])
    return [dict(address=f['addr'],size=(functions[i+1]['addr'] if i+1<len(functions) else 0x396f48)-f['addr'],region=label)
            for i,(f,label) in enumerate(zip(functions,labels))]


def summarize(fs, inputs, totals, pending):
    game = [f for f in fs if f['region']=='game']
    reached = [f for f in game if totals[f['address']]]
    ready = [f for f in game if totals[f['address']]>=20]
    passed = len(ready)*2>len(game) and not pending
    return dict(gate=2,status='passed' if passed else 'not_passed',
                measured_scope='Observed original-code inputs under the recorded EE hardware-stub profile; no source equivalence claim.',
                pending_inputs=pending,game_functions=len(game),game_functions_reached=len(reached),
                game_functions_with_20_states=len(ready),required_functions=len(game)//2+1,
                game_bytes=sum(f['size'] for f in game),reached_game_bytes=sum(f['size'] for f in reached),
                qualified_game_bytes=sum(f['size'] for f in ready),all_text_bytes=sum(f['size'] for f in fs),
                reached_text_bytes=sum(f['size'] for f in fs if totals[f['address']]),
                inputs=sorted(inputs,key=lambda r:r['input']),functions=[dict(f,recorded_states=totals[f['address']]) for f in fs],
                limits=['Root dispatcher/world calls use the recovered main-loop receiver contracts.',
                        'Hardware uses captured reads, local scratchpad DMA and recorded output completion/vblank stubs.',
                        'The issue clock is not cycle accurate. No IOP, GS, VU1 or general kernel scheduler is executed.',
                        'Vtable scans identify candidates; freed objects may retain pointers.',
                        'Fuzz mutations do not contribute to Gate 2 recorded-state counts.'])


def adopt_legacy(output):
    """Move the first run's numbered files once; never replace existing files."""
    report = output/'gate-2.json'
    if not report.exists():
        return
    for number,row in enumerate(json.loads(report.read_text()).get('inputs',[])):
        if row.get('artifact_prefix') or not row.get('sha256'):
            continue
        old = f'state-{number:02d}'
        new = 'input-'+row['sha256'][:16]
        for path in output.glob(old+'*'):
            if path.is_file() and path.name[len(old):].startswith(('-','.')):
                target = output/(new+path.name[len(old):])
                if not target.exists():
                    path.rename(target)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('states',nargs='*',type=Path)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/phase2')
    parser.add_argument('--harness',type=Path,default=ROOT/'build/eeharness/host/eeharness')
    parser.add_argument('--frames',type=int,default=40)
    parser.add_argument('--budget',type=int,default=6000000)
    parser.add_argument('--fuzz-limit',type=int,default=256,
                        help='maximum typed mutations; zero captures natural inputs without a class catalog')
    parser.add_argument('--reuse-captures',action='store_true',
                        help='reanalyze existing captures; new savestates are still captured')
    parser.add_argument('--jobs',type=int,default=2,help='independent input states processed concurrently')
    args = parser.parse_args()
    output = args.output.resolve()
    if not output.is_relative_to((ROOT/'build').resolve()):
        parser.error('private replay output must stay under ignored build/')
    if args.frames<1 or args.budget<1 or args.fuzz_limit<0 or args.jobs<1:
        parser.error('budgets must be positive; fuzz-limit may be zero')
    output.mkdir(parents=True,exist_ok=True)
    adopt_legacy(output)
    args.harness_sha256 = hashlib.sha256(args.harness.read_bytes()).hexdigest()
    args.analysis_signature = hashlib.sha256(inspect.getsource(capture_run).encode()+
        inspect.getsource(capture_fuzz).encode()+
        Path(corpus.__file__).read_bytes()+args.harness_sha256.encode()+str(args.fuzz_limit).encode()).hexdigest()
    sources = ('ee.hpp','decode.cpp','cpu.cpp','cop0.cpp','memory.cpp','fpu.cpp','fpu.hpp','vu.cpp','vu.hpp',
               'replay.cpp','replay.hpp','event_journal.cpp','event_journal.hpp','main.cpp')
    args.execution_signature = hashlib.sha256(b''.join(
        name.encode()+Path(__file__).with_name(name).read_bytes() for name in sources)).hexdigest()
    states = args.states or sorted((ROOT/'orig/savestates').glob('*.p2s'))
    if not states:
        parser.error('no real savestates')
    fs = inventory()
    functions = output/'functions.txt'
    functions.write_text(''.join(f"{f['address']:x}\n" for f in fs))
    catalog = capture_catalog(args.fuzz_limit,ROOT/'build/classes/catalog.json')
    elf = Elf((ROOT/'orig/usa-retail/files/SLUS_213.76').read_bytes())
    text = elf.section('.text'); retail = elf.content(text)
    totals, inputs, digests = collections.Counter(),[],set()
    unique = []
    for path in states:
        with path.open('rb') as stream:
            digest = hashlib.file_digest(stream,'sha256').hexdigest()
        if digest not in digests:
            unique.append(path);digests.add(digest)

    def process(path):
        started = time.monotonic()
        snapshot = savestate.load(path)
        if snapshot.registers['elf_name'].split('\\')[-1] != 'SLUS_213.76;1':
            raise ValueError('Phase 2 currently requires USA retail Black')
        ram = snapshot.regions['eeMemory.bin']
        changed = [text['addr']+i for i in range(0,len(retail),4)
                   if ram[text['addr']+i:text['addr']+i+4] != retail[i:i+4]]
        # Unknown modifications to game code invalidate this target's inputs.
        game_ranges = [(f['address'],f['address']+f['size']) for f in fs if f['region']=='game']
        if any(lo<=a<hi for a in changed for lo,hi in game_ranges):
            raise ValueError('savestate has modified game-region instructions')
        prefix = output/('input-'+snapshot.sha256[:16])
        objects = corpus.object_candidates(ram,catalog) if catalog is not None else []
        prefix.with_suffix('.objects.json').write_text(json.dumps(objects,indent=2)+'\n')
        root = struct.unpack_from('<I',ram,ROOT_POINTER)[0]
        stack = main_thread_stack(snapshot)
        runs, counts = [],collections.Counter()
        # The world update at 0x129360 is called at 0x102df0 with *(0x40f4d0).
        # Isolating it avoids renderer waits while preserving original callees.
        plans = [('frame',FRAME_ENTRY,root),('world',0x129360,struct.unpack_from('<I',ram,0x40f4d0)[0])]
        state_root = state_update_root(ram,root,{f['address'] for f in fs})
        if state_root is not None:
            plans.append(('state',*state_root))
        for name,entry,pointer in FRAME_SERVICES:
            receiver = struct.unpack_from('<I',ram,pointer)[0]
            if 0x100000<=receiver<len(ram):
                plans.append((name,entry,receiver))
        for name,entry,receiver in plans:
            run,captured = capture_run(args,functions,snapshot,catalog,Path(str(prefix)+'-'+name),entry,receiver,stack)
            counts.update(captured);runs.append(run)
            stop = ('returned','instruction budget','fault')[run['execution']['stop']]
            print(f"{path.name} {name}: {run['functions_reached']} functions, {run['entry_states']} inputs, "
                  f"{run['execution']['iterations_completed']} completed iterations; "
                  f"{run['execution']['error'] or stop}",flush=True)
        row = dict(input=path.name,sha256=snapshot.sha256,emulator=snapshot.emulator_version,
                   runtime_modified_words=[hex(a) for a in changed],root=hex(root),runs=runs,
                   object_vtable_types=len(objects),object_candidates=sum(len(r['pointer_locations']) for r in objects),
                   fuzz_cases=sum(r['fuzz_cases'] for r in runs),artifact_prefix=prefix.name,
                   elapsed_seconds=round(time.monotonic()-started,3))
        return row,counts

    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        futures = {executor.submit(process,path):path for path in unique}
        for future in as_completed(futures):
            path = futures[future]
            try:
                row,counts = future.result();totals.update(counts)
            except (ValueError,OSError,KeyError,zipfile.BadZipFile,subprocess.SubprocessError) as error:
                row = dict(input=path.name,error=str(error),runs=[])
                print(f'{path.name}: rejected: {error}',flush=True)
            inputs.append(row)
            report = summarize(fs,inputs,totals,len(unique)-len(inputs))
            report['fuzzing_scope'] = ('disabled; natural recorded inputs only; class scan skipped'
                                       if args.fuzz_limit == 0 else 'typed mutations from the generated class catalog')
            temporary = output/'gate-2.pending.json'
            temporary.write_text(json.dumps(report,indent=2)+'\n');temporary.replace(output/'gate-2.json')
            print(f"Gate 2 checkpoint: {report['game_functions_with_20_states']}/{report['required_functions']} required game functions; "
                  f"{report['pending_inputs']} inputs pending.",flush=True)
    print(f"Gate 2 {report['status']}: {report['game_functions_with_20_states']}/{report['game_functions']} game functions have >=20 recorded states; need {report['required_functions']}.")
    return 0 if report['status']=='passed' else 2


if __name__ == '__main__':
    raise SystemExit(main())
