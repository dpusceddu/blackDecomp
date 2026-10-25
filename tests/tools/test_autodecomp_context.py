import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as auto


class IntegrationTests(unittest.TestCase):
    def test_changed_headers_invalidate_a_saved_near_score(self):
        old = dict(status='near', score=2, source='source')
        with patch.object(auto, 'compiled_tokens', return_value=(['tokens'], None)), \
             patch.object(auto, 'Target'), patch.object(auto, 'score', return_value=(False, 27, 'changed layout')):
            updated = auto.rescore_saved_record(old, (0, '', b'object'), dict(name='f'), type('Image', (), {'word': None})())
        self.assertEqual((updated['status'], updated['score']), ('mismatch', 27))
        self.assertEqual(old['score'], 2)

    def test_deleted_draft_header_cannot_keep_a_historical_score(self):
        updated = auto.rescore_saved_record(dict(status='near', score=1, note='old'),
                                            (1, 'missing header', None), dict(name='f'), None)
        self.assertEqual(updated['status'], 'compile-failed')
        self.assertNotIn('score', updated)
        self.assertNotIn('note', updated)

    def test_instruction_rescore_does_not_erase_a_placement_failure(self):
        with patch.object(auto, 'compiled_tokens', return_value=(['tokens'], None)), \
             patch.object(auto, 'Target'), patch.object(auto, 'score', return_value=(True, 0, 'exact')):
            updated = auto.rescore_saved_record(dict(status='verify-failed', reason='extra'),
                (0, '', b'object'), dict(name='f'), type('Image', (), {'word': None})())
        self.assertEqual((updated['status'], updated['reason'], updated['score']), ('verify-failed', 'extra', 0))

    def test_duplicate_candidates_compile_once_and_persistent_counts_include_cache_reuse(self):
        import json
        import subprocess
        import tempfile
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ('include/macro.inc', 'tools/build/elfobj.py', 'tools/build/assembler.py'):
                path = root / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text('')
            auto_dir = root / 'build/auto'
            def worker(*args, **kwargs):
                command=args[0]
                self.assertEqual(Path(command[1]).name, 'compile.py')
                self.assertIn('-o',command)
                return subprocess.CompletedProcess([], 1, '', 'rejected')
            jobs = [('first', 'int f(void) {return 0;}', ['-O2', '-G0']),
                    ('same', 'int f(void) {return 0;}', ['-O2', '-G0'])]
            with patch.object(auto, 'ROOT', root), patch.object(auto, 'AUTO', auto_dir), \
                 patch.object(auto, 'compile_dependencies', return_value={}), \
                 patch('object_compile.environment'), \
                 patch.object(auto.subprocess, 'run', side_effect=worker) as run:
                first = auto.worker_compile(jobs)
                second = auto.worker_compile(jobs)
            self.assertEqual(first, second)
            self.assertEqual(set(first), {'first', 'same'})
            self.assertEqual(run.call_count, 1)
            rows = [json.loads(line) for path in (auto_dir / 'telemetry').glob('*.jsonl') for line in path.read_text().splitlines()]
            self.assertEqual([row['status'] for row in rows], ['submitted', 'completed', 'cached'])
            self.assertEqual(rows[0]['requested'], 2)
            self.assertEqual(rows[0]['compile_jobs'], 1)
            self.assertEqual(rows[0]['call_id'], rows[1]['call_id'])
            self.assertEqual(rows[2]['cached'], 2)

    def test_variadic_abi_overrides_stale_header_in_all_contexts_and_compile_drafts(self):
        import tempfile
        row = dict(name='func_002A5548', ret='s32', arity=1, params=['s32'],
                   register_slots=[0], source_quality=1.5, variadic=True)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            header = root / 'types.h'
            header.write_text('extern int func_002A5548(int, float, float);\n')
            (root / 'recovered_layouts.c').write_text('')
            with patch.object(auto, 'AUTO', root), patch.object(auto, 'HEADER', header), \
                 patch.object(auto, 'recovered_context', return_value={'signatures': {str(0x2a5548): row}}), \
                 patch.dict(auto.os.environ, {'AUTODECOMP_FREEZE_CONTEXT': '0'}):
                auto.write_context()
                auto.write_context_arity([])
                for name in ('ctx.c', 'ctx2.c', 'ctx3.c', 'ctx_void.c'):
                    self.assertIn('s32 func_002A5548(s32, ...);', (root / name).read_text())
                    self.assertNotIn('(int, float, float)', (root / name).read_text())
                draft, _ = auto.clean_function('func_00100000', dict(ret='s32', params='s32 arg0',
                    body='return func_002A5548(arg0, 9);', decls={}), {})
                self.assertIn('extern s32 func_002A5548(s32, ...);', draft)

    def test_split_switch_includes_secondary_labels_but_not_tail_or_owned_data(self):
        import tempfile
        source = '''.section .text.00100000, "ax"
glabel func_00100000
    /* 0 00100000 0800E003 */ jr $31
endlabel func_00100000
    /* 4 00100004 00000000 */ nop
jlabel func_00100008
    /* 8 00100008 0000023C */ lui $2, %hi(D_00400000)
endlabel func_00100008
    /* C 0010000C 00000000 */ nop
.section .rodata.00400000, "a"
dlabel D_00400000
    /* 10 00400000 00000000 */ .word 0
'''
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'switch.s'
            path.write_text(source)
            words, rel, mnemonics, _ = auto.parse_function(path)
        self.assertEqual(len(words), 3)
        self.assertEqual(mnemonics, ['jr', 'nop', 'lui'])
        self.assertEqual(rel[2], ('hi', 0x400000, 0, 'D_00400000'))

    def test_gnu_assembler_is_a_real_fallback_with_conditional_small_data_flags(self):
        with patch.object(auto, 'tu_flags', return_value=None), patch.object(auto, 'force_cc', side_effect=lambda x: x):
            regular = auto.extra_sets({'addr': 0x100000, 'rel': {}})
            small = auto.extra_sets({'addr': 0x100000, 'rel': {'0': ['gprel', 0x400000, 0, 'value']}})
        self.assertIn(['-O2', '-G0'], regular)
        self.assertIn(['-O2', '-G0', '-fbyte-bool'], regular)
        self.assertNotIn(['-O2', '-G1'], regular)
        self.assertIn(['-O2', '-G1'], small)
        self.assertIn(['-O2', '-G8', '-fbyte-bool'], small)
        with patch.object(auto, 'tu_flags', return_value=(auto.SONY, [], 'default')), patch.object(auto, 'force_cc', side_effect=lambda x: x):
            candidates = auto.extra_sets({'addr': 0x100000, 'rel': {}})
            self.assertEqual(candidates[:len(auto.SONY_EXTRA)], auto.SONY_EXTRA)
            self.assertIn(['--cc=' + auto.SONY, '--assembler=sn-2.73a'], candidates)

    def test_tu_assembler_selection_is_replaced_by_each_fallback(self):
        from assembler import FALLBACKS, selection
        for compiler in (auto.COMPILER, auto.SONY):
            recipe = ['-O2', '-G0', '--assembler=sn-min6']
            with patch.object(auto, 'tu_flags', return_value=(compiler, recipe, 'matched')), \
                 patch.object(auto, 'force_cc', side_effect=lambda x: x):
                candidates = auto.extra_sets({'addr': 0x100000, 'rel': {}})
            choices = [selection(flags)[0] for flags in candidates]
            self.assertEqual([choice for choice in choices if choice], list(FALLBACKS))

    def test_permuter_expansion_removes_header_comments_and_preserves_literals(self):
        source = '#include "game/object_56980.h"\nint f(void) { return 1; /* note */ }\n'
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
        result = auto.compile_dependencies('#include "animation/graph.h"\n#include "ps2/prelude.h"\n')
        self.assertIn('include/animation/graph.h', result)
        self.assertIn('include/ps2/prelude.h', result)

    def test_known_float_and_128bit_prototypes_are_preserved(self):
        self.assertEqual(auto.decl_function('f', ('func', 's128', 's64, f32')), 'extern s128 f(s64, f32);')

    def test_failed_confirm_stops_before_unit_mutation(self):
        import argparse
        from subprocess import CompletedProcess
        with patch.object(auto, 'load_results', return_value={}), patch.object(auto.subprocess, 'run', return_value=CompletedProcess([], 1, 'worker failed', 'connection error')) as run, patch.object(auto.sys, 'stderr'):
            with self.assertRaises(SystemExit):
                auto.cmd_confirm(argparse.Namespace(group=1))
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
