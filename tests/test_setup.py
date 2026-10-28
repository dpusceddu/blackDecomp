"""Session preparation generates metadata by default and uses the active Python environment."""
import importlib.util
import hashlib
import json
from pathlib import Path
import shlex
import shutil
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]


def module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    result = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(result)
    return result


S = module('session_setup', ROOT / 'tools/setup.py')


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


def iso_record(name, lba, size, directory=False):
    name = name.encode('ascii') if isinstance(name, str) else name
    record = bytearray(33 + len(name) + (33 + len(name)) % 2)
    record[0] = len(record)
    struct.pack_into('<I', record, 2, lba)
    struct.pack_into('<I', record, 10, size)
    record[25] = 2 if directory else 0
    record[32] = len(name)
    record[33:33 + len(name)] = name
    return record


def make_iso(path, executable, boot='SLUS_213.76', config=None):
    """A tiny synthetic disc, with no retail game bytes; exercise the real ISO reader."""
    image = bytearray(26 * 2048)
    root = iso_record(b'\0', 20, 2048, True)
    image[16 * 2048:16 * 2048 + 7] = b'\x01CD001\x01'
    image[16 * 2048 + 156:16 * 2048 + 190] = root
    cnf = config if config is not None else ('BOOT2 = cdrom0:\\%s;1\r\nVER = 1.00\r\n' % boot).encode()
    records = iso_record('SYSTEM.CNF;1', 21, len(cnf))
    exe = iso_record(boot + ';1', 22, len(executable))
    records += exe
    image[20 * 2048:20 * 2048 + len(records)] = records
    image[21 * 2048:21 * 2048 + len(cnf)] = cnf
    image[22 * 2048:22 * 2048 + len(executable)] = executable
    path.write_bytes(image)


class GameInput(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'config').mkdir()
        (self.root / 'orig').mkdir()
        self.data = b'\x7fELFsynthetic test executable'
        (self.root / 'config/versions.json').write_text(json.dumps({S.SLUG: {
            'boot': S.SLUG, 'executable_sha256': hashlib.sha256(self.data).hexdigest()}}))
        self.image = self.root / 'orig/game.iso'
        self.dest = self.root / 'orig' / S.SLUG / S.SLUG
        patcher = patch.object(S, 'ROOT', self.root)
        patcher.start()
        self.addCleanup(patcher.stop)

    def test_auto_import_preserves_image_and_extracts_only_verified_executable(self):
        make_iso(self.image, self.data)
        before = self.image.read_bytes()
        S.prepare_game()
        self.assertEqual(self.dest.read_bytes(), self.data)
        self.assertEqual(self.image.read_bytes(), before)
        self.assertEqual(list(self.dest.parent.iterdir()), [self.dest])
        S.prepare_game()  # Reuses and verifies the existing executable.

    def test_unsupported_version_and_missing_boot_leave_no_import(self):
        for kwargs, message in [({'boot': 'UNSUPPORTED'}, 'not USA retail'),
                                ({'config': b'VER = 1.00\n'}, 'no BOOT2')]:
            with self.subTest(kwargs=kwargs):
                make_iso(self.image, self.data, **kwargs)
                with self.assertRaisesRegex(SystemExit, message):
                    S.prepare_game()
                self.assertFalse(self.dest.exists())

    def test_wrong_checksum_is_rejected_before_creating_input(self):
        make_iso(self.image, b'changed executable')
        with self.assertRaisesRegex(SystemExit, 'checksum mismatch'):
            S.prepare_game()
        self.assertFalse(self.dest.parent.exists())

    def test_existing_executable_is_verified_and_never_overwritten(self):
        self.dest.parent.mkdir()
        self.dest.write_bytes(b'existing input')
        make_iso(self.image, self.data)
        for image in (None, self.image):
            with self.subTest(image=image), self.assertRaises(SystemExit):
                S.prepare_game(image)
            self.assertEqual(self.dest.read_bytes(), b'existing input')
        self.dest.write_bytes(self.data)
        S.prepare_game(self.image)

    def test_shared_executable_is_not_replaced(self):
        shared = self.root / 'shared'
        shared.write_bytes(b'existing shared input')
        self.dest.parent.mkdir()
        self.dest.symlink_to(shared)
        make_iso(self.image, self.data)
        with self.assertRaisesRegex(SystemExit, 'move it aside'):
            S.prepare_game(self.image)
        self.assertTrue(self.dest.is_symlink())
        self.assertEqual(shared.read_bytes(), b'existing shared input')

if __name__ == '__main__':
    unittest.main()
