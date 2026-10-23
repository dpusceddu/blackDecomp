"""Synthetic loop and catalog-recipe checks; no game input or SDK execution."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools' / 'studies'))
import assembler
import autodecomp
import compile as standalone
from loop_padding import (branch_offset, loops, padding_equivalent, candidate_padding,
                          classify_short_loops, instruction_features, summarize_classification)


def branch(displacement):
    return 0x14800000 | displacement & 65535


class LoopDiagnostics(unittest.TestCase):
    def test_regimm_traps_are_not_backward_branches(self):
        self.assertIsNone(branch_offset(0x0488ffff))

    def test_displacement_and_delay_slot_are_distinct(self):
        tokens = [(0x24840001, None)] * 3 + [(0, None), (branch(-5), None), (0x24a50001, None)]
        loop, = loops(tokens)
        self.assertEqual(loop['words_including_delay'], 6)
        self.assertEqual(loop['nops_before_branch'], 1)
        self.assertFalse(loop['delay_nop'])

    def test_comparison_relocates_edges_but_never_changes_input(self):
        original = [(0x24840001, None), (branch(-2), None), (0x24a50001, None)]
        padded = [original[0], (0, None), (branch(-3), None), original[2]]
        snapshot = list(padded)
        self.assertTrue(padding_equivalent(original, padded, lambda _: None))
        self.assertEqual(padded, snapshot)

    def test_useful_delay_slot_moved_outside_loop_is_not_padding(self):
        original = [(0x24840001, None), (branch(-2), None), (0x24a50001, None)]
        changed = [original[0], (branch(-2), None), (0, None), original[2]]
        self.assertFalse(padding_equivalent(original, changed, lambda _: None))

    def test_distinct_globals_with_the_same_value_are_not_padding(self):
        a = [(0x8c820000, ('lo', 0x400000))]
        b = [(0x8c820000, ('lo', 0x400004))]
        self.assertFalse(padding_equivalent(a, b, lambda _: '00000000'))


class LoopClassification(unittest.TestCase):
    def tu(self, compiler='ee-gcc2.95.3-136', stop=0x1100):
        return dict(name='test', text=['0x1000', hex(stop)], compiler=compiler,
                    confidence='medium', flags_basis='synthetic', library='test', flags=['-O2'])

    def test_prior_controls_own_their_delay_slot_nops(self):
        words = [0x08000000, 0, 0, branch(-4), 0]
        self.assertEqual(candidate_padding(words, 0, 3), 1)
        row, = classify_short_loops(words, 0x1000, [self.tu()])
        self.assertEqual(row['padding_nops'], 1)
        self.assertTrue(row['other_branch'])
        self.assertEqual(row['delay_op'], 'nop')

    def test_instruction_families_include_ee_and_fpu_operations(self):
        features = instruction_features([0x8c820000, 0xac820004, 0x00850018, 0x46000000, 0x48420800])
        for name in ('load', 'store', 'multdiv', 'cop1', 'cop2'):
            self.assertTrue(features[name], name)
        self.assertFalse(features['call'])

    def test_matching_recipe_overrides_inferred_compiler_without_erasing_basis(self):
        words = [0x24840001, branch(-2), 0]
        function = dict(addr=0x1000, size=12, span=12, region='test')
        unit = dict(name='matched', compiler='ee-gcc2.9-991111-01', flags=['-O2', '-G0'],
                    functions=[dict(addr=0x1000, status='source')])
        row, = classify_short_loops(words, 0x1000, [self.tu()], [function], [unit])
        self.assertEqual(row['compiler'], 'ee-gcc2.9-991111-01')
        self.assertEqual(row['compiler_basis'], 'matching-source-recipe')
        self.assertEqual(row['tu_compiler'], 'ee-gcc2.95.3-136')
        self.assertEqual(row['tu_confidence'], 'medium')
        self.assertFalse(row['sn'])

    def test_sony_library_assignment_is_not_reclassified_by_trivial_sn_match(self):
        function = dict(addr=0x1000, size=12)
        unit = dict(name='matched', compiler='ee-gcc2.95.3-136', flags=['-O2'],
                    functions=[dict(addr=0x1000, status='source')])
        row, = classify_short_loops([1, branch(-2), 0], 0x1000,
                                   [self.tu('ee-gcc2.9-991111-01')], [function], [unit])
        self.assertFalse(row['sn'])

    def test_identical_body_counterexamples_preserve_delay_instruction(self):
        first = [0x00041082] + [0] * 3 + [branch(-5), 0x24840001]
        second = [0x00041082] + [0] * 4 + [branch(-6), 0x24840001]
        rows = classify_short_loops(first + second, 0x1000, [self.tu()])
        result = summarize_classification(rows)
        self.assertEqual(result['summary']['sn']['branches'], 2)
        example, = result['content_counterexamples']
        self.assertEqual({r['length'] for r in example['branches']}, {6, 7})
        second[-1] = 0
        changed = summarize_classification(classify_short_loops(first + second, 0x1000, [self.tu()]))
        self.assertEqual(changed['content_counterexamples'], [])

    def test_short_branches_crossing_function_boundaries_are_still_classified(self):
        rows = classify_short_loops([0x24840001, branch(-2), 0], 0x1000, [self.tu()],
                                    [dict(addr=0x1004, size=8)])
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0]['target'], '0x1000')
        self.assertEqual(rows[0]['function'], '0x1004')

    def test_branch_likely_and_its_load_delay_slot_are_recorded(self):
        words = (0x24840001, 0x5480fffe, 0x8ca60000)
        row, = classify_short_loops(words, 0x1000, [self.tu()])
        self.assertTrue(row['likely'])
        self.assertEqual(row['delay_op'], 'lw')
        self.assertTrue(row['load'])
        self.assertFalse(row['body_features']['load'])

    def test_census_includes_six_negative_offsets_but_excludes_longer_loops(self):
        words = []
        for d in range(1, 8):
            words.extend([0x24840001] * (d - 1) + [branch(-d), 0])
        rows = classify_short_loops(words, 0x1000, [self.tu()])
        self.assertEqual({r['displacement'] for r in rows}, {-1, -2, -3, -4, -5, -6})


class AssemblerRecipes(unittest.TestCase):
    def test_standalone_output_before_input_does_not_read_existing_object_as_source(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            source = root / 'input.c'
            source.write_text('int f(void) { return 0; }')
            output = root / 'build/output.o'
            output.parent.mkdir()
            output.write_bytes(b'old object')
            args = ['compile.py', 'ee-gcc2.95.3-136', '--assembler=sn-2.73a',
                    '-o', str(output), '-c', str(source)]
            with patch.object(standalone, 'ROOT', root), patch.object(sys, 'argv', args), \
                 patch.object(autodecomp, 'worker_compile', return_value={
                     'standalone': (0, '', b'new object')}) as compile_job:
                self.assertEqual(standalone.main(), 0)
            self.assertEqual(compile_job.call_args.args[0][0][1], source.read_text())
            self.assertEqual(output.read_bytes(), b'new object')

    def test_unknown_or_repeated_selection_fails(self):
        for flags in [['--assembler=unknown'], ['--assembler=gas-2.40'] * 2]:
            with self.assertRaises(ValueError):
                assembler.selection(flags)

    def test_modern_recipes_explicitly_select_erratum_and_small_data(self):
        command = assembler.command('gas-2.40', ['-G8'], 'input.s', 'output.o')
        self.assertIn('-mno-fix-r5900', command)
        self.assertIn('-G8', command)
        self.assertIn('-mfix-r5900', assembler.command('gas-2.40-fix', [], 'i.s', 'o.o'))

    def test_alternate_recipe_assembles_untouched_compiler_output(self):
        success = subprocess.CompletedProcess([], 0, '', '')
        with patch.object(assembler.subprocess, 'run', return_value=success) as run:
            assembler.compile_with_assembler(['cc'], ['-O2', '--assembler=gas-2.40'],
                                             'input.c', 'output.o', {}, 30)
        self.assertEqual(run.call_args_list[0].args[0],
                         ['cc', '-O2', '-S', 'input.c', '-o', 'output.o.s'])
        self.assertEqual(run.call_args_list[1].args[0][-3:], ['-o', 'output.o', 'output.o.s'])

    def test_compile_failure_does_not_assemble_stale_output(self):
        failure = subprocess.CompletedProcess([], 1, '', 'error')
        with patch.object(assembler.subprocess, 'run', return_value=failure) as run:
            result = assembler.compile_with_assembler(['cc'], ['--assembler=gas-2.40'],
                                                      'input.c', 'output.o', {}, 30)
        self.assertEqual(result.returncode, 1)
        self.assertEqual(run.call_count, 1)


if __name__ == '__main__':
    unittest.main()
