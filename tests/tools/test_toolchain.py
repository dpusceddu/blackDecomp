"""The local toolchain installer: pins are consistent, downloads are verified, archives cannot escape, short paths work."""
import hashlib, io, json, os, sys, tarfile, tempfile, unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import assembler, backend, toolchain


class Pins(unittest.TestCase):
    def test_every_selected_compiler_is_pinned_with_an_archive_hash(self):
        table = toolchain.compiler_table()
        for ident in toolchain.settings()['compilers']:
            entry = table[ident]
            self.assertTrue(entry['source'].startswith('https://github.com/decompme/compilers/releases/download/'), ident)
            self.assertRegex(entry['archive_sha256'], r'^[0-9a-f]{64}$')
            self.assertGreater(entry['files'], 0)

    def test_assemblers_come_from_a_selected_compiler_and_have_both_hashes(self):
        table = toolchain.assembler_table()
        for ident in toolchain.settings()['assemblers']:
            entry = table[ident]
            self.assertIn(entry['source_compiler'], toolchain.settings()['compilers'])
            self.assertRegex(entry['original_sha256'], r'^[0-9a-f]{64}$')
            self.assertRegex(entry['sha256'], r'^[0-9a-f]{64}$')

    def test_wibo_and_objdiff_pins(self):
        settings = toolchain.settings()
        self.assertRegex(settings['wibo']['sha256'], r'^[0-9a-f]{64}$')
        self.assertIn('/releases/download/', settings['wibo']['url'])
        for asset in settings['objdiff']['assets'].values():
            self.assertRegex(asset['sha256'], r'^[0-9a-f]{64}$')


class Downloads(unittest.TestCase):
    def test_hash_mismatch_is_refused_and_leaves_nothing_behind(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'source.bin'
            source.write_bytes(b'payload')
            target = Path(directory) / 'out' / 'file'
            with self.assertRaises(SystemExit):
                toolchain.download(source.as_uri(), '0' * 64, target)
            self.assertFalse(target.exists())
            self.assertEqual([], [p for p in target.parent.iterdir()])

    def test_matching_hash_is_written_once(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory) / 'source.bin'
            source.write_bytes(b'payload')
            target = Path(directory) / 'file'
            digest = hashlib.sha256(b'payload').hexdigest()
            self.assertTrue(toolchain.download(source.as_uri(), digest, target))
            self.assertFalse(toolchain.download(source.as_uri(), digest, target))
            self.assertEqual(b'payload', target.read_bytes())

    def test_archive_members_cannot_leave_the_destination(self):
        with tempfile.TemporaryDirectory() as directory:
            archive = Path(directory) / 'bad.tar'
            with tarfile.open(archive, 'w') as tar:
                info = tarfile.TarInfo('../escape')
                info.size = 1
                tar.addfile(info, io.BytesIO(b'x'))
            with self.assertRaises(SystemExit):
                toolchain.safe_extract(archive, Path(directory) / 'dest')
            self.assertFalse((Path(directory) / 'escape').exists())


class ShortPaths(unittest.TestCase):
    def test_short_paths_are_unchanged_and_long_ones_are_copied(self):
        with tempfile.TemporaryDirectory() as directory:
            deep = Path(directory) / ('d' * 30) / ('e' * 30)
            deep.mkdir(parents=True)
            exe = deep / 'Ps2EeAs.exe'
            exe.write_bytes(b'tool')
            self.assertGreater(len(str(exe)), assembler.SHORT_LIMIT)
            staged = assembler.short_path(exe)
            self.assertLessEqual(len(staged), assembler.SHORT_LIMIT)
            self.assertEqual(b'tool', Path(staged).read_bytes())
            self.assertEqual(staged, assembler.short_path(exe))
            folder = assembler.short_path(deep)
            self.assertEqual(b'tool', (Path(folder) / 'Ps2EeAs.exe').read_bytes())

    def test_missing_files_are_returned_as_given(self):
        self.assertEqual('/nonexistent/' + 'x' * 80, assembler.short_path('/nonexistent/' + 'x' * 80))


class Backend(unittest.TestCase):
    def test_local_is_the_backend(self):
        self.assertEqual('local', backend.name())


if __name__ == '__main__':
    unittest.main()
