"""Functional validation must use existing binaries without implicit compilation."""
from pathlib import Path
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools/eeharness'))
import gate1


class SourceControlsReached(Exception):
    pass


class ExistingHarnessValidation(unittest.TestCase):
    def test_missing_binary_fails_without_dispatching_any_command(self):
        with tempfile.TemporaryDirectory() as directory, patch.object(gate1, 'run') as run:
            with self.assertRaisesRegex(ValueError, 'existing harness executable required'):
                gate1.check(SimpleNamespace(harness=Path(directory) / 'eeharness'))
            run.assert_not_called()

    def test_existing_suite_runs_before_worker_source_controls_without_building(self):
        counts = {'ee_semantics': 1000, 'vu_semantics': 385, 'cop0_semantics': 121}
        commands = []

        def execute(command, allowed=(0,)):
            commands.append([str(part) for part in command])
            if command[0] == 'ctest':
                return 'all tests passed'
            name = Path(command[0]).name
            if name in counts:
                return 'OK ' + str(counts[name]) + ' assertions'
            self.assertEqual(Path(command[1]).name, 'selfcheck.py')
            raise SourceControlsReached

        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name in ('eeharness', *counts):
                (root / name).touch()
            with patch.object(gate1, 'run', side_effect=execute):
                with self.assertRaises(SourceControlsReached):
                    gate1.check(SimpleNamespace(harness=root / 'eeharness'))
        self.assertEqual([Path(command[0]).name for command in commands[:4]],
                         ['ctest', *counts])
        self.assertEqual(len(commands), 5)


if __name__ == '__main__':
    unittest.main()
