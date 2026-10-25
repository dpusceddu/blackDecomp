"""Assembler includes preserve relocations, fixed encodings and compiler state."""
from pathlib import Path
import struct
import sys
import unittest
sys.path[:0] = [str(Path(__file__).resolve().parents[1]/'tools'/d) for d in ('','build')]
from asm_syntax import translate
from elfinfo import Elf
from elfobj import restore_gprel


def relocation_object(marker, addend=0, kind=2):
    names=['','.text.test','.rel.text.test','.strtab','.symtab','.shstrtab']
    strings=b'\0'+marker.encode()+b'\0dest\0'
    sym=[bytes(16),struct.pack('<IIIBBH',1,0,0,0x10,0,1),
         struct.pack('<IIIBBH',len(marker)+2,0,0,0x10,0,0)]
    shstrings=b'\0';offsets=[0]
    for name in names[1:]:
        offsets.append(len(shstrings));shstrings+=name.encode()+b'\0'
    payloads=[b'',struct.pack('<I',addend),struct.pack('<II',0,2<<8|kind),strings,b''.join(sym),shstrings]
    raw=bytearray(52);headers=[]
    for i,payload in enumerate(payloads):
        raw+=bytes((-len(raw))%4);start=len(raw);raw+=payload
        typ=[0,1,9,3,2,3][i]
        headers.append((offsets[i],typ,6 if i==1 else 0,0,start,len(payload),4 if i==2 else 3 if i==4 else 0,
                        1 if i in (2,4) else 0,4,8 if i==2 else 16 if i==4 else 0))
    raw+=bytes((-len(raw))%4);shoff=len(raw)
    raw+=b''.join(struct.pack('<10I',*h) for h in headers)
    raw[:7]=b'\x7fELF\x01\x01\x01'
    struct.pack_into('<HHIIIIIHHHHHH',raw,16,1,8,1,0,0,shoff,0,52,0,0,40,len(headers),5)
    return bytes(raw)


class IncludedSyntax(unittest.TestCase):
    def test_sn_labels_are_expanded_without_size_or_macros(self):
        text='.include "macro.inc"\n.section .text.00100000, "ax"\nglabel func_00100000\n  alabel func_00100000\nendlabel func_00100000\n'
        out,_=translate(text,sn=True)
        self.assertNotIn('macro.inc',out)
        self.assertEqual(out.count('\nfunc_00100000:'),1)
        self.assertIn('__nonmatching_func_00100000:',out)
        self.assertTrue(out.endswith('.text\n.set reorder\n.set at\n.set macro\n'))

    def test_short_loop_and_undecodable_word_are_fixed_encodings(self):
        text='    /* 0 00100000 FEFF4014 */  bnez $2, .L00100000\n    /* 4 00100004 FFFFFFFF */ .word 0xffffffff\n'
        out,_=translate(text,sn=True)
        self.assertIn('.word 0x1440FFFE',out)
        self.assertIn('.word 0xffffffff',out)

    def test_gp_addend_and_jump_remain_symbolic(self):
        text='    /* 0 00100000 0100828F */ lw $2, (D_00400000 + 0x4) /* gp_rel: (D_00400000 + 0x4) */\n    /* 4 00100004 0000040C */ jal func_00100000\n'
        out,aliases=translate(text,sn=True)
        self.assertIn('.word D_00400000_add_4',out)
        self.assertEqual(aliases,{'D_00400000_add_4':'D_00400000 + 0x4'})
        self.assertIn('__jump_0C000000_00100004:',out)
        self.assertIn('.word func_00100000',out)

    def test_normalization_changes_only_declared_word_and_relocation_kind(self):
        for marker,opcode,kind,addend in [('__gprel_8F820000_00100000',0x8f820000,7,0),
                                           ('__jump_0C000000_00100000',0x0c000001,4,4)]:
            before=Elf(relocation_object(marker,addend))
            after=Elf(restore_gprel(before.data))
            self.assertEqual(struct.unpack('<I',after.content(after.section('.text.test')))[0],opcode)
            self.assertEqual(struct.unpack('<II',after.content(after.section('.rel.text.test'))),(0,2<<8|kind))
            self.assertEqual(after.symbols(),before.symbols())

    def test_wrong_relocation_is_rejected(self):
        with self.assertRaises(ValueError):
            restore_gprel(relocation_object('__gprel_8F820000_00100000',kind=5))


if __name__=='__main__':
    unittest.main()
