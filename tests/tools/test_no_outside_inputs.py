"""The repository stands on its own committed files: no tool or test reads the retired config/symbols.txt or analysis exports."""
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SELF = Path(__file__).resolve()
# Spellings of the retired file and of the retired export inputs and outputs.
FORBIDDEN = [
    (re.compile(r"config/symbols\.txt"), 'config/symbols.txt'),
    (re.compile(r"['\"]config['\"]\s*/\s*['\"]symbols\.txt"), "'config' / 'symbols.txt'"),
    (re.compile(r"\.local/ghidra|ghidra_export|ghidra_types|types_ghidra|TYPES_GHIDRA|ghidra_seeds"), 'a Ghidra export input'),
]


def python_files():
    files = [ROOT / 'configure.py']
    for sub in ('tools', 'tests'):
        files += sorted((ROOT / sub).rglob('*.py'))
    return [p for p in files if p.resolve() != SELF]


class NoOutsideInputs(unittest.TestCase):
    def test_the_retired_file_and_headers_are_gone(self):
        for name in ('config/symbols.txt', 'include/types_ghidra.h', 'tools/ghidra_export.py', 'tools/ghidra_types.py'):
            self.assertFalse((ROOT / name).exists(), name)

    def test_no_tool_or_test_names_them(self):
        found = []
        for path in python_files():
            text = path.read_text(errors='replace')
            for pattern, label in FORBIDDEN:
                if pattern.search(text):
                    found.append('%s mentions %s' % (path.relative_to(ROOT), label))
        self.assertEqual([], found)

    def test_sources_and_headers_do_not_include_the_retired_header(self):
        found = [p.relative_to(ROOT).as_posix() for sub in ('src', 'include') for p in (ROOT / sub).rglob('*')
                 if p.suffix in ('.c', '.cpp', '.h', '.hpp') and re.search(r'types_ghidra|TYPES_GHIDRA', p.read_text(errors='replace'))]
        self.assertEqual([], found)

    def test_the_symbol_readers_use_the_per_version_file(self):
        import sys
        sys.path[:0] = [str(ROOT / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
        import splits
        symbols = splits.load_symbols('SLUS_213.76')
        self.assertTrue(symbols.function_aliases())
        self.assertEqual(ROOT / 'config/SLUS_213.76', splits.config_dir('SLUS_213.76'))


if __name__ == '__main__':
    unittest.main()
