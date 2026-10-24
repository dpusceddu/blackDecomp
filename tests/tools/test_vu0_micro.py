"""Synthetic VU instruction/control-flow checks; no input executable required."""
import sys
from pathlib import Path
import unittest

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import vu0_micro as micro


def arithmetic(fd, fs, ft, operation=0x28, lanes=0xe):
    return lanes << 21 | ft << 16 | fs << 11 | fd << 6 | operation


def instruction(reads=None, writes=None, branch=None, end=False):
    return dict(reads=reads or {}, writes=writes or {}, branch=branch,
                end=end, hazards=[])


class MicroContracts(unittest.TestCase):
    def test_upper_mask_and_broadcast(self):
        _, reads, writes, _ = micro.upper(arithmetic(4, 7, 9, 0x19))
        self.assertEqual(reads['vf7'], 7)
        self.assertEqual(reads['vf9'], 2)
        self.assertEqual(writes['vf4'], 7)

    def test_lower_rotate_mask(self):
        word = 0x8000003d | 12 << 6 | 7 << 11 | 4 << 16 | 0xa << 21
        name, reads, writes, _, _ = micro.lower(word)
        self.assertEqual(name, 'MR32')
        self.assertEqual(reads, {'vf7': 2 | 8})
        self.assertEqual(writes, {'vf4': 1 | 4})

    def test_sqrt_is_not_a_store(self):
        word = 0x8000003d | 14 << 6 | 7 << 16
        name, reads, writes, _, _ = micro.lower(word)
        self.assertEqual(name, 'SQRT')
        self.assertEqual(reads, {'vf7': 1})
        self.assertIn('Q', writes)
        self.assertNotIn('vu-memory', writes)

    def test_immediate_upper_reads_previous_i(self):
        high = arithmetic(4, 7, 0, 0x22) | 0x80000000
        result = micro.pair(0x3f000000, high)
        self.assertIn('I', result['reads'])
        self.assertIn('I', result['writes'])

    def test_no_false_constant_register_dependency(self):
        _, reads, writes, _ = micro.upper(arithmetic(0, 0, 0))
        self.assertNotIn('vf0', reads)
        self.assertNotIn('vf0', writes)

    def test_upper_and_lower_read_before_same_pair_write(self):
        code = {0: instruction({'vf4': 1}, {'vf4': 1}, end=True),
                8: instruction()}
        result = micro.contract(code, 0)
        self.assertEqual(result['read_before_definition']['vf4'], 'x')

    def test_end_delay_pair_is_included(self):
        code = {0: instruction(end=True), 8: instruction({'vf7': 2}, {'vf8': 4}),
                16: instruction({'vf9': 8})}
        result = micro.contract(code, 0)
        self.assertTrue(result['valid'])
        self.assertEqual(result['pairs'], 2)
        self.assertEqual(result['may_write']['vf8'], 'z')
        self.assertNotIn('vf9', result['read_before_definition'])

    def test_branch_delay_pair_is_included(self):
        code = {0: instruction(branch={'relative': 24, 'conditional': False}),
                8: instruction({'vf7': 2}), 16: instruction({'vf9': 8}),
                24: instruction(end=True), 32: instruction()}
        result = micro.contract(code, 0)
        self.assertTrue(result['valid'])
        self.assertIn('vf7', result['read_before_definition'])
        self.assertNotIn('vf9', result['read_before_definition'])

    def test_join_intersects_definitions(self):
        code = {0: instruction(branch={'relative': 32, 'conditional': True}),
                8: instruction(), 16: instruction(writes={'vf4': 1}),
                24: instruction(), 32: instruction({'vf4': 1}, end=True),
                40: instruction()}
        result = micro.contract(code, 0)
        self.assertTrue(result['valid'])
        self.assertEqual(result['read_before_definition']['vf4'], 'x')

    def test_unbounded_control_flow_invalidates_contract(self):
        self.assertFalse(micro.contract({0: instruction()}, 0)['valid'])

    def test_micro_macro_cooperation_requires_additional_analysis(self):
        code = {0: micro.pair(0x8000033c, 0x600002ff),
                8: micro.pair(0x8000033c, 0x000002ff)}
        result = micro.contract(code, 0)
        self.assertFalse(result['valid'])
        self.assertIn('micro-control-M', result['hazards'])

    def test_micro_clip_has_three_vector_lanes_and_history(self):
        word = 0xe << 21 | 11 << 16 | 7 << 11 | 0x1ff
        _, reads, writes, hazards = micro.upper(word)
        self.assertEqual(reads['vf7'], 7)
        self.assertEqual(reads['vf11'], 8)
        self.assertIn('clip-history', reads)
        self.assertIn('clip-history', writes)
        self.assertFalse(hazards)


if __name__ == '__main__':
    unittest.main()
