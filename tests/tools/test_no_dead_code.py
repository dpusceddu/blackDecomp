"""The sources hold no code that no build can reach: a draft is an `#ifdef NON_MATCHING` block above its INCLUDE_ASM line,
and readable code whose function is not known is not kept (docs/units.md, "Drafts")."""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


class NoDeadCode(unittest.TestCase):
    def test_no_if_0_block_in_src_or_include(self):
        found = []
        for base in ('src', 'include'):
            for path in sorted((ROOT / base).rglob('*')):
                if path.suffix in ('.c', '.cpp', '.h', '.hpp') and re.search(r'^\s*#\s*if\s+0\b', path.read_text(errors='replace'), re.M):
                    found.append(path.relative_to(ROOT).as_posix())
        self.assertEqual([], found)


if __name__ == '__main__':
    unittest.main()
