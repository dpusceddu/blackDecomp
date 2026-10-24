"""Explicit source data must replace whole labeled spans and retain failure ownership."""
import contextlib
import copy
import io
import json
import struct
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import make_ld
import source_data as D
import units_verify as V


class SourceDataRanges(unittest.TestCase):
    def unit(self, start=0x2000, end=0x2008, status='source'):
        return dict(name='owner', functions=[dict(addr=0x1000, symbol='body', status=status)],
                    data_ranges=[dict(section='.data', input='.data.owner', start=start, end=end)])

    def test_default_and_inactive_units_do_not_change_data_placement(self):
        self.assertEqual(D.source_ranges([dict(name='old', functions=[dict(status='source')])]), [])
        self.assertEqual(D.source_ranges([self.unit(status='asm')]), [])
        self.assertIsNone(D.carve_ranges('unchanged', '.data', 0x2000, 0x2010, []))

    def test_carving_preserves_symbolic_relocations_and_every_original_item(self):
        text = '.include "macro.inc"\n.section .data, "wa"\ndlabel D_00002000\n.word func_00001000\nenddlabel D_00002000\ndlabel D_00002008\n.word D_00002000\nenddlabel D_00002008\n'
        ranges = D.source_ranges([self.unit()])
        chunks = D.carve_ranges(text, '.data', 0x2000, 0x2010, ranges)
        self.assertEqual([(r['start'], r['end']) for r in chunks], [(0x2000, 0x2008), (0x2008, 0x2010)])
        self.assertIn('.word func_00001000', chunks[0]['text'])
        self.assertIn('.word D_00002000', chunks[1]['text'])
        self.assertNotIn('dlabel D_00002008', chunks[0]['text'])
        self.assertEqual(sum(r['text'].count('.word ') for r in chunks), 2)

    def test_boundary_inside_an_item_is_rejected(self):
        text = '.section .data\ndlabel D_00002000\n.word 0, 0, 0, 0\n'
        with self.assertRaisesRegex(ValueError, 'not an existing splat label'):
            D.carve_ranges(text, '.data', 0x2000, 0x2010, D.source_ranges([self.unit(end=0x2004)]))

    def unwind_fixture(self):
        # A synthetic version-1 CIE followed by one FDE and its group terminator.
        cie = struct.pack('<II', 16, 0) + bytes([1, 0, 1, 0x78, 0x40, 0x0c, 0x1d, 0, 9, 0x40, 0x1f, 0])
        return cie + struct.pack('<IIII', 12, 24, 0x1000, 4) + struct.pack('<I', 0)

    def test_only_complete_validated_unwind_groups_allow_new_split_labels(self):
        blob = self.unwind_fixture()
        groups = D.unwind_groups(blob, 0x2000, 0x1000, 0x1100)
        self.assertEqual(groups, {(0x2000, 0x2028): [(0x1000, 4)]})
        unit = self.unit(0x2000, 0x2028)
        unit['data_ranges'][0]['kind'] = 'unwind'
        lines = ['.include "macro.inc"', '.section .data, "wa"', 'dlabel D_00001FF0']
        lines += ['    /* %08X %08X 00000000 */ .word 0' % (a, a) for a in range(0x1ff0, 0x2030, 4)]
        lines += ['enddlabel D_00001FF0']
        chunks = D.carve_ranges('\n'.join(lines), '.data', 0x1ff0, 0x2030, D.source_ranges([unit]), groups)
        self.assertEqual([(r['start'], r['end']) for r in chunks], [(0x1ff0, 0x2000), (0x2000, 0x2028), (0x2028, 0x2030)])
        self.assertIn('dlabel D_00002000', chunks[1]['text'])
        self.assertIn('enddlabel D_00002000', chunks[1]['text'])
        self.assertIn('enddlabel D_00002028', chunks[2]['text'])

    def test_corrupt_backlink_or_text_extent_does_not_authorize_unwind_carving(self):
        blob = bytearray(self.unwind_fixture())
        struct.pack_into('<I', blob, 24, 28)
        self.assertEqual(D.unwind_groups(blob, 0x2000, 0x1000, 0x1100), {})
        self.assertEqual(D.unwind_groups(self.unwind_fixture(), 0x2000, 0x2000, 0x2100), {})
        unit = self.unit(0x2000, 0x2028)
        unit['data_ranges'][0]['kind'] = 'unwind'
        with self.assertRaisesRegex(ValueError, 'complete validated CIE/FDE group'):
            D.carve_ranges('dlabel D_00002000', '.data', 0x2000, 0x2040, D.source_ranges([unit]), {})

    def test_a_valid_group_does_not_authorize_an_interior_byte_cut(self):
        unit = self.unit(0x2000, 0x2024)
        unit['data_ranges'][0]['kind'] = 'unwind'
        with self.assertRaisesRegex(ValueError, 'complete validated CIE/FDE group'):
            D.carve_ranges('dlabel D_00002000', '.data', 0x2000, 0x2040, D.source_ranges([unit]),
                          D.unwind_groups(self.unwind_fixture(), 0x2000, 0x1000, 0x1100))

    def test_overlapping_owners_are_rejected(self):
        other = self.unit(0x2004, 0x2010)
        other['name'] = 'other'
        with self.assertRaisesRegex(ValueError, 'overlapping'):
            D.source_ranges([self.unit(), other])

    def constant_fixture(self):
        units = [dict(name='item%d' % i, addr=0x2000 + 8 * i, align=3,
                      lines=['item%d' % i]) for i in range(6)]
        runs = [dict(owner=None, head=0x2000, align=3, units=units[:2]),
                dict(owner=0x1000, head=0x2010, align=3, units=units[2:4]),
                dict(owner=None, head=0x2020, align=3, units=units[4:])]
        return runs, [u['addr'] for u in units]

    def constant_range(self, start=0x2008, end=0x2028):
        return dict(unit='owner', section='.rodata', input='.rodata', start=start, end=end)

    def test_explicit_rodata_keeps_every_item_and_both_shared_sides(self):
        runs, labels = self.constant_fixture()
        original = copy.deepcopy(runs)
        item = self.constant_range()
        result = D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030, [item], labels)
        self.assertEqual([(r['head'], r['owner']) for r in result],
                         [(0x2000, None), (0x2008, None), (0x2028, None)])
        self.assertEqual(result[1]['explicit_range'], item)
        self.assertEqual([u['name'] for r in result for u in r['units']],
                         [u['name'] for r in original for u in r['units']])
        self.assertEqual(runs, original)
        self.assertFalse(any(r['owner'] == 0x1000 for r in result))

    def test_explicit_rodata_rejects_partial_function_owned_runs(self):
        runs, labels = self.constant_fixture()
        for start, end in ((0x2010, 0x2018), (0x2018, 0x2028), (0x2018, 0x2020)):
            with self.assertRaisesRegex(ValueError, 'partial cut of a function-owned'):
                D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030,
                                          [self.constant_range(start, end)], labels)

    def test_rodata_partition_rejects_overlap_outside_and_interior_item_cuts(self):
        runs, labels = self.constant_fixture()
        cases = [([self.constant_range(0x1ff8, 0x2008)], 'outside'),
                 ([self.constant_range(0x2028, 0x2038)], 'outside'),
                 ([self.constant_range(0x2004, 0x2008)], 'existing object label'),
                 ([self.constant_range(0x2000, 0x2010),
                   self.constant_range(0x2008, 0x2020)], 'overlapping')]
        for ranges, message in cases:
            with self.assertRaisesRegex(ValueError, message):
                D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030, ranges, labels)

    def test_rodata_partition_preserves_untouched_owned_runs_and_default_behavior(self):
        runs, labels = self.constant_fixture()
        self.assertIs(D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030, [], labels), runs)
        result = D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030,
                                          [self.constant_range(0x2020, 0x2030)], labels)
        self.assertEqual(result[:2], runs[:2])
        self.assertEqual(result[2]['explicit_range']['end'], 0x2030)

    def test_rodata_cut_does_not_rephase_a_retained_input_alignment(self):
        runs, labels = self.constant_fixture()
        runs[0]['units'][1].update(addr=0x2004)
        labels[1] = 0x2004
        with self.assertRaisesRegex(ValueError, 'input alignment'):
            D.partition_constant_runs(runs, '.rodata', 0x2000, 0x2030,
                                      [self.constant_range(0x2004, 0x2028)], labels)

    def test_rodata_requires_exact_progbits_read_only_flags_and_size(self):
        unit = self.unit()
        unit['data_ranges'][0].update(section='.rodata', input='.rodata')
        ranges = D.source_ranges([unit])
        record = dict(type=1, size=8, align=8, flags=2)
        obj = SimpleNamespace(section=lambda _: record)
        placement = dict(sections={'.rodata': [dict(key=0x2000, end=0x2008),
                                              dict(key=0x2008, end=0x2010)]})
        self.assertIsNone(D.validate_inputs(obj, ranges, placement))
        for flags in (0, 1, 3, 4, 6, 7):
            record['flags'] = flags
            self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-flags')
        record.update(flags=2, type=8)
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-section')
        record.update(type=1, size=4)
        self.assertEqual(D.validate_inputs(obj, ranges, placement,
                         lambda *_: dict(type=8, size=8, align=8, flags=3)), 'data-size')

    def test_explicit_rodata_skips_only_inferred_constant_slot_validation(self):
        # Ordinary migration would accept just one smaller function slot. An
        # explicit input is validated by validate_inputs, never silently trimmed.
        unit = self.unit()
        unit['data_ranges'][0].update(section='.rodata', input='.rodata')
        live = [dict(addr=0x1000)]
        placement = dict(functions=[dict(name='body', addr=0x1000)], sections={
            '.rodata': [dict(key=0x2000, end=0x2008)], '.lit4': [], '.gcc_except_table': []})
        obj = SimpleNamespace(sections=[], section=lambda _: None)
        with patch.object(V, 'kept_text_names', return_value=set()):
            self.assertIsNone(V.data_sections(obj, [], unit, live, placement))
        bad = SimpleNamespace(section=lambda _: dict(type=1, size=4, align=4, flags=2))
        self.assertEqual(D.validate_inputs(bad, D.source_ranges([unit]), placement), 'data-size')

    def test_retained_fragment_alignment_phase_is_preserved_at_a_later_label(self):
        text = '.include "macro.inc"\n.section .data, "wa"\ndlabel D_00001FF0\n.space 0x14\nenddlabel D_00001FF0\ndlabel D_00002004\n.word 0\nenddlabel D_00002004\n\n.align 3\ndlabel D_00002008\n.word 0, 0\nenddlabel D_00002008\n'
        chunks = D.carve_ranges(text, '.data', 0x1ff0, 0x2010,
                                D.source_ranges([self.unit(0x1ff0, 0x2004)]))
        self.assertEqual([(r['start'], r['end']) for r in chunks],
                          [(0x1ff0, 0x2004), (0x2004, 0x2008), (0x2008, 0x2010)])
        self.assertNotIn('.align 3', chunks[1]['text'])
        self.assertIn('.align 3\ndlabel D_00002008', chunks[2]['text'])

    def test_implicit_wide_directive_alignment_uses_its_existing_label(self):
        text = '.section .data\ndlabel D_00001FF0\n.space 0x14\nenddlabel D_00001FF0\ndlabel D_00002004\n    /* 00002004 00002004 */ .word 0\nenddlabel D_00002004\ndlabel D_00002008\n    /* 00002008 00002008 */ .double 1.0\nenddlabel D_00002008\n'
        chunks = D.carve_ranges(text, '.data', 0x1ff0, 0x2010,
                                D.source_ranges([self.unit(0x1ff0, 0x2004)]))
        self.assertEqual([(r['start'], r['end']) for r in chunks],
                          [(0x1ff0, 0x2004), (0x2004, 0x2008), (0x2008, 0x2010)])
        self.assertNotIn('.double', chunks[1]['text'])

    def test_original_interior_labels_become_section_relative_aliases(self):
        result = make_ld.explicit_data_aliases(D.source_ranges([self.unit()]),
                                               [(0x2000, 'D_00002000'), (0x2004, 'D_00002004'), (0x2008, 'D_00002008')],
                                               dict(sections=[dict(name='.data', addr=0x1ff0)]))
        self.assertEqual(result, ['PROVIDE(D_00002000 = ADDR(.data) + 0x10);',
                                  'PROVIDE(D_00002004 = ADDR(.data) + 0x14);'])

    def test_input_must_fill_exactly_one_carved_range_with_correct_section_kind(self):
        ranges = D.source_ranges([self.unit()])
        placement = dict(sections={'.data': [dict(key=0x2000, end=0x2008)]})
        class Object:
            record = dict(type=1, size=8, align=8, flags=3)
            def section(self, name): return self.record
        obj = Object()
        self.assertIsNone(D.validate_inputs(obj, ranges, placement))
        obj.record = dict(type=1, size=4, align=4, flags=3)
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-size')
        obj.record = dict(type=8, size=8, align=8, flags=3)
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-section')
        obj.record = dict(type=1, size=8, align=0x4000, flags=3)
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-align')
        obj.record = None
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-section')
        self.assertEqual(D.validate_inputs(obj, ranges, dict(sections={})), 'data-layout')

    def storage_symbols(self, scalar_offset, arena_offset):
        return SimpleNamespace(
            sections=[dict(name=''),dict(name='.bss'),dict(name='.data')],
            symbols=lambda: [
                dict(name='counter',bind=1,shndx=1,value=scalar_offset),
                dict(name='arena',bind=1,shndx=1,value=arena_offset),
                dict(name='external',bind=1,shndx=0,value=0),
                dict(name='local',bind=0,shndx=1,value=0),
                dict(name='other_input',bind=1,shndx=2,value=0)])

    def test_correct_size_does_not_hide_reversed_storage_symbol_offsets(self):
        ranges=[dict(input='.bss',start=0x2000,end=0x2120)]
        expected=dict(counter=0x2110,arena=0x2000)
        self.assertEqual(D.validate_input_symbols(self.storage_symbols(0,16),ranges,expected),'data-symbol')

    def test_native_storage_symbol_offsets_and_undefined_aliases_are_accepted(self):
        ranges=[dict(input='.bss',start=0x2000,end=0x2120)]
        expected=dict(counter=0x2110,arena=0x2000,external=0x2050,local=0x2070,other_input=0x2090)
        self.assertIsNone(D.validate_input_symbols(self.storage_symbols(0x110,0),ranges,expected))

    def test_unknown_source_names_do_not_invent_original_data_addresses(self):
        self.assertIsNone(D.validate_input_symbols(self.storage_symbols(0,16),
                          [dict(input='.bss',start=0x2000,end=0x2120)],{}))

    def test_initialized_storage_cannot_replace_nobits_bss(self):
        unit = self.unit()
        unit['data_ranges'][0].update(section='.bss', input='.bss.owner')
        class Object:
            def section(self, name): return dict(type=1, size=8, align=8, flags=3)
        self.assertEqual(D.validate_inputs(Object(), D.source_ranges([unit]),
                         dict(sections={'.bss': [dict(key=0x2000, end=0x2008)]})), 'data-section')

    def nobits_fixture(self):
        unit = self.unit(0x2000, 0x2028)
        unit['data_ranges'][0].update(section='.bss', input='.bss.owner')
        record = dict(type=8, size=36, align=8, flags=3)
        obj = SimpleNamespace(section=lambda name: record)
        placement = dict(sections={'.bss': [dict(key=0x2000, end=0x2028),
                                           dict(key=0x2028, end=0x2050)]})
        following = dict(type=8, size=36, align=8, flags=3)
        return D.source_ranges([unit]), obj, record, placement, following

    def test_const_initialized_input_keeps_output_permission_verification(self):
        unit = self.unit()
        record = dict(type=1, size=8, align=8, flags=2)
        obj = SimpleNamespace(section=lambda name: record)
        placement = dict(sections={'.data': [dict(key=0x2000, end=0x2008)]})
        ranges = D.source_ranges([unit])
        self.assertIsNone(D.validate_inputs(obj, ranges, placement))
        record['flags'] = 3
        self.assertIsNone(D.validate_inputs(obj, ranges, placement))
        for flags in (0, 1, 4, 6, 7):
            record['flags'] = flags
            self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-flags')
        # Uninitialized storage must remain writable even though both are allocated.
        record.update(type=8, flags=2)
        ranges[0].update(section='.bss', input='.bss.owner')
        placement['sections']['.bss'] = placement['sections'].pop('.data')
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-flags')

    def test_nobits_tail_requires_the_immediately_following_actual_input(self):
        ranges, obj, record, placement, following = self.nobits_fixture()
        self.assertEqual(D.validate_inputs(obj, ranges, placement), 'data-size')
        evidence = lambda section, address: following if (section, address) == ('.bss', 0x2028) else None
        self.assertIsNone(D.validate_inputs(obj, ranges, placement, evidence))
        for alignment in (None, 1, 2, 4, 0, 3, 32):
            following['align'] = alignment
            self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')
        following['align'] = 8
        placement['sections']['.bss'][1]['key'] = 0x2030
        self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')
        placement['sections']['.bss'].pop()
        self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')

    def test_nobits_tail_rejects_wrong_kind_unknown_empty_and_large_gap(self):
        ranges, obj, record, placement, following = self.nobits_fixture()
        evidence = lambda section, address: following
        for change in (dict(type=1), dict(size=0), dict(flags=1), dict(flags=7)):
            bad = dict(following, **change)
            self.assertEqual(D.validate_inputs(obj, ranges, placement, lambda *_: bad), 'data-size')
        self.assertEqual(D.validate_inputs(obj, ranges, placement, lambda *_: None), 'data-size')
        record['size'] = 0
        self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')
        record['size'] = 36
        # Twenty bytes of real rounding still exceed the existing alignment policy.
        ranges[0].update(start=0x2008, end=0x2040)
        placement['sections']['.bss'][0].update(key=0x2008, end=0x2040)
        placement['sections']['.bss'][1]['key'] = 0x2040
        following['align'] = 64
        self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')
        # Initialized data retains the existing complete-input requirement.
        ranges[0].update(section='.data', input='.data.owner', start=0x2000, end=0x2028)
        placement['sections']['.data'] = [dict(key=0x2000, end=0x2028), dict(key=0x2028, end=0x2050)]
        record['type'] = 1
        following.update(type=1, align=8)
        self.assertEqual(D.validate_inputs(obj, ranges, placement, evidence), 'data-size')

    def test_sbss_uses_the_same_native_kind_and_alignment_requirements(self):
        ranges, obj, record, placement, following = self.nobits_fixture()
        ranges[0].update(section='.sbss', input='.sbss.owner')
        placement['sections']['.sbss'] = placement['sections'].pop('.bss')
        self.assertIsNone(D.validate_inputs(obj, ranges, placement, lambda *_: following))
        record['flags'] = 7
        self.assertEqual(D.validate_inputs(obj, ranges, placement, lambda *_: following), 'data-flags')

    def test_prepare_passes_native_nobits_evidence_and_still_checks_later_text_gaps(self):
        unit = self.unit(0x2000, 0x2008)
        unit['data_ranges'][0].update(section='.bss', input='.bss.owner')
        other = dict(name='later', functions=[dict(addr=0x1008, symbol='later_body', status='source', size=4)])
        unit['functions'][0]['size'] = 4
        sections = dict.fromkeys(('.rodata', '.lit4', '.gcc_except_table'), [])
        sections['.bss'] = [dict(key=0x2000, end=0x2008), dict(key=0x2008, end=0x2010)]
        placement = dict(sections=sections, functions=[dict(addr=0x1000, end=0x1004, name='body'),
                                                      dict(addr=0x1008, end=0x1010, name='later_body')])
        def native_object(symbol, owned=False):
            text = dict(name='.text', index=1, type=1, size=4, align=4)
            bss = dict(name='.bss.owner', index=2, type=8, size=4, align=4, flags=3)
            records = [dict(type=0, name=''), text] + ([bss] if owned else [])
            return SimpleNamespace(sections=records, content=lambda _: b'',
                section=lambda name: next((s for s in records if s.get('name') == name), None),
                symbols=lambda: [dict(name=symbol, type=2, bind=1, shndx=1, value=0, size=4)])
        inputs = SimpleNamespace(data_section=lambda sec, addr: dict(type=8, size=4, align=8, flags=3),
                                 at=lambda address: 8)
        original = SimpleNamespace(section=lambda name: dict(addr=0x1000), content=lambda _: bytes(16))
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory); build = root / 'build'; build.mkdir()
            (root/'orig/SLUS_213.76').mkdir(parents=True)
            (root/'orig/SLUS_213.76/SLUS_213.76').write_bytes(b'authored ELF fixture')
            (build/'placement.json').write_text(json.dumps(placement))
            (build/'labels.json').write_text('[]')
            with patch.object(V, 'ROOT', root), patch.object(V, 'BUILD', build), \
                    patch.object(V, 'load_units', return_value=[unit, other]), \
                    patch.object(V, 'cached_object', side_effect=lambda name: native_object('body', True)
                                 if name == 'owner' else native_object('later_body')), \
                    patch.object(V, 'Elf', return_value=original), \
                    patch('text_placement.InputAlignments', return_value=inputs), \
                    patch.object(V, 'save') as save, contextlib.redirect_stdout(io.StringIO()):
                V.prepare()
            self.assertTrue(all(f['status'] == 'source' for u in save.call_args[0][0] for f in u['functions']))

    def test_actual_nobits_inputs_resolve_source_and_retained_objects(self):
        from text_placement import InputAlignments
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory); (root/'object.o').write_bytes(b'authored ELF fixture')
            (root/'objects_cache.json').write_text(json.dumps({'units/next': 'object.o', 'data/remainder': 'object.o'}))
            source = dict(name='units/next', rename={'.bss': '.bss.00002028'})
            (root/'objects.json').write_text(json.dumps([source, dict(name='data/remainder')]))
            (root/'placement.json').write_text(json.dumps(dict(sections={'.bss': [
                dict(obj='data/remainder', sec='.bss', key=0x2050)]})))
            record = dict(type=8, size=36, align=8, flags=3)
            with patch('text_placement.Elf', return_value=SimpleNamespace(section=lambda _: record)):
                inputs = InputAlignments(root)
                self.assertEqual(inputs.data_section('.bss', 0x2028), record)
                self.assertEqual(inputs.data_section('.bss', 0x2050), record)
                self.assertIsNone(inputs.data_section('.bss', 0x2040))
                (root/'objects.json').write_text(json.dumps([source, source]))
                self.assertIsNone(InputAlignments(root).data_section('.bss', 0x2028))

    def test_data_byte_failure_demotes_its_owner_instead_of_an_unrelated_function(self):
        class Object:
            def __init__(self, changed): self.changed = changed
            def section(self, name): return dict(name=name, addr=0x2000 if name == '.data' else 0x1000)
            def content(self, section):
                return (b'\0\0\0\0' + (b'\1' if self.changed else b'\0') + b'\0\0\0') if section['name'] == '.data' else b''
        unit = self.unit()
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory); build = root / 'build'; build.mkdir()
            (root/'orig/SLUS_213.76').mkdir(parents=True)
            (root/'orig/SLUS_213.76/SLUS_213.76').write_bytes(b'original')
            (build/'linked.elf').write_bytes(b'changed')
            (build/'placement.json').write_text(json.dumps(dict(functions=[dict(addr=0x1000, name='body')],
                 sections={sec: [] for sec in ('.rodata', '.lit4', '.gcc_except_table')})))
            with patch.object(V, 'ROOT', root), patch.object(V, 'BUILD', build), \
                 patch.object(V, 'Elf', side_effect=[Object(False), Object(True)]), \
                 patch.object(V, 'load_units', return_value=[unit]), patch.object(V, 'save') as save, \
                 patch.object(sys, 'argv', ['units_verify.py', 'compare', '--fix']), contextlib.redirect_stdout(io.StringIO()):
                V.compare()
            self.assertEqual(save.call_args[0][0][0]['functions'][0]['status'], 'asm')
            self.assertEqual(save.call_args[0][0][0]['functions'][0]['reason'], 'bytes')

    def test_missing_interior_data_label_is_attributed_to_data_owner(self):
        unit = self.unit()
        with tempfile.TemporaryDirectory() as directory:
            build = Path(directory)
            (build/'link.log').write_text("obj/data/remainder.o: undefined reference to `D_00002004'\n")
            (build/'placement.json').write_text(json.dumps(dict(functions=[dict(addr=0x1000, name='body')],
                 sections={sec: [] for sec in ('.rodata', '.lit4', '.gcc_except_table')})))
            with patch.object(V, 'BUILD', build), patch.object(V, 'load_units', return_value=[unit]), \
                 patch.object(V, 'save') as save, contextlib.redirect_stdout(io.StringIO()):
                V.link_errors()
            self.assertEqual(save.call_args[0][0][0]['functions'][0]['reason'], 'labels')


if __name__ == '__main__':
    unittest.main()
