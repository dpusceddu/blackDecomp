"""Assembler provenance is separate from full-image byte identity."""
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import units_verify


class AssemblerEvidence(unittest.TestCase):
    def save_unit(self, flags, evidence=None):
        unit = dict(name='example', source='src/example.cpp', flags=flags,
                    functions=[dict(addr=0x100000, symbol='Example', status='source')])
        if evidence is not None:
            unit['assembler_evidence'] = evidence
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / 'config').mkdir()
            with patch.object(units_verify, 'ROOT', root):
                units_verify.save([unit])
            return yaml.safe_load((root / 'config/units.yaml').read_text())['units'][0]

    def test_selected_assembler_has_weak_historical_provenance(self):
        for variant in ('sn-min6', 'sn-2.73a'):
            unit = self.save_unit(['-O2', '--assembler=' + variant])
            self.assertEqual(unit['assembler_evidence']['strength'], 'weak')
            self.assertEqual(unit['assembler_evidence']['historical_provenance'], 'unresolved')
            self.assertEqual(unit['functions'][0]['status'], 'source')

    def test_removed_selector_drops_stale_evidence(self):
        unit = self.save_unit(['-O2', '-snas'], {'strength': 'weak'})
        self.assertNotIn('assembler_evidence', unit)


if __name__ == '__main__':
    unittest.main()
