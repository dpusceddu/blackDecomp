"""Every function belongs to exactly one file and the split ranges do not overlap (tools/build/splits.py, ownership.py)."""
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import include_asm
import ownership
import splits as S
import split_function
import tu_files
import units as U

TABLE = [(0x100000, 0x100010), (0x100010, 0x100020), (0x100020, 0x100030), (0x100030, 0x100040), (0x100040, 0x100050)]


def marker(address):
    return 'INCLUDE_ASM("asm/x", func_%08X);\n' % address


def splits(*entries):
    return [S.Split(dict(e), {}) for e in entries]


class Check(unittest.TestCase):
    def problems(self, entries, files, **kw):
        return S.check_ownership(splits(*entries), read=lambda p: files[p], **kw)

    def test_a_clean_list_has_no_problems(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100020]}, {'src': 'b.c', 'range': [0x100020, 0x100050]}]
        files = {'a.c': marker(0x100000) + marker(0x100010), 'b.c': marker(0x100020)}
        self.assertEqual([], self.problems(entries, files, table=TABLE, complete=True))

    def test_overlapping_ranges_are_reported(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100030]}, {'src': 'b.c', 'range': [0x100020, 0x100050]}]
        found = self.problems(entries, {'a.c': '', 'b.c': ''})
        self.assertEqual(1, len(found))
        self.assertIn('overlap', found[0])

    def test_a_marker_for_a_function_of_another_file_is_reported(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100020]}, {'src': 'b.c', 'range': [0x100020, 0x100050]}]
        found = self.problems(entries, {'a.c': marker(0x100000) + marker(0x100020), 'b.c': ''})
        self.assertEqual(1, len(found))
        self.assertIn('a.c:2: func_00100020 is not in the file', found[0])

    def test_a_marker_twice_in_a_file_is_reported(self):
        found = self.problems([{'src': 'a.c', 'range': [0x100000, 0x100020]}], {'a.c': marker(0x100000) * 2})
        self.assertIn('marked twice', found[0])

    def test_a_marker_that_is_not_a_function_start_is_reported_with_the_table(self):
        found = self.problems([{'src': 'a.c', 'range': [0x100000, 0x100020]}], {'a.c': marker(0x100004)}, table=TABLE)
        self.assertIn('not a function start', found[0])

    def test_complete_demands_an_owner_for_every_function(self):
        found = self.problems([{'src': 'a.c', 'range': [0x100000, 0x100020]}], {'a.c': ''}, table=TABLE, complete=True)
        self.assertEqual(['func_00100020 belongs to no file', 'func_00100030 belongs to no file', 'func_00100040 belongs to no file'], found)

    def test_no_overlap_is_accepted_not_even_one_byte_or_inside_one_file_or_a_nested_entry(self):
        for entries in (
                [{'src': 'a.c', 'range': [0x100000, 0x100021]}, {'src': 'b.c', 'range': [0x100020, 0x100050]}],   # one byte
                [{'src': 'a.c', 'range': [0x100000, 0x100030]}, {'src': 'a.c', 'range': [0x100010, 0x100040]}],   # same file
                [{'src': 'a.c', 'range': [0x100000, 0x100050]}, {'src': 'b.c', 'range': [0x100010, 0x100020]},   # nested
                 {'src': 'c.c', 'range': [0x100030, 0x100040]}]):
            found = self.problems(entries, {'a.c': '', 'b.c': '', 'c.c': ''})
            self.assertTrue(found and all('overlap' in p for p in found), entries)

    def test_adjacent_entries_and_a_file_with_separate_stretches_are_not_overlaps(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100010]}, {'src': 'b.c', 'range': [0x100010, 0x100030]},
                   {'src': 'a.c', 'range': [0x100030, 0x100050]}]
        self.assertEqual([], self.problems(entries, {'a.c': '', 'b.c': ''}))

    def test_a_functions_key_is_no_longer_accepted(self):
        with self.assertRaisesRegex(ValueError, 'unknown keys functions'):
            splits({'src': 'a.c', 'range': [0x100000, 0x100030], 'functions': [0x100000]})

    def test_the_committed_split_list_has_no_ownership_problems(self):
        # sources only, no game files: ranges and markers
        self.assertEqual([], S.check_ownership(S.load_splits()))


