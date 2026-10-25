#!/usr/bin/env python3
"""Check unique producers, direct generated-input dependencies and recovery of every generated file.

Usage: check_graph.py [--graph build/SLUS_213.76/graph.json] [--on-disk]
The structural/deletion check needs no SDK. Every build command additionally checks its actual Python file reads and
writes against the same edge contract. Ninja manages depfiles and its own state; installed SDK files are external inputs.
"""
import argparse
from collections import defaultdict
import json
from pathlib import Path
import sys
import subprocess
sys.path.insert(0,str(Path(__file__).resolve().parent))
from graph_io import generated


def validate(edges, root=Path('.'), on_disk=False):
    owners=defaultdict(list)
    problems=[]
    for e in edges:
        for path in e['outputs']:owners[path].append(e['name'])
    for path,names in owners.items():
        if len(names)!=1:problems.append('%s: multiple producers %s'%(path,', '.join(names)))
    for e in edges:
        inputs=set(e['inputs']+e.get('implicit',[]))
        for path in inputs:
            if generated(path) and path not in owners:
                problems.append('%s: generated input has no producer: %s'%(e['name'],path))
        contracts=[x for x in inputs if '/io/' in x and x.endswith('.json')]
        for contract in contracts:
            p=root/contract
            if not p.exists():
                if on_disk:problems.append('missing contract: '+contract)
                continue
            c=json.loads(p.read_text())
            for path in c['reads']:
                if generated(path) and path not in inputs and path not in e['outputs']:
                    problems.append('%s: undeclared generated read: %s'%(e['name'],path))
            if set(c['writes'])!=set(e['outputs']):
                problems.append('%s: contract outputs differ from Ninja outputs'%e['name'])
    # Missing any output must dirty its producer. This uses the same multi-output
    # edge semantics as Ninja; no generated path may be a source-only leaf.
    generated_outputs=[p for p in owners if generated(p)]
    for path in generated_outputs:
        if len(owners[path])!=1:continue
        if on_disk and not (root/path).is_file():problems.append('missing output: '+path)
    by_output={p:i for i,e in enumerate(edges) for p in e['outputs']}
    active,done=set(),set()
    def visit(path):
        index=by_output.get(path)
        if index is None or index in done:return
        if index in active:
            problems.append('dependency cycle at '+path);return
        active.add(index)
        e=edges[index]
        for p in e['inputs']+e.get('implicit',[]):visit(p)
        active.remove(index);done.add(index)
    for path in by_output:visit(path)
    return sorted(set(problems)),len(generated_outputs)


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--graph',type=Path,default=Path('build/SLUS_213.76/graph.json'))
    p.add_argument('--on-disk',action='store_true')
    p.add_argument('--ninja',action='store_true',help='also verify every producer against Ninja itself')
    a=p.parse_args()
    edges=json.loads(a.graph.read_text())
    problems,count=validate(edges,on_disk=a.on_disk)
    if a.ninja:
        result=subprocess.run(['ninja','-t','targets','all'],check=True,capture_output=True,text=True)
        actual={line.rsplit(': ',1)[0] for line in result.stdout.splitlines()}
        problems += ['not a declared Ninja output: '+path for e in edges for path in e['outputs'] if path not in actual]
    if problems:
        print('\n'.join(problems[:40]),file=sys.stderr)
        if len(problems)>40:print('... %d more'% (len(problems)-40),file=sys.stderr)
        return 1
    print('graph OK: %d generated files have unique producers and declared generated-input dependencies'%count)
    return 0


if __name__=='__main__':sys.exit(main())
