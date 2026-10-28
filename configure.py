#!/usr/bin/env python3
"""Generate Ninja rules with one producer for every generated input and per-object build edges."""
import argparse
import json
from pathlib import Path
import shlex
import subprocess
import sys
sys.path[:0]=[str(Path(__file__).resolve().parent/'tools'/d) for d in ('','build','pipeline','maint')]
from graph_io import write_text, python_inputs
from ninja_graph import escape

ROOT=Path(__file__).resolve().parent
SLUG='SLUS_213.76'


def python_command():
    """Respect an active environment; a host-side checkout venv may be incompatible with this shell."""
    if sys.prefix != sys.base_prefix:
        return sys.executable
    return '.venv/bin/python' if (ROOT/'.venv/bin/python').is_file() else sys.executable


def stages(nm):
    slug=SLUG
    return [('extract',['tools/build/prepare.py','extract',slug]),
            ('boundaries',['tools/build/boundaries.py',slug]),
            ('split',['tools/build/prepare.py','split',slug]),
            ('support',['tools/build/link_support.py',slug]),
            ('functions',['tools/build/split_objects.py',slug,'--functions']),
            ('owners',['tools/build/linkonce_owners.py','--write']),
            ('units',['tools/build/units.py',slug]),
            ('placement',['tools/build/split_objects.py',slug]),
            ('inventory',['tools/build/inventory.py']),
            ('graph',['tools/build/object_graph.py',slug]+(['--non-matching'] if nm else []))]


def stage_rules(records, py):
    lines=[]
    # A recorded source/header can disappear during a rename. Let its producer
    # rediscover the current inputs before Ninja attempts to build leaf objects.
    sources=sorted({path for _,_,io in records for path in io['reads']
                    if path.startswith(('src/','include/'))})
    lines += ['build '+escape(path)+': phony' for path in sources]
    for name,path,io in records:
        command=[py,'tools/build/graph_io.py','record',path,'--']+io['command']
        if name=='split':
            command=[py,'tools/build/graph_io.py','--log',str(Path(path).parents[1]/'splat.log'),'record',path,'--']+io['command']
        lines+=['rule prepare_'+name,'  command = '+shlex.join(command).replace('$','$$'),
                '  description = PREPARE '+name, '  restat = 1']
        if name=='graph':
            lines += ['  generator = 1']
        outputs=[path]+[x for x in io['writes'] if x!=path]
        lines += ['build %s%s: prepare_%s %s' % (escape(outputs[0]),
                  ' | '+' '.join(map(escape,outputs[1:])) if outputs[1:] else '',name,
                  ' '.join(map(escape,io['reads']+['tools/build/graph_io.py'])))]
    return '\n'.join(lines)+'\n'


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--non-matching',action='store_true')
    p.add_argument('--from-ninja',action='store_true',help=argparse.SUPPRESS)
    a=p.parse_args()
    versions=json.loads((ROOT/'config/versions.json').read_text())
    slug=SLUG;boot=versions[slug]['boot'];b='build/'+slug
    out=b+('-nm' if a.non_matching else '')
    py=python_command()
    header='ninja_required_version = 1.10\npy = '+shlex.quote(py).replace('$','$$')+'\n'
    preflight=f'''rule needexe
  command = $py tools/build/preflight.py exe {slug}
  generator = 1
build orig/{slug}/{boot}: needexe
'''
    have=(ROOT/'orig'/slug/boot).is_file()
    records=[]
    if have:
        for name,command in stages(a.non_matching):
            path=out+'/prepare/'+name+'.json'
            if not (ROOT/path).is_file():
                # The first configure discovers dynamic splat/partition outputs.
                # Later invocations let Ninja's normal restat/log handling decide.
                argv=[py,'tools/build/graph_io.py']
                if name=='split':argv+=['--log',out+'/splat.log']
                subprocess.run(argv+['record',path,'--']+command,cwd=ROOT,check=True)
            records.append((name,path,json.loads((ROOT/path).read_text())))
        bootstrap=out+'/bootstrap.ninja'
        write_text(ROOT/bootstrap,header+preflight+stage_rules(records,py))
        if not a.from_ninja:
            subprocess.run(['ninja','-f',bootstrap,records[-1][1]],cwd=ROOT,check=True)
        records=[(name,path,json.loads((ROOT/path).read_text())) for name,path,_ in records]
        leaves=json.loads((ROOT/out/'leaf_graph.json').read_text())
        # This registry is also checked in CI and by the deletion/read audit.
        edges=[dict(name='prepare_'+name,outputs=io['writes'],inputs=io['reads']+['tools/build/graph_io.py'],
                    command=io['command']) for name,_,io in records]+leaves
        graph=out+'/graph.json'
        text=header+preflight+stage_rules(records,py)+(ROOT/out/'objects.ninja').read_text()
        dependencies=[path for _,path,_ in records]+[out+'/leaf_graph.json',out+'/objects.ninja']
    else:
        text=header+preflight+f'build all: phony orig/{slug}/{boot}\ndefault all\n'
        dependencies=[];graph=None
    command=[py,'configure.py','--from-ninja']+(['--non-matching'] if a.non_matching else [])
    outputs=['build.ninja']+([graph,out+'/bootstrap.ninja'] if have else [])
    source_inputs=['configure.py','config/versions.json','orig/'+slug+'/'+boot]+python_inputs('configure.py')
    text+='rule reconfigure\n  command = '+shlex.join(command)+'\n  generator = 1\n  restat = 1\n'
    text+='build '+outputs[0]+(' | '+' '.join(outputs[1:]) if outputs[1:] else '')+': reconfigure '+ ' '.join(sorted(set(dependencies+source_inputs)))+'\n'
    if have:
        edges.append(dict(name='configure',outputs=outputs,inputs=sorted(set(dependencies+source_inputs)),command=command[1:]))
        write_text(ROOT/graph,json.dumps(edges,indent=1)+'\n')
    write_text(ROOT/'build.ninja',text)
    print('wrote build.ninja for '+slug+(' (NON_MATCHING)' if a.non_matching else ''))


if __name__=='__main__':main()
