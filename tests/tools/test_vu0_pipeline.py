"""VU rejection is local to a function; register options survive saved recipes."""
import os
from pathlib import Path
import sys
import tempfile
import unittest
import subprocess
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp


class VuPipeline(unittest.TestCase):
    def test_unsupported_operation_does_not_abort_batch(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 'nonmatchings').mkdir(parents=True)
            (root / 'nonmatchings/func_00F00000.s').write_text('vcallms 0')
            with patch.object(autodecomp, 'AUTO', root), \
                    patch.object(autodecomp, 'BUILD', root), patch.object(autodecomp, 'FUNCTION_ASM', root / 'nonmatchings'), \
                    patch('m2c_input.prepare', side_effect=ValueError('unverified microprogram')), \
                    patch.object(autodecomp.subprocess, 'run') as run:
                result = autodecomp.run_m2c([dict(name='func_00F00000', lit4=False)])
            run.assert_not_called()
            self.assertEqual(result['func_00F00000']['error'],
                             'ee-instruction: unverified microprogram')

    def test_vu_register_option_is_saved_for_every_variant(self):
        source = [['-O2', '-G0'], ['-Os', '-G0', '-mvu0-use-vf0-vf31']]
        with patch.dict(os.environ, {'AUTODECOMP_VU0': '1'}):
            sets = autodecomp.vu0_flags(dict(mnem=['lqc2', 'vadd.xyz']), source)
            scalar = autodecomp.vu0_flags(dict(mnem=['lw', 'addu']), source)
        self.assertTrue(all(flags.count('-mvu0-use-vf0-vf31') == 1 for flags in sets))
        self.assertEqual(scalar, source)
        self.assertNotIn('-mvu0-use-vf0-vf31', source[0])

    def test_native128_void_pointer_access_keeps_memory_width(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            context = root / 'ctx.c'
            assembly = root / 'probe.s'
            context.write_text('void probe(void *out, void *in);')
            assembly.write_text('.text\nglabel probe\nlqc2 $vf1,0($a1)\nsqc2 $vf1,0($a0)\njr $ra\nnop\n')
            environment = dict(os.environ, AUTODECOMP_VU0='1')
            result = subprocess.run([sys.executable, str(Path(autodecomp.__file__).with_name('m2c_wrap.py')),
                                     '-t', 'mipsee-gcc-c', '--valid-syntax', '--no-cache',
                                     '--context', str(context), str(assembly)],
                                    env=environment, capture_output=True, text=True, timeout=20)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('M2C_FIELD(out, s128 *, 0)', result.stdout)
        self.assertNotIn('*out =', result.stdout)

    def test_vector_low_word_to_float_is_a_bit_transfer(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            context, assembly = root / 'ctx.c', root / 'probe.s'
            context.write_text('float probe(void *in);')
            assembly.write_text('.text\nglabel probe\nlqc2 $vf1,0($a0)\nqmfc2.ni $v0,$vf1\n'
                                'mtc1 $v0,$f0\njr $ra\nnop\n')
            result = subprocess.run([sys.executable, str(Path(autodecomp.__file__).with_name('m2c_wrap.py')),
                                     '-t', 'mipsee-gcc-c', '--valid-syntax', '--no-cache',
                                     '--context', str(context), str(assembly)],
                                    env=dict(os.environ, AUTODECOMP_VU0='1'),
                                    capture_output=True, text=True, timeout=20)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('__ee_vu_read_x(', result.stdout)
        self.assertNotIn('M2C_BITWISE', result.stdout)


if __name__ == '__main__':
    unittest.main()
