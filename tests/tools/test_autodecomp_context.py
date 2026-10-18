import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp as auto


class IntegrationTests(unittest.TestCase):
    def test_permuter_expansion_removes_header_comments_and_preserves_literals(self):
        source = '#include "recovered/Recovered_Vtable_003DBDC8.h"\nint f(void) { return 1; /* note */ }\n'
        expanded = auto.expand_macros(source)
        self.assertNotIn('/*', expanded)
        sys.path.insert(0, str(auto.PERMUTER))
        try:
            from perm_pycparser import c_parser
        except ImportError:
            self.skipTest('optional pinned permuter is not installed')
        c_parser.CParser().parse(expanded)
        self.assertEqual(auto.strip_c_comments('int/**/x; // note\nchar *s="/*literal*/ //";'),
                         'int x;  \nchar *s="/*literal*/ //";')

    def test_permuter_reports_zero_candidates_instead_of_silent_rounds(self):
        sys.path.insert(0, str(auto.PERMUTER))
        try:
            from src.candidate import Candidate
        except ImportError:
            self.skipTest('optional pinned permuter is not installed')
        import random
        climb = auto.Climb.__new__(auto.Climb)
        climb.src, climb.f, climb.weights, climb.rnd = 'invalid', {'name': 'f'}, {}, random.Random(1)
        with patch.object(Candidate, 'from_source', side_effect=ValueError('bad source')):
            with self.assertRaisesRegex(RuntimeError, 'no candidates for f: bad source'):
                climb.generate(3)

    def test_header_closure_includes_custom_area_dependencies(self):
        result = auto.compile_dependencies('#include "animation/graph.h"\n#include "auto/prelude.h"\n')
        self.assertIn('include/animation/graph.h', result)
        self.assertIn('include/auto/prelude.h', result)

    def test_replacement_only_retires_asm_placeholder(self):
        units = [dict(name='mixed', functions=[dict(addr=1, status='source'), dict(addr=2, status='asm')]),
                 dict(name='asm', functions=[dict(addr=3, status='asm')])]
        out = auto.retire_asm_entries(units, {1, 2, 3})
        self.assertEqual(out, [dict(name='mixed', functions=[dict(addr=1, status='source')])])
        self.assertEqual(len(units[0]['functions']), 2)

    def test_known_float_and_128bit_prototypes_are_preserved(self):
        self.assertEqual(auto.decl_function('f', ('func', 's128', 's64, f32')), 'extern s128 f(s64, f32);')

    def test_failed_settle_stops_before_unit_mutation(self):
        import argparse
        from subprocess import CompletedProcess
        with patch.object(auto.subprocess, 'run', return_value=CompletedProcess([], 1, 'worker failed', 'connection error')) as run, patch.object(auto.sys, 'stderr'):
            with self.assertRaises(SystemExit):
                auto.cmd_settle(argparse.Namespace(group=1))
            self.assertEqual(run.call_count, 1)

    def test_forwarded128_abi_uses_physical_gpr_slot_and_preserves_true64(self):
        rows = {'1048576': dict(name='func_00100000', ret='s128', params=['f32', 's128', 's64'], register_slots=[8, 3, 4]),
                '2097152': dict(name='func_00200000', ret='s128', params=[], register_slots=[])}
        with patch.object(auto, 'recovered_context', return_value={'signatures': rows}):
            ret, params, body = auto.restore_abi_widths('func_00100000', 's64', 'f32 fparg0, s64 arg3, s64 arg4',
                's64 value; s64 real; value = func_00200000(); real = load64(); return value;')
        self.assertEqual(ret, 's128')
        self.assertEqual(params, 'f32 fparg0, s128 arg3, s64 arg4')
        self.assertIn('s128 value;', body)
        self.assertIn('s64 real;', body)

    def test_frozen_missing_context_fails_without_recovery(self):
        import tempfile
        with tempfile.TemporaryDirectory() as directory:
            with patch.object(auto, 'AUTO', Path(directory)), patch.object(auto, 'RECOVERED', None), patch.dict(auto.os.environ, {'AUTODECOMP_FREEZE_CONTEXT': '1'}):
                with self.assertRaisesRegex(SystemExit, 'Frozen recovery context is missing'):
                    auto.recovered_context()


if __name__ == '__main__':
    unittest.main()
