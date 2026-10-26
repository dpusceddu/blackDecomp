"""Real unfinished TU context must never become linked source implicitly."""
from pathlib import Path
from types import SimpleNamespace
import struct
import sys
import unittest
sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import elfobj
import units_verify as V


def section_object():
    sections=[dict(index=0,name='',size=0),dict(index=1,name='.text.kept',size=8),
              dict(index=2,name='.text.pending',size=12),dict(index=3,name='.text.helper',size=4)]
    symbols=[dict(name='kept',type=2,shndx=1),dict(name='pending',type=2,shndx=2),
             dict(name='helper',type=2,shndx=3)]
    return SimpleNamespace(sections=sections),symbols


class FullTUContext(unittest.TestCase):
    def test_only_enabled_function_inputs_are_relocation_roots(self):
        elf,symbols=section_object()
        self.assertEqual(V.kept_text_names(elf,symbols,[dict(symbol='kept')]),{'.text.kept'})

    def test_context_requires_real_manifest_functions_or_explicit_helpers(self):
        elf,symbols=section_object()
        unit=dict(functions=[dict(symbol='kept',status='source'),dict(symbol='pending',status='asm')])
        self.assertFalse(V.valid_context_sections(elf,symbols,unit))
        unit['unlinked_context_helpers']=['helper']
        self.assertTrue(V.valid_context_sections(elf,symbols,unit))
        elf.sections[3]['name']='.text'
        self.assertFalse(V.valid_context_sections(elf,symbols,unit))

    def test_nonempty_anonymous_function_section_cannot_supply_context(self):
        elf,symbols=section_object()
        unit=dict(functions=[dict(symbol=s['name']) for s in symbols])
        elf.sections.append(dict(index=4,name='.text.unknown',size=8))
        self.assertFalse(V.valid_context_sections(elf,symbols,unit))

    def test_only_constants_owned_by_enabled_functions_supply_relocations(self):
        placement=dict(functions=[dict(name='kept',addr=0x1000),dict(name='pending',addr=0x1100)],
                       sections={'.rodata':[dict(owner='pending')],'.lit4':[dict(owner='kept')],
                                 '.gcc_except_table':[dict(owner=None)]})
        self.assertEqual(V.owned_constant_names([dict(addr=0x1000)],placement),{'.lit4'})

    def test_unplaced_allocated_inputs_miss_every_sorted_output_wildcard(self):
        names=['','.text.kept','.text.pending','.rodata.pending','.debug_info','.shstrtab',
               '.reginfo','.MIPS.abiflags']
        strings=b'\0';offsets=[0]
        for name in names[1:]:offsets.append(len(strings));strings+=name.encode()+b'\0'
        raw=bytearray(52+len(strings));raw[52:]=strings
        table=len(raw);headers=[]
        for i,name in enumerate(names):
            flags=6 if i in(1,2) else 2 if i in(3,6,7) else 0
            kind=0x70000006 if i==6 else 0x7000002A if i==7 else 3 if i==5 else 1
            headers.append((offsets[i],kind,flags,0,52 if i==5 else 0,len(strings)if i==5 else 4,0,0,4,0))
        raw.extend(b''.join(struct.pack('<10I',*h)for h in headers))
        struct.pack_into('<I',raw,32,table);struct.pack_into('<HHH',raw,46,40,len(names),5)
        result=elfobj.unplaced_allocated_sections(raw,{'.text.kept'})
        self.assertEqual(set(result),{'.text.pending','.rodata.pending'})
        self.assertTrue(all(name.startswith('.discard.')for name in result.values()))

    def test_unfinished_local_data_is_ignored_only_when_its_caller_is_dropped(self):
        elf,symbols=section_object()
        elf.sections += [dict(index=4,name='.private',type=1),
                         dict(index=5,name='.rel.pending',type=9,info=2)]
        for section in elf.sections:section.setdefault('type',1)
        symbols.append(dict(name='',type=3,bind=0,shndx=4))
        elf.content=lambda _:struct.pack('<II',0,3<<8|5)
        elf.section=lambda _:None
        unit=dict(data_ranges=[]);placement=dict(functions=[],sections={'.rodata':[],'.lit4':[],'.gcc_except_table':[]})
        self.assertIsNone(V.data_sections(elf,symbols,unit,[dict(addr=0x1000,symbol='kept')],placement))
        elf.sections[5]['info']=1
        self.assertEqual(V.data_sections(elf,symbols,unit,[dict(addr=0x1000,symbol='kept')],placement),'section')


if __name__=='__main__':unittest.main()
