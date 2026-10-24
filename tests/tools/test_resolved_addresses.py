"""Strict MIPS REL address comparisons, using synthetic instructions only."""
import struct
import sys
import unittest
from pathlib import Path
sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
from autodecomp import CompiledTokens, HI, LO, Target, resolved_address_words, score


class ResolvedAddresses(unittest.TestCase):
    def resolve(self, words, rels, bindings):
        return resolved_address_words(struct.pack('<' + 'I' * len(words), *words), rels, bindings)

    def test_signed_low_carry_and_nonzero_addend(self):
        symbol = dict(name='address')
        result = self.resolve([0x3c020001, 0x24428004],
                              {0: (HI, symbol), 4: (LO, symbol)}, {'address': 0x28000})
        self.assertEqual(result, {0: 0x3c020003, 4: 0x24420004})

    def test_all_pending_highs_pair_with_their_low(self):
        symbol = dict(name='D_00028000')
        result = self.resolve([0x3c020000, 0x3c030000, 0x24420000],
                              {0: (HI, symbol), 4: (HI, symbol), 8: (LO, symbol)}, {})
        self.assertEqual(result[0], 0x3c020003)
        self.assertEqual(result[4], 0x3c030003)
        self.assertEqual(result[8], 0x24428000)

    def test_unknown_unpaired_and_distinct_aliases_stay_unresolved(self):
        first, second = dict(name='known'), dict(name='known')
        self.assertEqual(self.resolve([0x3c020000], {0: (HI, first)}, {'known': 0x28000}), {})
        self.assertEqual(self.resolve([0x3c020000, 0x24420000],
                         {0: (HI, first), 4: (LO, first)}, {}), {})
        self.assertNotIn(0, self.resolve([0x3c020000, 0x24420000],
                         {0: (HI, first), 4: (LO, second)}, {'known': 0x28000}))

    def test_retail_raw_high_and_symbolic_object_can_match(self):
        target = Target(dict(words=[0x3c020003, 0x24428000],
                             rel={'1': ['lo', 0x28000, 0]}), None)
        tokens = CompiledTokens()
        tokens.extend([(0x3c020000, ('hi', 2)), (0x24420000, ('lo', 0x28000))])
        tokens.resolved_words = {0: 0x3c020003, 1: 0x24428000}
        self.assertTrue(score(target, tokens, lambda a: None)[0])
        tokens.resolved_words[0] = 0x3c020002
        self.assertFalse(score(target, tokens, lambda a: None)[0])

    def test_wrong_low_and_unknown_target_are_not_forgiven(self):
        target = Target(dict(words=[0x24428000], rel={'0': ['lo', 'unknown', 0]}), None)
        tokens = CompiledTokens()
        tokens.append((0x24420000, ('lo', 0x28000)))
        tokens.resolved_words = {0: 0x24428000}
        self.assertFalse(score(target, tokens, lambda a: None)[0])
        target = Target(dict(words=[0x24428000], rel={}), None)
        tokens.resolved_words = {0: 0x24428004}
        self.assertFalse(score(target, tokens, lambda a: None)[0])


if __name__ == '__main__':
    unittest.main()
