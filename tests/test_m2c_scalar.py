"""EE scalar instructions must retain live registers when producing source."""
import importlib.util
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools/pipeline'))
import ee_prep


@unittest.skipUnless(importlib.util.find_spec('m2c'), 'm2c is not installed')
class ScalarDecompilationWorkflow(unittest.TestCase):
    def test_clamp_preserves_bounds_flag_and_later_float(self):
        instructions = [
            'andi $3, $4, 2',
            'max.s $f12, $f12, $f13',
            'min.s $f0, $f12, $f14',
            'beqz $3, .Ldone',
            'nop',
            'mul.s $f0, $f0, $f15',
            '.Ldone:',
            'jr $31',
            'nop',
        ]
        assembly = '.text\nglabel func_00100000\n' + '\n'.join(
            line if line.endswith(':') else f'/* {i * 4:06X} {0x100000 + i * 4:08X} 00000000 */  {line}'
            for i, line in enumerate(instructions)
        )
        prepared, _ = ee_prep.prep(assembly)
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, context = root / 'clamp.s', root / 'context.c'
            source.write_text(prepared)
            context.write_text('''typedef unsigned int u32;
typedef float f32;
f32 func_00100000(u32 flags, f32 value, f32 low, f32 high, f32 scale);
f32 __ee_max_s(f32, f32);
f32 __ee_min_s(f32, f32);
''')
            result = subprocess.run(
                [sys.executable, str(ROOT / 'tools/pipeline/m2c_wrap.py'), '-t', 'mipsee-gcc-c',
                 '--valid-syntax', '--context', str(context), '--no-cache', str(source)],
                capture_output=True, text=True, timeout=30,
            )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('__ee_min_s(__ee_max_s(value, low), high)', result.stdout)
        self.assertIn('if (flags & 2)', result.stdout)
        self.assertIn('*= scale;', result.stdout)
        self.assertNotIn('M2C_ERROR', result.stdout)


if __name__ == '__main__':
    unittest.main()
