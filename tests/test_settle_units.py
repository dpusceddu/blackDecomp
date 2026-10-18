"""Infrastructure errors must not demote matching source or keep retrying."""
import subprocess
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import settle_units


class SettleFailures(unittest.TestCase):
    def test_alignment_cascade_restores_input_claims_and_stops(self):
        import tempfile
        original = b'units:\n- name: old\n  functions:\n  - {addr: 0x1000, status: source}\n- name: candidate\n  functions:\n  - {addr: 0x2000, status: source}\n'
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'units.yaml'
            path.write_bytes(original.replace(b'status: source', b'status: asm'))
            with self.assertRaisesRegex(SystemExit, 'demoted 1 committed functions'):
                settle_units.check_source_regression(path, original, {0x1000}, 'compare')
            self.assertEqual(path.read_bytes(), original)

    def test_new_candidate_can_be_demoted_without_losing_committed_source(self):
        import tempfile
        original = b'units:\n- name: old\n  functions:\n  - {addr: 4096, status: source}\n- name: candidate\n  functions:\n  - {addr: 0x2000, status: source}\n'
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'units.yaml'
            demoted = original.replace(b'addr: 0x2000, status: source', b'addr: 0x2000, status: asm')
            path.write_bytes(demoted)
            settle_units.check_source_regression(path, original, {0x1000}, 'prepare')
            self.assertEqual(path.read_bytes(), demoted)

    def test_failed_generator_aborts(self):
        result = subprocess.CompletedProcess([], 1, '', 'invalid placement')
        with patch.object(settle_units.subprocess, 'run', return_value=result):
            with self.assertRaises(SystemExit):
                settle_units.run('tools/make_ld.py', 'usa-retail')

    def test_worker_failure_is_fatal_even_for_candidate_compile(self):
        result = subprocess.CompletedProcess([], 1, '', 'Build backend failed; check the build backend configuration.')
        with patch.object(settle_units.subprocess, 'run', return_value=result):
            with self.assertRaises(SystemExit):
                settle_units.run('tools/build_objects.py', 'usa-retail', check=False)

    def test_compiler_diagnostic_can_be_settled(self):
        result = subprocess.CompletedProcess([], 1, 'compiler: unknown type name', '')
        with patch.object(settle_units.subprocess, 'run', return_value=result):
            self.assertIs(settle_units.run('tools/build_objects.py', 'usa-retail', check=False), result)


if __name__ == '__main__':
    unittest.main()
