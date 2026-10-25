"""A timed-out compiler must not leave an assembler holding its output pipe open."""
from pathlib import Path
import os
import sys
import tempfile
import time
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[2]/'tools/build'))
from assembler import run_tool


@unittest.skipUnless(sys.platform.startswith('linux'), 'Linux process groups')
class ToolTimeout(unittest.TestCase):
    def test_timeout_stops_the_child_and_returns_without_waiting_for_its_pipe(self):
        with tempfile.TemporaryDirectory() as directory:
            marker = Path(directory)/'orphan-ran'
            child = 'import time; from pathlib import Path; time.sleep(1); Path(%r).write_text("orphan")' % str(marker)
            parent = 'import subprocess,sys,time; subprocess.Popen([sys.executable,"-c",%r]); time.sleep(30)' % child
            started = time.monotonic()
            result = run_tool([sys.executable,'-c',parent], dict(os.environ), 0.2)
            self.assertEqual(result.returncode,124)
            self.assertIn('process group was stopped',result.stderr)
            self.assertLess(time.monotonic()-started,5)
            time.sleep(1.1)
            self.assertFalse(marker.exists())


if __name__=='__main__':
    unittest.main()
