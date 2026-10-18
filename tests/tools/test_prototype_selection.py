"""Physical ABI evidence and prototype precedence; no target toolchain runs."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp as auto
import context_recovery as cr


def instruction(op, rs, rt, imm):
    return op << 26 | rs << 21 | rt << 16 | (imm & 0xffff)


def function(address, words, rel=None):
    return dict(addr=address, name='func_%08X' % address, words=words,
                rel=rel or {}, size=len(words)*4)


class PhysicalEvidenceTests(unittest.TestCase):
    def recover(self, functions, seeds=None):
        analysis = {f['addr']: cr.analyze_function(f) for f in functions}
        return cr.recover_signatures(functions, analysis, seeds or {})[0]

    def test_live_integer_result_has_direct_producer_and_consumption(self):
        callee = function(0x179cd0, [instruction(0x23, 4, 3, 0x50), 0x03e00008,
                                     instruction(0x23, 3, 2, 8)])
        caller = function(0x100000, [0x0c05e734, 0, instruction(0x0a, 2, 2, 2), 0x03e00008, 0],
                          {'0': ['jal', callee['addr'], 0, callee['name']]})
        row = self.recover([callee, caller])[callee['addr']]
        self.assertEqual(row['return_evidence']['direct_types'], {'gpr': ['s32'], 'fpr': []})
        self.assertEqual(row['return_evidence']['consumed_banks'], ['gpr'])
        self.assertEqual(row['return_evidence']['consumers'], 1)
        self.assertEqual(row['live_register_slots'], [0])

    def test_copy_alone_is_not_caller_consumption(self):
        callee = function(0x200000, [instruction(9, 0, 2, 1), 0x03e00008, 0])
        caller = function(0x100000, [0x0c080000, 0, 0x0040802d, instruction(9, 2, 3, 0), 0x03e00008, 0],
                          {'0': ['jal', callee['addr'], 0, callee['name']]})
        row = self.recover([callee, caller])[callee['addr']]
        self.assertEqual(row['return_evidence']['consumed_banks'], [])

    def test_quadword_and_syscall_facts_do_not_depend_on_propagation(self):
        wide = function(0x179ce0, [instruction(0x1e, 4, 2, 0), 0x03e00008, 0])
        syscall = function(0x367880, [instruction(9, 0, 3, 0x42), 0x0000000c, 0x03e00008, 0])
        rows = self.recover([wide, syscall])
        self.assertEqual(rows[wide['addr']]['return_evidence']['direct_types']['gpr'], ['s128'])
        self.assertFalse(rows[wide['addr']]['syscall'])
        self.assertTrue(rows[syscall['addr']]['syscall'])
        self.assertEqual(rows[syscall['addr']]['return_evidence']['direct_types'], {'gpr': [], 'fpr': []})


class PrototypeSelectionTests(unittest.TestCase):
    def row(self, ret='s32', direct=('s32',), consumed=('gpr',), **updates):
        row = dict(name='func_00179CD0', ret=ret, arity=1, params=['void *'], register_slots=[0],
                   source_quality=1, conflicts=[], return_evidence=dict(
                       direct_types={'gpr': list(direct), 'fpr': []}, consumed_banks=list(consumed)))
        row.update(updates)
        return row

    def check_consumers(self, row, header, expected, m2c_expected=None):
        m2c_expected = m2c_expected or expected
        rows = {str(int(row['name'][5:], 16)): row}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            header_path = root / 'types.h'
            header_path.write_text(header + '\n')
            (root / 'recovered_layouts.c').write_text('')
            with patch.object(auto, 'AUTO', root), patch.object(auto, 'HEADER', header_path), \
                 patch.object(auto, 'recovered_context', return_value={'signatures': rows}), \
                 patch.dict(auto.os.environ, {'AUTODECOMP_FREEZE_CONTEXT': '0'}):
                auto.write_context()
                auto.write_context_arity([])
                for name in ('ctx.c', 'ctx2.c', 'ctx3.c', 'ctx_void.c'):
                    text = (root / name).read_text()
                    self.assertIn(m2c_expected, text, name)
                    self.assertEqual(text.count(row['name'] + '('), 1, name)
                draft, _ = auto.clean_function('func_00100000', dict(ret='void', params='void',
                    body=row['name'] + '(0);', decls={}), {})
                self.assertIn(expected, draft)

    def test_void_live_integer_return_changes_all_consumers(self):
        self.check_consumers(self.row(), 'extern void func_00179CD0(void *);',
                             'extern s32 func_00179CD0(void *);')

    def test_quadword_return_keeps_named_header_parameters(self):
        row = self.row(ret='s128', direct=('s128',), consumed=(), name='func_00179CE0', arity=2,
                       params=['void *', 's32'], register_slots=[0, 1],
                       conflicts=[dict(slot='ret', kind='source-hint-disagrees', types=['s128', 'u64'])])
        self.check_consumers(row, 'extern u64 func_00179CE0(RecoveredRouteRequest *, s32);',
                             'extern s128 func_00179CE0(RecoveredRouteRequest *, s32);',
                             'extern s64 func_00179CE0(RecoveredRouteRequest *, s32);')

    def test_compatible_low_word_facts_keep_named_pointer_return(self):
        self.check_consumers(self.row(ret='void *'), 'extern Named * func_00179CD0(Named *);',
                             'extern Named * func_00179CD0(Named *);')

    def test_uncertain_or_unconsumed_facts_do_not_override_header(self):
        header = 'extern void func_00179CD0(void *);'
        rows = [self.row(ret='unknown'), self.row(direct=()), self.row(consumed=()),
                self.row(ret='s128', direct=('s64', 's128')),
                self.row(conflicts=[dict(slot='ret', types=['s32', 'f32'])])]
        for row in rows:
            with self.subTest(row=json.dumps(row)):
                self.check_consumers(row, header, header)

    def test_width_override_requires_direct_evidence_agreeing_with_resolved_return(self):
        header = 'extern u64 func_00179CD0(void *);'
        for row in (self.row(ret='s128', direct=()), self.row(ret='s128', direct=('s32',))):
            with self.subTest(row=row):
                self.check_consumers(row, header, header)

    def test_low_word_producer_cannot_narrow_a_wider_header_return(self):
        header = 'extern u64 func_00179CD0(void *);'
        self.check_consumers(self.row(), header, header)

    def test_syscall_false_void_arity_relaxes_without_propagated_return_guess(self):
        self.check_consumers(self.row(ret='void *', direct=(), syscall=True, params=['s32']),
                             'extern void func_00179CD0(void);', 'extern void func_00179CD0();')

    def test_authored_signature_stays_anchored(self):
        self.check_consumers(self.row(ret='f32', source_quality=4, params=['f32'], register_slots=[8]),
                             'extern void func_00179CD0(Named *);', 'extern f32 func_00179CD0(f32);')

    def test_float_bank_contradiction_has_direct_support(self):
        row = self.row(ret='f32', return_evidence=dict(direct_types={'gpr': [], 'fpr': ['f32']}, consumed_banks=['fpr']))
        self.check_consumers(row, 'extern s32 func_00179CD0(Named *);', 'extern f32 func_00179CD0(Named *);')


if __name__ == '__main__':
    unittest.main()
