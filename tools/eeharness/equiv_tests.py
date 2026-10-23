#!/usr/bin/env python3
"""Coverage denominator checks for the differential pilot."""
import sys
from pathlib import Path
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from equiv import coverage


class CoverageTests(unittest.TestCase):
    def test_unreachable_alignment(self):
        result=coverage([0x03e00008,0x24020001,0,0],0x1000,[0x1000,0x1004],[(0x1000,0x1004),(0x1004,0xfffffffC)])
        self.assertEqual(result['instructions'],2)
        self.assertEqual(result['block_fraction'],1)

    def test_missing_branch_is_not_full_coverage(self):
        # beq a0,zero,+3; delay; jr ra; delay; jr ra; delay
        result=coverage([0x10800003,0,0x03e00008,0,0x03e00008,0],0x1000,
                        [0x1000,0x1004,0x1008,0x100c],[(0x1000,0x1004),(0x1004,0x1008)])
        self.assertEqual(result['basic_blocks'],3)
        self.assertEqual(result['covered_basic_blocks'],2)
        self.assertEqual(result['branch_outcomes'],2)
        self.assertEqual(result['covered_branch_outcomes'],1)

    def test_branch_likely_annul(self):
        result=coverage([0x50800003,0,0x03e00008,0,0x03e00008,0],0x1000,
                        [0x1000,0x1008,0x100c],[(0x1000,0x1008)])
        self.assertEqual(result['covered_branch_outcomes'],1)
        self.assertEqual(result['covered_instructions'],3)

    def test_unknown_switch_blocks_promotion(self):
        result=coverage([0x01000008,0],0x1000,[0x1000,0x1004],[])
        self.assertEqual(result['unresolved_indirect_jumps'],['0x1000'])

    def test_call_is_not_followed_into_callee(self):
        result=coverage([0x0c080000,0,0x03e00008,0],0x1000,[0x1000,0x1004,0x1008,0x100c],[])
        self.assertEqual(result['instructions'],4)
        self.assertEqual(result['basic_blocks'],2)


if __name__=='__main__':
    unittest.main()
