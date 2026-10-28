"""Session preparation generates metadata by default and uses the active Python environment."""
import importlib.util
from contextlib import contextmanager
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
P = module('native_permuter_prepare', ROOT / 'tools/permuter/prepare.py')


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

    def test_full_image_build_runs_after_lock_is_released(self):
        held = False
        commands = []

        @contextmanager
        def lock(_root):
            nonlocal held
            held = True
            yield
            held = False

        def run(*args):
            commands.append((args, held))

        with patch.object(S, 'preparation_lock', lock), patch.object(S, 'run', run):
            S.prepare(sys.executable, build=True)
        self.assertEqual([held for _, held in commands], [True, True, True, False, False])

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


class NativeProvisioning(unittest.TestCase):
    def test_permuter_uses_the_selected_native_objdump(self):
        with patch('toolchain.find_binutils', return_value=(Path('/native/bin'), 'mips64-linux-gnu-')):
            self.assertEqual(shlex.split(P.objdump_command()),
                             ['/native/bin/mips64-linux-gnu-objdump', '-drz', '-m', 'mips:5900'])

    def test_package_manager_runs_only_during_explicit_provisioning(self):
        with patch.object(S.sys, 'argv', ['setup.py']), \
             patch.object(S.platform, 'system', return_value='Linux'), \
             patch.object(S.platform, 'machine', return_value='x86_64'), \
             patch.object(S, 'binutils_prefix', return_value='mipsel-linux-gnu-'), \
             patch.object(S.shutil, 'which', return_value=None), \
             patch.object(S, 'provision_system') as provision, patch.object(S, 'run') as run:
            with self.assertRaisesRegex(SystemExit, '--provision once'):
                S.main()
            provision.assert_not_called()
            run.assert_not_called()

    def test_native_distribution_package_commands(self):
        for distro, uid, expected in [('ubuntu', 1000, ['sudo', 'apt-get']), ('fedora', 0, ['dnf'])]:
            with self.subTest(distro=distro), \
                 patch.object(S.platform, 'freedesktop_os_release', return_value={'ID': distro}), \
                 patch.object(S.os, 'geteuid', return_value=uid), \
                 patch.object(S.shutil, 'which', return_value='/usr/bin/tool'), patch.object(S, 'run') as run:
                S.provision_system()
                commands = [list(c.args) for c in run.call_args_list]
                self.assertEqual(commands[-1][:len(expected) + 2], expected + ['install', '-y'])
                self.assertIn('ninja-build', commands[-1])
                self.assertIn('binutils-mipsel-linux-gnu' if distro == 'ubuntu' else 'binutils-mips64-linux-gnu', commands[-1])
                self.assertEqual(len(commands), 2 if distro == 'ubuntu' else 1)

    def test_unsupported_distribution_does_not_install_anything(self):
        with patch.object(S.platform, 'freedesktop_os_release', return_value={'ID': 'unsupported'}), \
             patch.object(S, 'run') as run:
            with self.assertRaisesRegex(SystemExit, 'install the prerequisites'):
                S.provision_system()
            run.assert_not_called()

    def test_native_fedora_prefix_and_explicit_override(self):
        with patch.dict(S.os.environ, {}, clear=True), \
             patch.object(S.shutil, 'which', side_effect=lambda name: '/usr/bin/' + name if name.startswith('mips64-linux-gnu-') else None):
            self.assertEqual(S.binutils_prefix(), 'mips64-linux-gnu-')
        with patch.dict(S.os.environ, {'BLACK_BINUTILS_PREFIX': 'chosen-'}), \
             patch.object(S.shutil, 'which', return_value='/usr/bin/tool'):
            self.assertEqual(S.binutils_prefix(), 'chosen-')

    def test_provisioning_checks_little_endian_linker_support(self):
        with patch.object(S.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, 'Supported emulations:\nelf32ltsmip\n', '')):
            S.verify_native_linker('mips64-linux-gnu-')
        with patch.object(S.subprocess, 'run', return_value=subprocess.CompletedProcess([], 0, 'elf32btsmip\n', '')):
            with self.assertRaisesRegex(SystemExit, 'must support elf32ltsmip'):
                S.verify_native_linker('mips64-linux-gnu-')

    def test_provisioning_needs_no_game_or_image_and_uses_selected_venv_without_reexec(self):
        original_exists = Path.exists
        with tempfile.TemporaryDirectory() as folder, patch.object(S, 'ROOT', Path(folder)), \
             patch.object(S.sys, 'argv', ['setup.py', '--provision']), \
             patch.object(S.sys, 'prefix', 'base'), patch.object(S.sys, 'base_prefix', 'base'), \
             patch.object(S.platform, 'system', return_value='Linux'), \
             patch.object(S.platform, 'machine', return_value='x86_64'), \
             patch.object(S, 'binutils_prefix', return_value='mipsel-linux-gnu-'), \
             patch.object(S.shutil, 'which', return_value='/usr/bin/tool'), \
             patch.object(Path, 'exists', autospec=True, side_effect=lambda p: str(p) == '/lib/ld-linux.so.2' or original_exists(p)), \
             patch.object(S, 'main_worktree', return_value=None), \
             patch.object(S, 'provision_system') as provision, \
             patch.object(S, 'verify_native_linker') as verify, \
             patch.object(S, 'run') as run, patch.object(S, 'prepare') as prepare, \
             patch.object(S.os, 'execv') as reexec:
            self.assertEqual(S.main(), 0)
            provision.assert_called_once()
            verify.assert_called_once_with('mipsel-linux-gnu-')
            prepare.assert_not_called()
            reexec.assert_not_called()
            python = Path(folder) / '.venv/bin/python3'
            self.assertIn((python, 'tools/toolchain.py', 'install', '--objdiff'), [c.args for c in run.call_args_list])
            self.assertIn((python, '-m', 'pip', 'install', '-q', '-r', 'requirements.txt'), [c.args for c in run.call_args_list])

    def test_provisioning_cannot_request_an_image_build(self):
        result = subprocess.run([sys.executable, str(ROOT / 'tools/setup.py'), '--provision', '--build'],
                                capture_output=True, text=True)
        self.assertEqual(result.returncode, 2)
        self.assertIn('not allowed with argument', result.stderr)


if __name__ == '__main__':
    unittest.main()
