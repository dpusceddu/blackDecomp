"""Synthetic MIPS address materialization; no target execution or game bytes."""
import sys
import unittest
from pathlib import Path
sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from autodecomp import Target, parse_operand, score


class AbsoluteAddresses(unittest.TestCase):
    def test_short_addresses_are_numeric_but_unrelated_names_are_not(self):
        self.assertEqual(parse_operand('D_2014C'), (0x2014c, 0, 'D_2014C'))
        self.assertEqual(parse_operand('D_20abc+0x4')[:2], (0x20abc, 4))
        self.assertEqual(parse_operand('D_FOO')[0], 'D_FOO')
        self.assertEqual(parse_operand('D_100000000')[0], 'D_100000000')

    def target(self, address=0x28000):
        # LUI includes the signed-low carry; compare the actual encoded words.
        return Target(dict(words=[0x3c020003, 0x24428000], rel={
            '0': ['hi', address, 0], '1': ['lo', address, 0]}), None)

    def test_folded_immediates_must_match_complete_original_words(self):
        target = self.target()
        self.assertTrue(score(target, [(0x3c020003, None), (0x24428000, None)], lambda a: None)[0])
        self.assertFalse(score(target, [(0x3c020002, None), (0x24428000, None)], lambda a: None)[0])
        self.assertFalse(score(target, [(0x3c020003, None), (0x24428004, None)], lambda a: None)[0])
        self.assertTrue(score(target, target.tokens, lambda a: None)[0])

    def test_unknown_symbol_is_not_forgiven_even_with_equal_encoded_words(self):
        target = self.target('unknown_symbol')
        self.assertFalse(score(target, [(0x3c020003, None), (0x24428000, None)], lambda a: None)[0])


if __name__ == '__main__':
    unittest.main()