class Groups(unittest.TestCase):
    def test_later_entries_of_a_file_are_continuations_of_the_first(self):
        group, = S.group_splits(splits({'src': 'a.c', 'range': [0x100000, 0x100010], 'flags': ['-O1']},
                                       {'src': 'a.c', 'range': [0x100030, 0x100040], 'note': 'second stretch'}))
        self.assertEqual(2, len(group))
        with self.assertRaisesRegex(ValueError, 'may only have src, range and note'):
            S.group_splits(splits({'src': 'a.c', 'range': [0x100000, 0x100010]}, {'src': 'a.c', 'range': [0x100030, 0x100040], 'flags': ['-O1']}))

    def test_a_file_with_several_ranges_is_one_unit_that_leaves_the_functions_between_as_assembly(self):
        entries = splits({'src': 'a.c', 'range': [0x100000, 0x100010]}, {'src': 'b.c', 'range': [0x100010, 0x100030]},
                         {'src': 'a.c', 'range': [0x100030, 0x100050]})
        files = {'a.c': marker(0x100030) + 'void Own(void) {}\n', 'b.c': marker(0x100010) + marker(0x100020)}
        units = U.derive_units(entries, TABLE, S.Symbols(), read=lambda p: files[p])
        a, b = units
        self.assertEqual(('a.c', [0x100000, 0x100050], [[0x100000, 0x100010], [0x100030, 0x100050]]), (a['source'], a['range'], a['ranges']))
        status = {f['addr']: f['status'] for f in a['functions']}
        self.assertEqual({0x100000: 'source', 0x100010: 'asm', 0x100020: 'asm', 0x100030: 'asm', 0x100040: 'source'}, status)
        self.assertEqual({0x100010: 'asm', 0x100020: 'asm'}, {f['addr']: f['status'] for f in b['functions']})

    def test_a_marker_for_a_foreign_function_makes_the_units_fail(self):
        entries = splits({'src': 'a.c', 'range': [0x100000, 0x100020]}, {'src': 'b.c', 'range': [0x100020, 0x100050]})
        with self.assertRaisesRegex(ValueError, 'is not in the file'):
            U.derive_units(entries, TABLE, S.Symbols(), read=lambda p: marker(0x100020))


class NoSplitList(unittest.TestCase):
    def test_a_version_without_a_split_list_needs_no_owner(self):
        self.assertEqual([], U.derive_units([], TABLE, S.Symbols(), complete=True))


