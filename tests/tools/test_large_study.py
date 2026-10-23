"""Synthetic scoring and study-design checks; no SDK execution or game fixtures."""
import ast
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import types
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools' / 'studies'))
import autodecomp as auto
from large_study import flag_grid, invariant_flags


class ObjectTokens(unittest.TestCase):
    def test_wrong_pointer_stride_is_an_operand_difference_not_an_allocator_diagnosis(self):
        target = auto.Target(dict(words=[0x24840004], rel={}), None)
        self.assertEqual(auto.score(target, [(0x24840010, None)], lambda address: None),
                         (False, 1, 'operands'))

    def object(self):
        sections = [dict(index=0, name='', type=0), dict(index=1, name='.text', type=1),
                    dict(index=2, name='.text.method', type=1),
                    dict(index=3, name='.rel.text.method', type=9, info=2)]
        symbols = [dict(name='', shndx=0, value=0, size=0),
                   dict(name='method__5Class', shndx=2, value=4, size=8),
                   dict(name='helper__5Class', shndx=1, value=0, size=8)]
        content = {1: struct.pack('<II', 0x03e00008, 0),
                   2: struct.pack('<III', 0, 0x0c000000, 0),
                   3: struct.pack('<II', 4, (2 << 8) | auto.J26)}
        return types.SimpleNamespace(sections=sections, symbols=lambda: symbols,
                                     content=lambda section: content[section['index']])

    def test_named_method_in_function_section_uses_its_own_relocations_and_bounds(self):
        with patch.object(auto, 'Elf', return_value=self.object()):
            tokens, error = auto.compiled_tokens(b'fixture', 'method__5Class',
                                                  bindings={'helper__5Class': 0x100000})
        self.assertIsNone(error)
        self.assertEqual(tokens, [(0x0c000000, ('jal', 0x100000)), (0, None)])

    def test_data_symbol_is_not_accepted_as_function(self):
        obj = self.object()
        obj.sections[2]['name'] = '.rodata'
        with patch.object(auto, 'Elf', return_value=obj):
            self.assertEqual(auto.compiled_tokens(b'fixture', 'method__5Class'),
                             (None, 'function symbol missing'))


class StudyDesign(unittest.TestCase):
    def test_factorial_covers_required_interactions_and_both_assemblers(self):
        grid = flag_grid('ee-gcc2.95.3-136')
        wanted = ('-Os', '-G8', '-fno-schedule-insns', '-fno-schedule-insns2',
                  '-fno-strict-aliasing', '-fbyte-bool')
        self.assertIn(wanted, grid)
        self.assertIn(wanted + ('-snas',), grid)
        self.assertIn(('-O3', '-G0', '-finline-limit-2000', '-snas'), grid)
        self.assertIn(('-O2', '-G0', '-fno-omit-frame-pointer'), grid)
        self.assertEqual(len(grid), len(set(grid)))

    def test_size_optimization_is_a_per_function_candidate_with_both_assemblers(self):
        with patch.object(auto, 'tu_flags', return_value=None), patch.object(auto, 'force_cc', side_effect=lambda x: x):
            flags = auto.extra_sets({'addr': 0x100000, 'rel': {}})
        self.assertIn(['-Os', '-G0', '-snas'], flags)
        self.assertIn(['-Os', '-G0'], flags)
        self.assertIn(['-O2', '-G0', '-snas', '-fno-schedule-insns'], flags)
        self.assertIn(['-O2', '-G0', '-fno-schedule-insns'], flags)
        self.assertEqual(auto.BASE_FLAGS, ['-O2', '-G0', '-snas'])

    def test_only_language_defines_function_sections_and_vu_bank_are_invariants(self):
        self.assertEqual(invariant_flags(['--cc=old', '-O2', '-G0', '-snas', '-fbyte-bool',
                                         '-x', 'c++', '-DNONMATCHING', '-ffunction-sections',
                                         '-mvu0-use-vf0-vf15']),
                         ['-x', 'c++', '-DNONMATCHING', '-ffunction-sections', '-mvu0-use-vf0-vf15'])

    def test_metrowerks_uses_its_language_option_and_no_gcc_specific_section_option(self):
        self.assertEqual(invariant_flags(['-x', 'c++', '-ffunction-sections', '-DNONMATCHING'],
                                         'mwcps2-3.0.1b205-051227'),
                         ['-lang', 'c++', '-DNONMATCHING'])


class CatalogLaunch(unittest.TestCase):
    def test_legacy_windows_compiler_selects_catalog_backend_instead_of_assuming_295(self):
        # build_job executes a full plan at module scope; load only its pure launch function.
        path = Path(__file__).resolve().parents[2] / 'tools/build_job.py'
        function = next(node for node in ast.parse(path.read_text()).body
                        if isinstance(node, ast.FunctionDef) and node.name == 'compile_one')
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            compiler = root / 'ee-gcc2.9-991111b-r4'
            (compiler / 'bin').mkdir(parents=True)
            (compiler / 'bin/ee-gcc.exe').touch()
            backend = compiler / 'lib/gcc-lib/ee/2.9-ee-991111'
            backend.mkdir(parents=True)
            namespace = dict(os=__import__('os'), subprocess=subprocess, CC=str(root))
            exec(compile(ast.Module(body=[function], type_ignores=[]), str(path), 'exec'), namespace)
            result = subprocess.CompletedProcess([], 1, '', 'expected fixture rejection')
            with patch.object(subprocess, 'run', return_value=result) as run:
                rc = namespace['compile_one'](dict(compiler=compiler.name, src='fixture.c',
                                                   obj=str(root / 'obj/fixture.o'), args=['-O2']))[1]
            self.assertEqual(rc, 1)
            self.assertEqual(run.call_args.args[0][2], '-B' + str(backend) + '/')
            self.assertEqual(run.call_args.kwargs['env']['WIBO_PATH'], str(backend))


if __name__ == '__main__':
    unittest.main()
