"""VU rejection is local to a function; register options survive saved recipes."""
import os
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import autodecomp


class VuPipeline(unittest.TestCase):
    def test_unsupported_operation_does_not_abort_batch(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / 's/text').mkdir(parents=True)
            (root / 's/text/func_00F00000.s').write_text('vcallms 0')
            with patch.object(autodecomp, 'AUTO', root), \
                    patch.object(autodecomp, 'BUILD', root), \
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


if __name__ == '__main__':
    unittest.main()