class MovingAFunction(unittest.TestCase):
    def test_carving_the_middle_of_the_first_entry_keeps_the_options_on_the_left_piece(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100050], 'flags': ['-O1', '-G0'], 'note': 'n'}]
        out, options = S.carve_range(entries, 0x100020, 0x100030)
        self.assertIsNone(options)
        self.assertEqual([{'src': 'a.c', 'range': [0x100000, 0x100020], 'flags': ['-O1', '-G0'], 'note': 'n'},
                          {'src': 'a.c', 'range': [0x100030, 0x100050]}], out)

    def test_carving_the_whole_first_entry_hands_the_options_to_the_next_one_or_reports_them(self):
        first = {'src': 'a.c', 'range': [0x100000, 0x100010], 'flags': ['-O1']}
        second = {'src': 'a.c', 'range': [0x100030, 0x100040]}
        out, options = S.carve_range([first, second], 0x100000, 0x100010)
        self.assertEqual([{'src': 'a.c', 'range': [0x100030, 0x100040], 'flags': ['-O1']}], out)
        self.assertIsNone(options)
        out, options = S.carve_range([dict(first)], 0x100000, 0x100010)
        self.assertEqual(([], {'flags': ['-O1']}), (out, options))

    def test_adopting_extends_a_neighbour_or_adds_a_continuation(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100020], 'flags': ['-O1']}]
        self.assertEqual([0x100000, 0x100030], S.adopt_range(entries, 'a.c', 0x100020, 0x100030)[0]['range'])
        out = S.adopt_range([{'src': 'a.c', 'range': [0x100000, 0x100010], 'flags': ['-O1']}], 'a.c', 0x100030, 0x100040)
        self.assertEqual({'src': 'a.c', 'range': [0x100030, 0x100040]}, out[1])
        out = S.adopt_range([{'src': 'a.c', 'range': [0x100030, 0x100040], 'flags': ['-O1']}], 'a.c', 0x100000, 0x100010)
        self.assertEqual([{'src': 'a.c', 'range': [0x100030, 0x100040]}, {'src': 'a.c', 'range': [0x100000, 0x100010], 'flags': ['-O1']}], out)

    def test_marker_removal_and_insertion_keep_address_order(self):
        text = marker(0x100000) + '#ifdef NON_MATCHING\nint func_00100010(void) { return 1; }\n#else\n' + marker(0x100010) + '#endif\n' + marker(0x100030)
        self.assertEqual(marker(0x100000) + marker(0x100030), include_asm.remove(text, 'func_00100010'))
        again = include_asm.insert(marker(0x100000) + marker(0x100030), 'func_00100010', 'asm/x')
        self.assertEqual(marker(0x100000) + marker(0x100010) + marker(0x100030), again)
        self.assertTrue(include_asm.insert(marker(0x100000), 'func_00100040', 'asm/x').endswith(marker(0x100040)))

    def test_a_file_made_for_a_function_takes_it_over_and_gives_it_back_on_revert(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / 'config/SLUS_213.76').mkdir(parents=True)
            (root / 'build/SLUS_213.76').mkdir(parents=True)
            (root / 'src/game').mkdir(parents=True)
            split_list = root / 'config/SLUS_213.76/splits.yaml'
            start = 'variant: SLUS_213.76\nsplits:\n'
            split_list.write_text(start + '  - {src: src/game/a.c, range: [0x100000, 0x100050], flags: [-O1, -G0]}\n')
            a = root / 'src/game/a.c'
            body = ''.join(marker(x) for x, _ in TABLE)
            a.write_text(body.replace('asm/x', tu_files.ASM_DIR))
            (root / 'build/SLUS_213.76/functions.json').write_text('[%s]' % ','.join('[%d,%d]' % t for t in TABLE))
            saved = (S.ROOT, T_ROOT := tu_files.ROOT, U.ROOT)
            try:
                S.ROOT = tu_files.ROOT = U.ROOT = root
                released = tu_files.release_function(0x100020)
                self.assertNotIn('func_00100020', a.read_text())
                left = S.load_splits(path=split_list)
                self.assertEqual([[0x100000, 0x100020], [0x100030, 0x100050]], [[s.start, s.end] for s in left])
                self.assertEqual([], S.check_ownership(left, read=lambda p: (root / p).read_text()))
                tu_files.restore_function(0x100020, released)
                self.assertEqual(body.replace('asm/x', tu_files.ASM_DIR), a.read_text())
                again = S.load_splits(path=split_list)
                self.assertEqual([[0x100000, 0x100050]], [[s.start, s.end] for s in again])
                self.assertEqual(['-O1', '-G0'], again[0].flags)
            finally:
                S.ROOT, tu_files.ROOT, U.ROOT = saved


