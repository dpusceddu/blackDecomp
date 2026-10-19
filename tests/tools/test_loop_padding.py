"""Synthetic loop and catalog-recipe checks; no game input or SDK execution."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import assembler
import autodecomp
import compile as standalone
from loop_padding import branch_offset, loops, padding_equivalent


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
