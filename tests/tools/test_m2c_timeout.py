import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as auto


class DecompilerTimeout(unittest.TestCase):
    def test_batch_parse_failure_is_not_recorded_as_function_failures(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'nonmatchings'
            path.mkdir(parents=True)
            (path / 'func_00F00000.s').write_text('glabel func_00F00000\n')
            failed = subprocess.CompletedProcess([], 1, '/*\nDecompilation failure:\nFailed to parse instruction\n*/', '')
            with patch.object(auto, 'BUILD', root), patch.object(auto, 'FUNCTION_ASM', root / 'nonmatchings'), patch.object(auto, 'AUTO', root), \
                 patch.object(auto.subprocess, 'run', return_value=failed):
                with self.assertRaisesRegex(SystemExit, 'before analyzing the batch'):
                    auto.run_m2c([dict(name='func_00F00000', lit4=False)])

    def test_single_timeout_is_recorded_without_starting_compiler(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 'nonmatchings'
            path.mkdir(parents=True)
            (path / 'func_00F00000.s').write_text('glabel func_00F00000\n')
            function = dict(name='func_00F00000', lit4=False)
            with patch.object(auto, 'BUILD', root), patch.object(auto, 'FUNCTION_ASM', root / 'nonmatchings'), patch.object(auto, 'AUTO', root), \
                 patch.object(auto.subprocess, 'run', side_effect=subprocess.TimeoutExpired('m2c', 1)):
                result = auto.run_m2c([function])
        self.assertIn('decompiler timeout', result[function['name']]['error'])


if __name__ == '__main__':
    unittest.main()