class SplitFunction(unittest.TestCase):
    def setUp(self):
        self.dir = tempfile.TemporaryDirectory()
        self.addCleanup(self.dir.cleanup)
        self.root = root = Path(self.dir.name)
        (root / 'config/SLUS_213.76').mkdir(parents=True)
        (root / 'build/SLUS_213.76').mkdir(parents=True)
        (root / 'src/game/unsorted').mkdir(parents=True)
        (root / 'config/SLUS_213.76/splits.yaml').write_text(
            'variant: SLUS_213.76\nsplits:\n  - {src: src/game/unsorted/tu_100000.c, range: [0x100000, 0x100050]}\n')
        self.old = root / 'src/game/unsorted/tu_100000.c'
        self.old.write_text('#include "include_asm.h"\n' + ''.join(marker(x).replace('asm/x', tu_files.ASM_DIR) for x, _ in TABLE))
        (root / 'build/SLUS_213.76/functions.json').write_text('[%s]' % ','.join('[%d,%d]' % t for t in TABLE))
        self.saved = (S.ROOT, tu_files.ROOT, U.ROOT, split_function.ROOT)
        S.ROOT = tu_files.ROOT = U.ROOT = split_function.ROOT = root
        self.addCleanup(lambda: (setattr(S, 'ROOT', self.saved[0]), setattr(tu_files, 'ROOT', self.saved[1]),
                                 setattr(U, 'ROOT', self.saved[2]), setattr(split_function, 'ROOT', self.saved[3])))

    def test_the_function_gets_a_file_of_its_own_and_the_old_file_keeps_the_rest(self):
        with patch.object(tu_files, 'unique_path', return_value='src/game/unsorted/tu_100000_100020.c'):
            new, old = split_function.split_function(0x100020, flags=['-O1', '-G0', '-snas'])
        self.assertEqual(('src/game/unsorted/tu_100000_100020.c', 'src/game/unsorted/tu_100000.c'), (new, old))
        self.assertNotIn('func_00100020', self.old.read_text())
        self.assertEqual(4, self.old.read_text().count('INCLUDE_ASM('))
        self.assertIn('func_00100020', (self.root / new).read_text())
        splits = S.load_splits(path=self.root / 'config/SLUS_213.76/splits.yaml')
        self.assertEqual([('src/game/unsorted/tu_100000.c', 0x100000, 0x100020, False), ('src/game/unsorted/tu_100000_100020.c', 0x100020, 0x100030, True),
                          ('src/game/unsorted/tu_100000.c', 0x100030, 0x100050, False)],
                         [(s.src, s.start, s.end, s.flags == ['-O1', '-G0', '-snas']) for s in splits])
        self.assertEqual([], S.check_ownership(splits, read=lambda p: (self.root / p).read_text(), table=TABLE, complete=True))

    def test_a_recovered_function_or_an_unknown_one_is_refused(self):
        self.old.write_text(self.old.read_text().replace(marker(0x100020).replace('asm/x', tu_files.ASM_DIR), 'void func_00100020(void) {}\n'))
        with self.assertRaisesRegex(SystemExit, 'only plain INCLUDE_ASM functions'):
            split_function.split_function(0x100020)
        with self.assertRaisesRegex(SystemExit, 'no file owns it'):
            split_function.split_function(0x200000)


class WhereIsIt(unittest.TestCase):
    TEXT = ('#include "include_asm.h"\nINCLUDE_ASM("asm/x", func_00100000);\nint Game::Tick(void) {\n  return 1;\n}\n'
            '#ifdef NON_MATCHING\nint func_00100030(void) { return 2; }\n#else\nINCLUDE_ASM("asm/x", func_00100030);\n#endif\n')

    def test_mangled_names_have_a_source_spelling(self):
        self.assertEqual(['Tick__4Game', 'Game::Tick'], ownership.source_names('Tick__4Game'))
        self.assertEqual(['__4Game', 'Game::Game'], ownership.source_names('__4Game'))
        self.assertEqual(['_$_4Game', 'Game::~Game'], ownership.source_names('_$_4Game'))
        self.assertEqual(['Reset__Q24Kaim6CBrainv', 'CBrain::Reset'], ownership.source_names('Reset__Q24Kaim6CBrainv'))
        self.assertEqual(['func_00100000'], ownership.source_names('func_00100000'))

    def test_assembly_draft_and_source_are_told_apart(self):
        self.assertEqual(('assembly', 2), ownership.locate_in_text(self.TEXT, 0x100000, []))
        self.assertEqual(('draft', 9), ownership.locate_in_text(self.TEXT, 0x100030, []))
        self.assertEqual(('source', 3), ownership.locate_in_text(self.TEXT, 0x100010, ['Tick__4Game', 'Game::Tick']))
        self.assertEqual((None, None), ownership.locate_in_text(self.TEXT, 0x100040, []))

    def test_the_owner_is_the_entry_whose_range_contains_the_address(self):
        a, b = splits({'src': 'a.c', 'range': [0x100020, 0x100040]}, {'src': 'b.c', 'range': [0x100000, 0x100020]})
        self.assertEqual('a.c', ownership.owner_entry(0x100020, [a, b]).src)
        self.assertEqual('b.c', ownership.owner_entry(0x10001c, [a, b]).src)
        self.assertIsNone(ownership.owner_entry(0x100040, [a, b]))


if __name__ == '__main__':
    unittest.main()
