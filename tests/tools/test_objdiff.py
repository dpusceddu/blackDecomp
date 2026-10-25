"""The objdiff project file: one unit per object, a category per library, assembly-backed functions excluded from source progress."""
import json, struct, sys, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import elfobj
import objdiff


class ProjectFile(unittest.TestCase):
    def plan(self):
        return [dict(name='kynapse_a', base_in='cache/x.o', source='src/kynapse/a.cpp', library='kynapse',
                     functions=[], redefine={}, complete=True),
                dict(name='asm_game_tu_100000', base_in=None, source='src/game/a.c', library='game',
                     functions=[], redefine={}, complete=False)]

    def test_units_categories_and_paths(self):
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(objdiff, 'ROOT', Path(directory)):
                self.assertEqual(2, objdiff.write_project('SLUS_213.76', self.plan()))
            project = json.loads((Path(directory) / 'objdiff.json').read_text())
        self.assertEqual(['game', 'kynapse'], [c['id'] for c in project['progress_categories']])
        source, asm = project['units']
        self.assertEqual('kynapse/kynapse_a', source['name'])
        self.assertEqual('build/SLUS_213.76/objdiff/base/kynapse_a.o', source['base_path'])
        self.assertEqual('src/kynapse/a.cpp', source['metadata']['source_path'])
        self.assertTrue(source['metadata']['complete'])
        self.assertEqual('build/SLUS_213.76/objdiff/base/asm_game_tu_100000.o', asm['base_path'])
        self.assertEqual('ninja',project['custom_make'])
        self.assertEqual([],project['custom_args'])
        self.assertEqual(['kynapse'], source['metadata']['progress_categories'])

    def test_only_the_usa_version_has_source_units(self):
        with patch.object(sys, 'argv', ['objdiff.py', 'SLES_538.86']):
            with self.assertRaises(SystemExit):
                objdiff.main()


def asm(addr, body_words, padding=1, tail_labels=()):
    """Split assembly of one function in the format of tools/build/split_objects.py: code, `endlabel`, then padding nops."""
    lines = ['.section .text.%08X, "ax"' % addr, 'glabel func_%08X' % addr]
    for i in range(body_words):
        lines.append('    /* %X %08X 00000000 */  nop' % (addr - 0x100000 + 4 * i, addr + 4 * i))
    lines.append('endlabel func_%08X' % addr)
    for i in range(padding):
        lines.append('    /* %X %08X 00000000 */  nop' % (addr - 0x100000 + 4 * (body_words + i), addr + 4 * (body_words + i)))
    for name in tail_labels:
        lines += ['.section .rodata.%08X, "a"' % addr, 'dlabel %s' % name, '    /* 0 0 00000000 */ .word 0', 'enddlabel %s' % name]
    return '\n'.join(lines) + '\n'


class CodeSize(unittest.TestCase):
    def test_trailing_alignment_padding_is_not_part_of_the_function(self):
        self.assertEqual(36, objdiff.code_size(asm(0x100230, 9, padding=1), 0x100230, 40))
        self.assertEqual(36, objdiff.code_size(asm(0x100230, 9, padding=3), 0x100230, 48))

    def test_data_sections_after_the_code_are_ignored(self):
        self.assertEqual(8, objdiff.code_size(asm(0x100000, 2, 1, tail_labels=['D_00400000']), 0x100000, 12))

    def test_a_function_with_switch_fragments_spans_up_to_its_last_fragment(self):
        text = asm(0x100000, 2, padding=0).replace('endlabel func_00100000\n', 'endlabel func_00100000\n'
            '.align 3\njlabel func_00100008\n    /* 8 00100008 00000000 */  nop\n    /* C 0010000C 00000000 */  nop\n'
            'endlabel func_00100008\n    /* 10 00100010 00000000 */  nop\n')
        self.assertEqual(16, objdiff.code_size(text, 0x100000, 20))

    def test_without_an_endlabel_the_span_is_used(self):
        self.assertEqual(20, objdiff.code_size('glabel f\n', 0x100000, 20))


class UnitMapping(unittest.TestCase):
    def test_one_comparison_unit_keeps_the_whole_file_including_assembly(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory)
            build=root/'build/SLUS_213.76'
            build.mkdir(parents=True)
            unit=dict(name='mixed',library='game',functions=[dict(addr=1,status='source'),dict(addr=2,status='asm')])
            (build/'unit_objects.json').write_text(json.dumps([dict(name='units/mixed',kind='cc',src='src/game/mixed.c',unit=unit)]))
            with patch.object(objdiff,'ROOT',root):
                plan=objdiff.unit_plan('SLUS_213.76')
            self.assertEqual(len(plan),1)
            self.assertEqual([1,2],[f['addr'] for f in plan[0]['functions']])
            self.assertFalse(plan[0]['complete'])


def elf_object(entries, flags=0x20920001):
    """A minimal ELF32 little-endian object: a header and one SHT_REL section holding the relocation entries."""
    shoff = 52 + 8 * len(entries)
    header = b'\x7fELF\x01\x01\x01' + bytes(9) + struct.pack('<HHIIIIIHHHHHH', 1, 8, 1, 0, 0, shoff, flags, 52, 0, 0, 40, 2, 0)
    body = b''.join(struct.pack('<II', offset, info) for offset, info in entries)
    null_section = bytes(40)
    rel = struct.pack('<IIIIIIIIII', 0, 9, 0, 0, 52, len(body), 0, 0, 4, 8)
    return header + body + null_section + rel


class ObjectNormalization(unittest.TestCase):
    def test_header_flags_are_copied_from_the_template(self):
        target, base = elf_object([], 0x20920001), elf_object([], 0x20924001)
        fixed = elfobj.copy_header_flags(target, base)
        self.assertEqual(base[0x24:0x28], fixed[0x24:0x28])
        self.assertEqual(target[:0x24] + target[0x28:], fixed[:0x24] + fixed[0x28:])

    def test_literal_relocations_become_gp_relative(self):
        data = elf_object([(4, 0x0A08), (8, 0x0B05), (12, 0x0C08)])             # LITERAL, HI16, LITERAL
        fixed = elfobj.literal_as_gprel(data)
        types = [struct.unpack_from('<I', fixed, 52 + 8 * i + 4)[0] & 0xFF for i in range(3)]
        self.assertEqual([7, 5, 7], types)
        self.assertEqual(0x0A, struct.unpack_from('<I', fixed, 52 + 4)[0] >> 8)       # the symbol index stays


if __name__ == '__main__':
    unittest.main()
