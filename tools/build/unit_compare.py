#!/usr/bin/env python3
"""Explain a full-image mismatch with function sizes and decoded instruction diffs."""
import argparse
import difflib
import json
from pathlib import Path
import struct
import sys
sys.path[:0] = [str(Path(__file__).resolve().parents[1]/d) for d in ('','build')]
from elfinfo import Elf
from objdiff import code_size


def instruction_diff(want, got, address, limit=24):
    """Changed instructions with a small amount of context; never raw hex words."""
    import rabbitizer
    def instructions(data):
        return [rabbitizer.Instruction(word,address+offset,rabbitizer.InstrCategory.R5900).disassemble()
                for offset,(word,) in zip(range(0,len(data),4),struct.iter_unpack('<I',data))]
    left,right=instructions(want),instructions(got)
    lines=list(difflib.unified_diff(left,right,fromfile='original',tofile='compiled',n=2,lineterm=''))
    return lines[:limit]+(['...'] if len(lines)>limit else [])


def compare(slug, build):
    root=Path(__file__).resolve().parents[2]
    boot=json.loads((root/'config/versions.json').read_text())[slug]['boot']
    original=Elf((root/'orig'/slug/boot).read_bytes())
    linked=Elf((build/'linked.elf').read_bytes())
    original_text=original.section('.text');linked_text=linked.section('.text')
    want=original.content(original_text);got=linked.content(linked_text)
    symbols={s['name']:s for s in linked.symbols()}
    problems=[]
    for obj in json.loads((build/'objects.json').read_text()):
        if obj['kind']!='cc':
            continue
        for f in obj['unit']['functions']:
            r=obj['resolved'][str(f['addr'])]
            name='func_%08X'%f['addr']
            sym=symbols.get(r['link_name'])
            if not sym:
                continue
            assembly=root/'asm'/slug/'nonmatchings'/(name+'.s')
            expected=code_size(assembly.read_text(),f['addr'],f['size'])
            actual=r['size'] if r['status']=='source' else expected
            a=f['addr']-original_text['addr'];b=sym['value']-linked_text['addr']
            before,after=want[a:a+expected],got[b:b+actual]
            if before!=after or actual!=expected:
                reason='size differs (%d bytes, original %d)'%(actual,expected) if actual!=expected else 'differs from the original'
                problems.append((actual!=expected,obj['src'],name,reason,before,after,f['addr']))
    problems.sort(key=lambda p:not p[0])
    for _,source,name,reason,before,after,address in problems[:12]:
        print('MISMATCH %s: %s: %s'%(source,name,reason))
        print('\n'.join(instruction_diff(before,after,address)))
    if len(problems)>12:
        print('... %d more differing functions'%(len(problems)-12))
    return len(problems)


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('version')
    ap.add_argument('build',type=Path)
    a=ap.parse_args()
    return bool(compare(a.version,a.build))


if __name__=='__main__':
    sys.exit(main())
