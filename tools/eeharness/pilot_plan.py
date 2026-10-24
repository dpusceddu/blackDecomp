#!/usr/bin/env python3
"""Stage the first 50-candidate diagnostic batch without promoting raw drafts.

Requires the existing ignored autodecomp results and Phase 2 report. Recovered
game source from that cache stays private until reviewed. C++ type conversions
below make diagnostics compile; they do not establish correct ABI or behavior.
"""
import argparse
import json
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[2]
SMALL=(0x14d998,0x182550,0x1297a0,0x13bac8,0x16b4f8,0x182968,0x188fb8,0x18d5d0,
       0x18d918,0x1abee0,0x1c1a98,0x1c2a98,0x1dd748,0x1e8980,0x1ea580,0x1ed648,
       0x1f1608,0x12ae00,0x135b60,0x16e250,0x176f38,0x178f28,0x179668,0x179680,
       0x17b930,0x17ea70,0x182158,0x1a27a8,0x1a9ea0,0x1adbc0,0x1adc10,0x1c2a68,
       0x23bc28,0x250370,0x2722d0,0x274fd8,0x27d098,0x16a250,0x177780,0x177aa0)
LARGE=(0x21c268,0x1d7ee0,0x21e420,0x1a9908,0x284bf0,0x21ea58,0x165f30,0x22a440)
READABLE={0x1c1a98:'RefreshAtCoordinates',0x1c2a98:'CurrentBuffer',0x1dd748:'PlaybackInterval',
          0x1f1608:'UpdateLinkedItems',0x12ae00:'VisitWorldActor',0x176f38:'AdvanceRing',
          0x178f28:'IsUnblockedPlayer',0x179668:'TableWord',0x179680:'TableFollowingWord',
          0x17ea70:'IsWeaponReadyWithoutAction',0x1a27a8:'IsMovementReady',0x1c2a68:'SwapBuffer',
          0x2722d0:'SelectedRecord',0x274fd8:'ContainsAddress'}
FLAGS=['-O2','-G0','-snas','-ffunction-sections','-fno-exceptions','-fno-rtti']


def cpp_draft(address,text):
    text=text.replace('#include "ps2/recovered_types.h"\n','#include "ps2/recovered_types.h"\nextern "C" {\n',1)+'\n}\n'
    if address==0x16e250:text=text.replace('s32 *arg2','s64 *arg2')
    if address==0x16a250:text=text.replace('func_0016A4C0(arg0,','func_0016A4C0((s64*)arg0,')
    if address in (0x21c268,0x21e420,0x21ea58,0x22a440):
        typ='s32*' if address==0x21ea58 else 'u16**'
        text=re.sub(r'(?<![\w])sp(?=\s*[,\)])',lambda _:f'({typ})sp',text)
    if address==0x21e420:
        text=re.sub(r'var_16 = (func_\w+\()',r'var_16 = (s32*) \1',text)
    if address==0x21ea58:text=text.replace('(sp + 16),','(s32*)(sp + 16),')
    if address==0x22a440:
        text=text.replace('M2C_UNK *var_5;','const void *var_5;')
        for before,after in (
            ('temp_5_5 = "apply";','temp_5_5 = (M2C_UNK*)"apply";'),
            ('(sp + 16), 1, 1, 0','(u16**)(sp + 16), 1, 1, 0'),
            ('var_19 == M2C_FIELD(arg1, s32 *, 0x10)','(s32)var_19 == M2C_FIELD(arg1, s32 *, 0x10)'),
            ('M2C_FIELD(var_19, s32 *, 0x44) != var_5_4','M2C_FIELD(var_19, s32 *, 0x44) != (s32)var_5_4'),
            ('var_19 == D_0043DF48','(s32)var_19 == D_0043DF48'),
            ('s32 *, -4) != D_0043DF40','s32 *, -4) != (s32)D_0043DF40')):
            text=text.replace(before,after)
    return text


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=ROOT/'build/eeharness/pilot')
    args=parser.parse_args();out=args.output.resolve()
    if not out.is_relative_to(ROOT/'build'):parser.error('private drafts must stay under build/')
    (out/'drafts').mkdir(parents=True,exist_ok=True)
    auto=json.loads((ROOT/'build/auto.json').read_text())
    inventory={f['address']:f for f in json.loads((ROOT/'build/eeharness/phase2/gate-2.json').read_text())['functions']}
    rows=[]
    for address in SMALL+LARGE:
        draft=auto[hex(address)];source=out/'drafts'/f'{address:x}.cpp'
        text=cpp_draft(address,draft['source']);source.write_text(text)
        signature=re.search(r'\n([^\n]+?)\s+\**\s*'+draft['name']+r'\(',text)
        ret=signature[1].strip() if signature else 'unknown'
        abi={'f32':'f32','void':'void','s128':'i128','s64':'i64'}.get(ret,'i32')
        row=dict(address=address,size=inventory[address]['size'],symbol=draft['name'],
                 source=str(source.relative_to(ROOT)),returns=abi,abi_reviewed=False,readable_reviewed=False,
                 flags=FLAGS+['-fpermissive'],origin='existing generated draft; diagnostic only')
        if address in READABLE:
            row.update(source='src/game/pilot_scalar.cpp',name=READABLE[address],
                       abi_reviewed=True,readable_reviewed=True,flags=FLAGS,
                       origin='readable access view reviewed against original instructions',
                       returns='f32' if address==0x1dd748 else 'void' if address in (0x1f1608,0x176f38) else 'i64')
        if address==0x1a9908:
            row.update(source='src/game/graphics_selector_1a9908.cpp',
                       symbol='Turn__Q218AnimationSelectPS28SelectorPcPQ218AnimationSelectPS25Actorlf',
                       returns='void',abi_reviewed=True,readable_reviewed=True,
                       flags=['-O2','-G0','-snas','-ffunction-sections','-mvu0-use-vf0-vf31','-fno-rtti','-fno-exceptions'])
        rows.append(row)
    notification=(ROOT/'src/game/graphics_overlay_drafts.cpp').read_text().split('#if 0',1)[1].split('#endif',1)[0]
    notification=notification.replace('void Update(float);','void Update(float) __asm__("func_001F4770");')
    source=out/'drafts/notification.cpp';source.write_text(notification)
    vector_flags=next(row['flags'] for row in rows if row['address']==0x1a9908)
    rows.append(dict(address=0x1f4770,size=inventory[0x1f4770]['size'],symbol='func_001F4770',source=str(source.relative_to(ROOT)),
                     returns='void',abi_reviewed=True,readable_reviewed=False,flags=vector_flags))
    rows.append(dict(address=0x1046b0,size=inventory[0x1046b0]['size'],symbol='func_001046B0',
                     source='src/game/graphics_frontend_1046b0.cpp',returns='void',abi_reviewed=True,readable_reviewed=True,
                     flags=['-O2','-G0','-snas','-ffunction-sections','-fbyte-bool','-fno-rtti','-fno-exceptions']))
    (out/'plan.json').write_text(json.dumps(rows,indent=2)+'\n')
    print('Staged 50 candidates, including ten game functions above 1 KB. Raw drafts cannot be promoted.')


if __name__=='__main__':main()
