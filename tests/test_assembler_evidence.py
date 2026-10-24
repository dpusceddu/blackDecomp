"""Assembler provenance is separate from full-image byte identity."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import splits as S
import units


class AssemblerEvidence(unittest.TestCase):
    def derive(self, **entry):
        split = S.Split(dict(src='src/example.cpp', range=[0x100000, 0x100008], **entry), {})
        unit, = units.derive_units([split], [(0x100000, 0x100008)], S.Symbols(), read=lambda p: '')
        return unit

    def test_selected_assembler_has_weak_historical_provenance(self):
        for variant in ('sn-min6', 'sn-2.73a'):
            unit = self.derive(flags=['-O2'], assembler=variant)
            self.assertIn('--assembler=' + variant, unit['flags'])
            self.assertEqual(unit['assembler_evidence']['strength'], 'weak')
            self.assertEqual(unit['assembler_evidence']['historical_provenance'], 'unresolved')
            self.assertEqual(unit['functions'][0]['status'], 'source')

    def test_snas_without_selector_has_no_evidence(self):
        self.assertNotIn('assembler_evidence', self.derive(flags=['-O2', '-snas']))

    def test_sn_driver_gnu_choice_also_has_weak_provenance(self):
        self.assertEqual(self.derive(flags=['-O2', '-G0'])['assembler_evidence']['strength'], 'weak')


if __name__ == '__main__':
    unittest.main()
