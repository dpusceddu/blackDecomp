"""Infrastructure errors must not demote matching source or keep retrying."""
import subprocess
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import settle_units


class SettleFailures(unittest.TestCase):
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
