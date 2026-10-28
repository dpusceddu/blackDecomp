"""Every function belongs to exactly one file and the split ranges do not overlap (tools/build/splits.py, ownership.py)."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import splits as S
import tu_files
import units as U

TABLE = [(0x100000, 0x100010), (0x100010, 0x100020), (0x100020, 0x100030), (0x100030, 0x100040), (0x100040, 0x100050)]


def marker(address):
    return 'INCLUDE_ASM("asm/x", func_%08X);\n' % address


def splits(*entries):
    return [S.Split(dict(e), {}) for e in entries]


class Check(unittest.TestCase):
    def problems(self, entries, files, **kw):
        return S.check_ownership(splits(*entries), read=lambda p: files[p], **kw)

    def test_overlapping_ranges_are_reported(self):
        entries = [{'src': 'a.c', 'range': [0x100000, 0x100030]}, {'src': 'b.c', 'range': [0x100020, 0x100050]}]
        found = self.problems(entries, {'a.c': '', 'b.c': ''})
        self.assertEqual(1, len(found))
        self.assertIn('overlap', found[0])

    def test_the_committed_split_list_has_no_ownership_problems(self):
        # sources only, no game files: ranges and markers
        self.assertEqual([], S.check_ownership(S.load_splits()))


class MovingAFunction(unittest.TestCase):
    def test_a_file_made_for_a_function_takes_it_over_and_gives_it_back_on_revert(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / 'config/SLUS_213.76').mkdir(parents=True)
            (root / 'build/SLUS_213.76').mkdir(parents=True)
            (root / 'src/game').mkdir(parents=True)
            split_list = root / 'config/SLUS_213.76/splits.yaml'
            start = 'variant: SLUS_213.76\nsplits:\n'
            split_list.write_text(start + '  - {src: src/game/a.c, range: [0x100000, 0x100050], flags: [-O1, -G0]}\n')
            a = root / 'src/game/a.c'
            body = ''.join(marker(x) for x, _ in TABLE)
            a.write_text(body.replace('asm/x', tu_files.ASM_DIR))
            (root / 'build/SLUS_213.76/functions.json').write_text('[%s]' % ','.join('[%d,%d]' % t for t in TABLE))
            saved = (S.ROOT, T_ROOT := tu_files.ROOT, U.ROOT)
            try:
                S.ROOT = tu_files.ROOT = U.ROOT = root
                released = tu_files.release_function(0x100020)
                self.assertNotIn('func_00100020', a.read_text())
                left = S.load_splits(path=split_list)
                self.assertEqual([[0x100000, 0x100020], [0x100030, 0x100050]], [[s.start, s.end] for s in left])
                self.assertEqual([], S.check_ownership(left, read=lambda p: (root / p).read_text()))
                tu_files.restore_function(0x100020, released)
                self.assertEqual(body.replace('asm/x', tu_files.ASM_DIR), a.read_text())
                again = S.load_splits(path=split_list)
                self.assertEqual([[0x100000, 0x100050]], [[s.start, s.end] for s in again])
                self.assertEqual(['-O1', '-G0'], again[0].flags)
            finally:
                S.ROOT, tu_files.ROOT, U.ROOT = saved


if __name__ == '__main__':
    unittest.main()
