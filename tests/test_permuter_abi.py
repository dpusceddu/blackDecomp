"""A permuter parser round trip must preserve aggregate and scalar ABI attributes."""
from pathlib import Path
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
PERMUTER = ROOT / '.venv/decomp-permuter'
sys.path.insert(0, str(ROOT / 'tools/permuter'))
from abi import preserve_typedefs


@unittest.skipUnless((PERMUTER / 'src/ast_util.py').is_file(), 'decomp-permuter is not installed')
class PermuterAbiWorkflow(unittest.TestCase):
    def test_parser_round_trip_preserves_aligned_and_packed_aggregates(self):
        sys.path.insert(0, str(PERMUTER))
        from src import ast_util
        aligned = '''typedef struct {
    union { unsigned int words[4]; unsigned char bytes[16]; } payload;
    unsigned int flags;
} Parameters __attribute__((aligned(16)));'''
        packed = '''typedef struct __attribute__((packed)) {
    unsigned char tag;
    unsigned int value;
} Packed;'''
        wide = 'typedef int s128 __attribute__((mode(TI)));'
        source = '\n'.join((wide, aligned, packed, '''
void Copy(Parameters* output, Parameters* input) { *output = *input; }
'''))
        prepared = preserve_typedefs(source)
        self.assertEqual(preserve_typedefs(prepared), prepared)
        result = ast_util.to_c(ast_util.parse_c(prepared))
        for declaration in (wide, aligned, packed):
            self.assertEqual(result.count(declaration), 1, result)
        self.assertIn('PermuterSize_s128[sizeof(s128) == 16 ? 1 : -1]', result)
        self.assertIn('*output = *input;', result)


if __name__ == '__main__':
    unittest.main()
