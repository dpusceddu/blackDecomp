"""The objdiff project file: one unit per object, a category per library, asm-only units without a base object."""
import json, struct, sys, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import elfobj
import objdiff
import splits as S
import units as U


class ProjectFile(unittest.TestCase):
    def plan(self):
        return [dict(name='kynapse_a', base_in='cache/x.o', source='src/kynapse/a.cpp', library='kynapse',
                     functions=[], redefine={}, complete=True),
                dict(name='asm_game_tu_100000', base_in=None, source=None, library='game',
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
        self.assertNotIn('base_path', asm)
        self.assertTrue(asm['metadata']['auto_generated'])
        self.assertEqual(['kynapse'], source['metadata']['progress_categories'])

    def test_only_the_usa_version_has_source_units(self):
        with patch.object(sys, 'argv', ['objdiff.py', 'SLES_538.86']):
            with self.assertRaises(SystemExit):
                objdiff.main()


def asm(addr, body_words, padding=1, tail_labels=()):
    """Split assembly of one function in the format of tools/split_objects.py: code, `endlabel`, then padding nops."""
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


SPLIT_LIST = '''variant: SLUS_213.76
defaults: {compiler: ee-gcc2.95.3-136, flags: [-O2, -G0, -snas], sections: true}
splits:
  - {src: src/game/merged.cpp, range: [0x100000, 0x100080]}
  - {src: src/game/selectors.c, range: [0x100080, 0x100090], flags: [-O2, -G0, -snas, -DFIRST_ONLY], sections: false, functions: [0x100080]}
  - {src: src/game/selectors.c, range: [0x100090, 0x1000a0], flags: [-O2, -G0, -snas, -DSECOND_ONLY], sections: false, functions: [0x100090]}
'''
MERGED = '''#include "include_asm.h"
void recovered_a(void) {}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100020);
bool Mangled::IsSet() const { return true; }
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100060);
'''
SYMBOLS = 'IsSet__C7Mangled = 0x100040; // type:func\n'
# function starts and ends of the image: two recovered, two marked INCLUDE_ASM, the named one, two selector functions
TABLE = [(0x100000, 0x100020), (0x100020, 0x100040), (0x100040, 0x100060), (0x100060, 0x100080), (0x100080, 0x100090),
         (0x100090, 0x1000a0)]


class FakeElf:
    """Stands in for tools/elfinfo.Elf: the cached object file holds a JSON description of its symbols and sections."""
    def __init__(self, data):
        spec = json.loads(data)
        self._symbols = spec['symbols']
        self.sections = [dict(name=n, size=spec.get('sizes', {}).get(n, 0)) for n in spec['sections']]

    def symbols(self):
        return [dict(shndx=s.get('shndx', 1), **{k: v for k, v in s.items() if k != 'shndx'}) for s in self._symbols]


class UnitMapping(unittest.TestCase):
    """The mapping of source units onto objdiff units, for a split list with an INCLUDE_ASM translation unit, a file compiled
    twice with -D selectors, a mangled symbol that the base object refers to by its address name, and padding."""

    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        build = self.root / 'build/SLUS_213.76'
        (build / 'cache').mkdir(parents=True)
        for name, spec in (('merged', dict(
                sections=['.text.func_00100000', '.text.IsSet__C7Mangled', '.rodata'], sizes={'.rodata': 16},
                symbols=[dict(name='func_00100000'), dict(name='IsSet__C7Mangled'),
                         dict(name='func_00100040', shndx=0),      # the object refers to the function by address too
                         dict(name='func_00100020', shndx=0)])),    # the INCLUDE_ASM function is called, not defined
                           ('first', dict(sections=['.text'], symbols=[dict(name='func_00100080')])),
                           ('second', dict(sections=['.text'], symbols=[dict(name='func_00100090')]))):
            (build / 'cache' / (name + '.o')).write_text(json.dumps(spec))
        (build / 'objects.json').write_text(json.dumps([dict(name='units/merged', kind='cc'),
                                                         dict(name='units/selectors_100080', kind='cc'),
                                                         dict(name='units/selectors_100090', kind='cc')]))
        (build / 'objects_cache.json').write_text(json.dumps({'units/merged': 'cache/merged.o',
                                                              'units/selectors_100080': 'cache/first.o',
                                                              'units/selectors_100090': 'cache/second.o'}))
        (build / 'plan.json').write_text(json.dumps(dict(rename=[
            dict(obj='obj/units/merged.o', sections={'.rodata': '.rodata.00400010', '.text.func_00100000': '.text.00100000'})])))
        (build / 'symbols.ld').write_text('D_10F00 = 0x10F00;\nD_49BFBC = __end_bss;\n')
        (build / 'placement.json').write_text(json.dumps(dict(functions=[dict(addr=a, end=e, name='func_%08X' % a) for a, e in TABLE])))
        nonmatchings = self.root / 'asm/SLUS_213.76/nonmatchings'
        nonmatchings.mkdir(parents=True)
        for (addr, end), words in zip(TABLE, (7, 7, 7, 7, 3, 3)):
            (nonmatchings / ('func_%08X.s' % addr)).write_text(asm(addr, words, padding=(end - addr) // 4 - words))
        first = nonmatchings / 'func_00100000.s'     # the original refers to unit-owned data and to a number by name
        text = first.read_text().replace('00000000 */  nop', '3C020000 */  lui $2, %hi(D_00400018)', 1)
        first.write_text(text.replace('00000000 */  nop', '24420000 */  addiu $2, $2, %lo(D_10F00)', 1))
        split_file = self.root / 'splits.yaml'
        split_file.write_text(SPLIT_LIST)
        texts = {'src/game/merged.cpp': MERGED, 'src/game/selectors.c': '// selectors\n'}
        self.units = U.derive_units(S.load_splits(path=split_file), TABLE, S.Symbols(S.parse_symbols(SYMBOLS)),
                                    read=lambda path: texts[path])
        for target in (patch.object(objdiff, 'ROOT', self.root), patch.object(objdiff, 'Elf', FakeElf),
                       patch.object(objdiff, 'load_units', return_value=self.units)):
            target.start()
            self.addCleanup(target.stop)

    def test_the_fixture_units_are_what_the_test_assumes(self):
        names = [u['name'] for u in self.units]
        self.assertEqual(['merged', 'selectors_100080', 'selectors_100090'], names)
        merged = self.units[0]
        self.assertEqual(['source', 'asm', 'source', 'asm'], [f['status'] for f in merged['functions']])

    def test_every_source_function_is_in_a_base_unit_and_asm_functions_are_not(self):
        plan = objdiff.unit_plan('SLUS_213.76')
        by_unit = {u['name']: u for u in plan}
        self.assertEqual(['merged', 'selectors_100080', 'selectors_100090'], sorted(by_unit))
        in_base = {f['addr'] for u in plan for f in u['functions']}
        expected = {f['addr'] for u in self.units for f in u['functions'] if f['status'] == 'source'}
        self.assertEqual(expected, in_base)
        self.assertEqual({0x100000, 0x100040}, {f['addr'] for f in by_unit['merged']['functions']})

    def test_unrecovered_functions_are_target_only_units(self):
        plan = objdiff.unit_plan('SLUS_213.76')
        covered = {f['addr'] for u in plan for f in u['functions']}
        with patch('layout.library_of', return_value='game'), patch('layout.tu_of', return_value=0x100000), \
             patch('layout.tu_stem', return_value='tu_100000'), patch('progress.orphan_pieces', return_value=set()):
            rest = objdiff.remaining_plan('SLUS_213.76', covered)
        self.assertEqual([None], [u['base_in'] for u in rest])
        self.assertEqual({0x100020, 0x100060}, {f['addr'] for f in rest[0]['functions']})
        self.assertFalse(rest[0]['complete'])
        self.assertEqual(set(a for a, _ in TABLE), covered | {f['addr'] for f in rest[0]['functions']})

    def test_sizes_exclude_the_padding_that_follows_the_code(self):
        sizes = {f['addr']: f['size'] for u in objdiff.unit_plan('SLUS_213.76') for f in u['functions']}
        self.assertEqual({0x100000: 28, 0x100040: 28, 0x100080: 12, 0x100090: 12}, sizes)

    def test_renames_follow_the_address_name_even_when_the_base_refers_to_it(self):
        merged = next(u for u in objdiff.unit_plan('SLUS_213.76') if u['name'] == 'merged')
        self.assertEqual('func_00100040', merged['redefine']['IsSet__C7Mangled'])      # the undefined func_00100040 does not block it
        self.assertEqual({'.text.IsSet__C7Mangled': '.text.func_00100040'}, merged['sections'])

    def test_data_the_unit_owns_gets_the_name_the_original_uses(self):
        merged = next(u for u in objdiff.unit_plan('SLUS_213.76') if u['name'] == 'merged')
        self.assertEqual({'D_00400018': ('.rodata', 8)}, merged['symbols'])       # .rodata is placed at 0x400010

    def test_numbers_named_like_data_are_numbers_in_the_target(self):
        merged = next(u for u in objdiff.unit_plan('SLUS_213.76') if u['name'] == 'merged')
        self.assertEqual({'D_10F00': 0x10F00}, merged['constants'])               # D_49BFBC is an address, not a number
        text = objdiff.numeric_names('addiu $2, $2, %lo(D_10F00)\nlui $3, %hi(D_10F00)\nlui $4, %hi(D_00400000)\n', merged['constants'])
        self.assertEqual('addiu $2, $2, 3840\nlui $3, 0x1\nlui $4, %hi(D_00400000)\n', text)
        self.assertEqual('-32768', objdiff.numeric_names('%lo(D_8000)', {'D_8000': 0x8000}))


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
