"""Unsectioned CFI mode remains relocatable after normalizing one TU object."""
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
sys.path[:0]=[str(Path(__file__).resolve().parents[1]/'tools'/'build')]
from elfinfo import Elf
from elfobj import split_text_sections

AS=shutil.which('mipsel-linux-gnu-as')
LD=shutil.which('mipsel-linux-gnu-ld')


@unittest.skipUnless(AS and LD,'MIPS binutils are not installed')
class UnitSections(unittest.TestCase):
    def setUp(self):
        directory=tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root=Path(directory.name)
        source=self.root/'input.s'
        source.write_text(''' .set noreorder
.text
.globl first
.type first,@function
first:
jal second
nop
.size first,.-first
.globl second
.type second,@function
second:
jr $31
nop
.size second,.-second
.data
.word .text+8
.word 0x10
''')
        self.original=self.root/'original.o'
        subprocess.run([AS,'-EL','-march=r5900','-o',str(self.original),str(source)],check=True)
        spec=dict(unit=dict(functions=[dict(addr=0x100000,symbol='first'),dict(addr=0x100008,symbol='second')]))
        self.normalized=self.root/'normalized.o'
        self.normalized.write_bytes(split_text_sections(self.original.read_bytes(),spec))

    def link(self,path,order):
        script=self.root/(path.stem+'.ld')
        script.write_text('SECTIONS { . = 0x100000; .text : { '+order+' } .data ALIGN(16) : { *(.data) } /DISCARD/ : { *(*) } }')
        output=path.with_suffix('.elf')
        subprocess.run([LD,'-m','elf32ltsmip','-T',str(script),'-o',str(output),str(path)],check=True,stdout=subprocess.DEVNULL,stderr=subprocess.PIPE)
        return Elf(output.read_bytes())

    def test_code_addresses_and_native_range_word_are_identical(self):
        before=self.link(self.original,'*(.text)')
        after=self.link(self.normalized,'*(.text.first) *(.text.second)')
        for section in ('.text','.data'):
            self.assertEqual(before.content(before.section(section)),after.content(after.section(section)))
        normalized=Elf(self.normalized.read_bytes())
        self.assertEqual(normalized.section('.text')['size'],0)
        self.assertEqual(normalized.section('.text.first')['size'],8)
        self.assertEqual(normalized.section('.text.second')['size'],8)

    def test_section_reference_follows_function_when_inputs_move(self):
        after=self.link(self.normalized,'*(.text.second) *(.text.first)')
        pointer,span=struct.unpack_from('<II',after.content(after.section('.data')))
        self.assertEqual((pointer,span),(0x100000,0x10))
        first=next(s['value'] for s in after.symbols() if s['name']=='first')
        call=struct.unpack_from('<I',after.content(after.section('.text')),first-after.section('.text')['addr'])[0]
        self.assertEqual((call&0x3ffffff)<<2,0x100000)


if __name__=='__main__':
    unittest.main()
