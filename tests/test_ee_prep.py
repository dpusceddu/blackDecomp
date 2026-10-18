import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from ee_prep import prep, post


def assembly(*instructions):
    return '\n'.join('    /* probe */  ' + instruction for instruction in instructions)


class FrameWidths(unittest.TestCase):
    def test_callee_save_does_not_widen_real64_data(self):
        _, flags = prep(assembly('sq $16, 16($29)', 'ld $2, 0($4)', 'lq $16, 16($29)', 'jr $31', 'nop'))
        self.assertFalse(flags['q'])
        self.assertTrue(flags['real64'])
        source = 's64\x00void *arg0\x00return M2C_FIELD(arg0, s64 *, 0);'
        self.assertEqual(post(source, flags), source)

    def test_actual128_memory_stays_wide(self):
        _, flags = prep(assembly('sq $16, 16($29)', 'lq $2, 0($4)', 'lq $16, 16($29)', 'jr $31', 'nop'))
        self.assertTrue(flags['q'])

    def test_overwritten_register_is_not_a_callee_save(self):
        _, flags = prep(assembly('por $16, $4, $0', 'sq $16, 16($29)', 'lq $16, 16($29)', 'jr $31', 'nop'))
        self.assertTrue(flags['q'])

    def test_real_mixed_widths_remain_explicitly_unsupported(self):
        _, flags = prep(assembly('lq $2, 0($4)', 'ld $3, 16($4)'))
        self.assertIsNone(post('s64\x00void *arg0\x00return 0;', flags))

    def test_upper_argument_registers(self):
        _, flags = prep(assembly('por $2, $10, $0'))
        self.assertEqual(flags['qargs'], [6])


if __name__ == '__main__':
    unittest.main()
