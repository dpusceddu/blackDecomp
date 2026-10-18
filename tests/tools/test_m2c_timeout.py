import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp as auto


class DecompilerTimeout(unittest.TestCase):
    def test_single_timeout_is_recorded_without_starting_compiler(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            path = root / 's/text'
            path.mkdir(parents=True)
            (path / 'func_00F00000.s').write_text('glabel func_00F00000\n')
            function = dict(name='func_00F00000', lit4=False)
            with patch.object(auto, 'BUILD', root), patch.object(auto, 'AUTO', root), \
                 patch.object(auto.subprocess, 'run', side_effect=subprocess.TimeoutExpired('m2c', 1)):
                result = auto.run_m2c([function])
        self.assertIn('decompiler timeout', result[function['name']]['error'])


if __name__ == '__main__':
    unittest.main()
