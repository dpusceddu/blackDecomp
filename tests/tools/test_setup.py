"""Session preparation generates metadata by default and uses the active Python environment."""
import importlib.util
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


S = module('session_setup', ROOT / 'tools/setup.py')
C = module('session_configure', ROOT / 'configure.py')


@unittest.skipUnless(shutil.which('ninja'), 'ninja is not installed')
class Preparation(unittest.TestCase):
    def fixture(self, root):
        tools = root / 'tools'
        (tools / 'build').mkdir(parents=True)
        image = 'build/SLUS_213.76/SLUS_213.76.elf'
        manifest = ('rule write\n  command = %s tools/write.py $out\n'
                    'build objdiff.json: write\nbuild %s: write\n'
                    'build all: phony %s\ndefault all\n') % (shlex.quote(sys.executable), image, image)
        (root / 'configure.py').write_text('from pathlib import Path\nPath("build.ninja").write_text(%r)\n' % manifest)
        (tools / 'write.py').write_text('from pathlib import Path\nimport sys\np=Path(sys.argv[1]); '
                                       'p.parent.mkdir(parents=True,exist_ok=True); p.write_text("generated")\n')
        (tools / 'build/tus.py').write_text('from pathlib import Path\np=Path("build/SLUS_213.76/tus.yaml"); '
                                         'p.parent.mkdir(parents=True,exist_ok=True); p.write_text("tus: []")\n')
        (tools / 'check_elf.py').write_text('from pathlib import Path\nimport sys\n'
                                          'assert Path(sys.argv[2]).is_file()\nPath("verified.stamp").touch()\n')
        return root / image

    def test_default_preparation_does_not_compile_or_link_the_image(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            image = self.fixture(root)
            with patch.object(S, 'ROOT', root):
                S.prepare(sys.executable)
            self.assertTrue((root / 'objdiff.json').is_file())
            self.assertTrue((root / 'build/SLUS_213.76/tus.yaml').is_file())
            self.assertFalse(image.exists())
            self.assertFalse((root / 'verified.stamp').exists())

    def test_explicit_build_also_verifies_an_up_to_date_image(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            image = self.fixture(root)
            with patch.object(S, 'ROOT', root):
                S.prepare(sys.executable, build=True)
                (root / 'verified.stamp').unlink()
                S.prepare(sys.executable, build=True)
            self.assertTrue(image.is_file())
            self.assertTrue((root / 'verified.stamp').is_file())


class Environment(unittest.TestCase):
    def test_active_python_wins_over_checkout_venv(self):
        with patch.object(C.sys, 'prefix', 'active'), patch.object(C.sys, 'base_prefix', 'base'), \
             patch.object(C.sys, 'executable', '/active/python'), patch.object(C.Path, 'is_file', return_value=True):
            self.assertEqual(C.python_command(), '/active/python')

    def test_checkout_venv_is_a_fallback_without_an_active_environment(self):
        with patch.object(C.sys, 'prefix', 'base'), patch.object(C.sys, 'base_prefix', 'base'), \
             patch.object(C.sys, 'executable', '/base/python'), patch.object(C.Path, 'is_file', return_value=True):
            self.assertEqual(C.python_command(), '.venv/bin/python')
        with patch.object(C.sys, 'prefix', 'base'), patch.object(C.sys, 'base_prefix', 'base'), \
             patch.object(C.sys, 'executable', '/base/python'), patch.object(C.Path, 'is_file', return_value=False):
            self.assertEqual(C.python_command(), '/base/python')

    def test_build_modes_are_mutually_exclusive(self):
        result = subprocess.run([sys.executable, str(ROOT / 'tools/setup.py'), '--build', '--no-build'],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 2)
        self.assertIn('not allowed with argument', result.stderr)


if __name__ == '__main__':
    unittest.main()
