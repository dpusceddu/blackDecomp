#!/usr/bin/env python3
"""Coverage denominator checks for the differential pilot."""
import sys
from pathlib import Path
import unittest
import struct
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from equiv import coverage, overlay_linker_script, reference_gp


class ReferenceGpTests(unittest.TestCase):
    class Reference:
        def __init__(self, payload, kind=0x70000006):
            self.payload = payload
            self.kind = kind

        def section(self, name):
            return dict(type=self.kind) if self.payload is not None else None

        def content(self, section):
            return self.payload

    def test_original_gp_is_independent_of_overlay_address(self):
        gp = reference_gp(self.Reference(struct.pack('<6I', 0, 0, 0, 0, 0, 0x4157f0)))
        script = overlay_linker_script('candidate', '.text.candidate', ['D_0040E1C4'],
                                      {'D_0040E1C4': 0x40e1c4}, gp)
        self.assertIn('_gp = 0x4157f0;', script)
        self.assertIn('D_0040E1C4 = 0x40e1c4;', script)
        self.assertIn('. = 0x08000000;', script)
        # The original small-data displacement fits; candidate-relative GP would not.
        self.assertTrue(-32768 <= 0x40e1c4 - gp <= 32767)
        self.assertFalse(-32768 <= 0x40e1c4 - 0x08000000 <= 32767)

    def test_missing_malformed_or_zero_gp_is_rejected(self):
        for elf in (self.Reference(None), self.Reference(bytes(20)),
                    self.Reference(bytes(24)), self.Reference(bytes(24), kind=1)):
            with self.subTest(elf=elf), self.assertRaises(ValueError):
                reference_gp(elf)


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
