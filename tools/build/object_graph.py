#!/usr/bin/env python3
"""Generate real assembler includes and ordinary per-object Ninja edges from the split image."""
import argparse
import json
import re
from pathlib import Path
import sys
sys.path[:0] = [str(Path(__file__).resolve().parents[1]), str(Path(__file__).resolve().parent)]
from asm_syntax import translate
from splits import group_splits, load_splits
from units import load_units
from split_objects import write_if_changed

ROOT = Path(__file__).resolve().parents[2]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version')
    ap.add_argument('--non-matching', action='store_true')
    a = ap.parse_args()
    slug = a.version
    build = Path('build') / slug
    out = Path(str(build) + ('-nm' if a.non_matching else ''))
    out.mkdir(parents=True, exist_ok=True)
    placement = json.loads((build / 'placement.json').read_text())
    units = load_units(variant=slug, facts=False)
    ownership = {f['addr']: u for u in units for f in u['functions']
                 if any(lo <= f['addr'] < hi for lo,hi in u.get('ranges', [u['range']]))}
    funcs = {f['addr']: f for f in placement['functions']}
    aliases, objects, edges = {}, [], []
    includes = {}
    for addr, u in ownership.items():
        f = funcs[addr]
        original = Path(placement['objects'][f['obj']]['src'])
        directory = Path('asm') / slug / 'nonmatchings' / Path(u['source']).relative_to('src').with_suffix('')
        path = directory / (f['name'] + '.s')
        sn = '-snas' in u['flags'] or any(x.startswith('--assembler=sn-') for x in u['flags'])
        text, extra = translate(original.read_text(), sn=sn)
        write_if_changed(path, text)
        aliases.update(extra)
        includes.setdefault(u['name'], []).append(path.as_posix())
    write_if_changed(out/'asm_aliases.ld','\n'.join('%s = %s;'%x for x in sorted(aliases.items()))+'\n')
    layout = json.loads((build / 'layout.json').read_text())
    limits = {s['name']: s['addr']+s.get('orig_size', 0) for s in layout['sections']}
    all_slots = {}
    for sec, entries in placement['sections'].items():
        if sec == '.text':
            continue
        for i, e in enumerate(entries):
            if e.get('owner'):
                stop = entries[i+1].get('key') if i+1 < len(entries) else None
                all_slots.setdefault(e['owner'], []).append((sec, e['key'], stop or limits[sec]))
    for u in units:
        flags = list(u['flags'])
        if a.non_matching:
            flags.append('-DNON_MATCHING')
        u['functions'] = [f for f in u['functions'] if any(lo <= f['addr'] < hi for lo, hi in u.get('ranges', [u['range']]))]
        slots = {}
        for f in u['functions']:
            for sec, low, high in all_slots.get('func_%08X' % f['addr'], []):
                slots.setdefault(sec, []).append([low, high, f['addr']])
        objects.append(dict(name='units/' + u['name'], kind='cc', src=u['source'], compiler=u['compiler'],
                            flags=flags, slots=slots, includes=includes.get(u['name'], []), unit=u))
    # Functions without source belong to one assembly segment, never one object per function.
    remaining = [f for f in placement['functions'] if f['addr'] not in ownership]
    if remaining:
        source = Path('asm') / slug / 'text_units.s'
        lines = [re.sub(r'^\.section \.text\.[^\n]+', '.text', Path(placement['objects'][f['obj']]['src']).read_text(), flags=re.M) for f in remaining]
        write_if_changed(source, '\n'.join(lines) + '\n')
        objects.append(dict(name='asm/text', kind='asm', src=str(source), includes=[placement['objects'][f['obj']]['src'] for f in remaining]))
    text_objects = {f['obj'] for f in placement['functions']}
    for name, spec in placement['objects'].items():
        if name not in text_objects:
            objects.append(dict(spec, name=name))
    from ninja_graph import Graph
    graph=Graph(out)
    original_asm=[spec['src'] for spec in placement['objects'].values() if spec['src'].endswith('.s')]
    config=['config/versions.json','include/macro.inc']
    symbols='config/'+slug+'/symbols.txt'
    if Path(symbols).exists():config.append(symbols)
    common=[str(build/x) for x in ('placement.json','layout.json','labels.json','functions.json','symbols.ld')]
    state_files=[];raw_objects=[];bases=[];targets=[]
    for o in objects:
        spec=out/'spec'/(o['name']+'.json')
        obj=out/'obj'/(o['name']+'.o')
        write_if_changed(spec,json.dumps(o,sort_keys=True)+'\n')
        outputs=[str(obj)]
        inputs=[o['src'],str(spec)]+o.get('includes',[])+config
        if o['kind']=='cc':
            outputs.append(str(obj)+'.json')
            state_files.append(str(obj)+'.json')
            if a.non_matching:inputs+=common+[str(out/'asm_aliases.ld')]
        else:
            # Binary assets expanded for old GAS are real object inputs too.
            inputs += re.findall(r'^\.incbin "([^"]+)"',Path(o['src']).read_text(),re.M)
        graph.add('object/'+o['name'],['tools/build/object_compile.py',str(spec),str(obj)],outputs,inputs,depfile=str(obj)+'.d')
        raw_objects.append(str(obj))
        if o['kind']=='cc':
            base=out/'objdiff/base'/(o['unit']['name']+'.o')
            target=out/'objdiff/target'/(o['unit']['name']+'.o')
            originals=[str(Path('asm')/slug/'nonmatchings'/('func_%08X.s'%f['addr'])) for f in o['unit']['functions']]
            graph.add('objdiff/'+o['unit']['name'],['tools/objdiff.py','--unit',str(spec),'--output',str(base)],
                      [str(base),str(target),str(target.with_suffix('.s'))],
                      [str(obj),str(obj)+'.json',str(spec),str(build/'placement.json'),str(build/'symbols.ld'),
                       'orig/'+slug+'/'+slug]+originals+config)
            bases.append(str(base));targets.append(str(target))
    listing=out/'unit_objects.json'
    write_if_changed(listing,json.dumps(objects,indent=1,sort_keys=True)+'\n')
    link_outputs=[str(out/x) for x in ('linked.elf','link.ld','unit_facts.json','objects.json','objects_cache.json','objects.rsp','link.map','link.log')]
    if a.non_matching:link_outputs.append(str(out/'nm_fallback.json'))
    graph.add('link',['tools/build/unit_link.py',slug]+(['--non-matching'] if a.non_matching else []),link_outputs,
              raw_objects+state_files+[str(listing),str(out/'asm_aliases.ld')]+common+config,console=True)
    boot=json.loads(Path('config/versions.json').read_text())[slug]['boot']
    blobs=['data/'+slug+'/'+s['blob'] for s in layout['sections'] if s['source']=='blob']
    image=str(out/(boot+'.elf'))
    graph.add('pack',['tools/build/pack_elf.py',str(out/'linked.elf'),str(build/'layout.json'),'data/'+slug+'/elf',image],
              [image],[str(out/'linked.elf'),str(build/'layout.json')]+blobs)
    check=str(out/'ok.stamp')
    graph.add('check',['tools/check_elf.py',slug,image,'--stamp',check],[check],
              [image,str(out/'linked.elf'),str(out/'objects.json'),'config/'+slug+'/checksums.sha256',
               'orig/'+slug+'/'+boot]+common+original_asm,console=True)
    graph.add('all',None,['all'],[image if a.non_matching else check])
    if slug=='SLUS_213.76' and not a.non_matching:
        shared=[str(build/x) for x in ('placement.json','layout.json','functions.json','units.json','unit_facts.json','inline_owners.txt')]
        raw_asm=[str(p) for p in Path('asm/'+slug).glob('*.s')]+[str(p) for p in Path('asm/'+slug+'/data').glob('*.s')]
        shared+=['build/auto/inventory.json','orig/'+slug+'/'+boot,'config/versions.json',
                 'config/'+slug+'/libraries.txt',symbols]
        tus=str(build/'tus.yaml')
        graph.add('tus',['tools/build/tus.py','map','--out',tus],[tus],shared+raw_asm+['config/tus_overrides.yaml'])
        graph.add('tus_alias',None,['tus'],[tus])
        graph.add('owners_alias',None,['owners'],[str(build/'inline_owners.txt')])
        graph.add('project',['tools/objdiff.py',slug,'--project'],['objdiff.json'],[str(listing),str(build/'placement.json')]+config+
                  (['.local/objdiff.json'] if Path('.local/objdiff.json').exists() else []))
        graph.add('objdiff_alias',None,['objdiff'],['objdiff.json']+bases+targets)
        graph.add('objdiff_objects_alias',None,['objdiff_objects'],bases+targets)
        report=str(build/'report.json')
        graph.add('report',['tools/objdiff.py',slug,'--report-only'],[report],['objdiff.json',str(build/'placement.json'),str(out/'linked.elf')]+bases+targets,console=True)
        graph.add('report_alias',None,['report'],[report])
        progress=str(build/'progress.json')
        graph.add('progress',['tools/progress.py',slug,'--check'],[progress],shared+[tus,report,str(out/'linked.elf')]+original_asm,console=True)
        graph.add('progress_alias',None,['progress'],[progress])
        badge_files=[str(build/'badges'/(x+'.json')) for x in ('game','kynapse','rw_core','rw_audio','animation','physics','apt','sony','libc')]
        graph.add('badges',['tools/badges.py',slug,'--no-progress'],badge_files+['progress/code.json','progress/functions.json','docs/status.md'],
                  [progress]+shared+[tus]+[u['source'] for u in units],generator=True,console=True)
        graph.add('badges_alias',None,['badges'],badge_files)
    write_if_changed(out/'leaf_graph.json',json.dumps(graph.edges,indent=1)+'\n')
    write_if_changed(out/'objects.ninja',graph.render()+'default all\n')
    print('%d source objects, %d assembly objects'%(len(units),len(objects)-len(units)))


if __name__=='__main__':main()
