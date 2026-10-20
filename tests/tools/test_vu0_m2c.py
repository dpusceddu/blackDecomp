"""Closed authored VU fixtures and native128 m2c integration, no SDK needed."""
import sys
from pathlib import Path
import subprocess
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import vu0_m2c as v


class LoweringTests(unittest.TestCase):
    def test_splat_bare_architectural_registers(self):
        self.assertIn('bkvu_cross', v.prepare(
            ' vopmula.xyz ACC, $vf2, $vf3\n vopmsub.xyz $vf1, $vf3, $vf2\n', strict=True))
        self.assertIn('bkvu_normalize', v.prepare(
            ' vnop\n vnop\n vnop\n vrsqrt Q, $vf0w, $vf2x\n vwaitq\n vmulq.xyz $vf1, $vf3, Q\n', strict=True))

    def test_mixed_stack_overlay_is_not_a_numeric_cast(self):
        with self.assertRaisesRegex(ValueError, 'mixed-width stack overlay'):
            v.prepare(' sqc2 $vf1, 0x10($29)\n lwc1 $f0, 0x14($29)\n', strict=True)
        self.assertIn('sqc2', v.prepare(' sqc2 $vf1, 0x10($29)\n lwc1 $f0, 0x30($29)\n', strict=True))

    def test_full_store_keeps_w_and_comments(self):
        text = '/* synthetic */ lqc2 $vf1, 0($a0)\n vadd.xyz $vf1, $vf2, $vf3\n sqc2 $vf1, 0($a0)\n'
        got = v.prepare(text)
        self.assertIn('bkvu_add_keep $vf1, $vf1, $vf2, $vf3', got)
        self.assertIn('/* synthetic */', got)

    def test_closed_cross_and_reversed_source_requirement(self):
        got = v.prepare(' vopmula.xyz $ACC, $vf2, $vf3\n vopmsub.xyz $vf1, $vf3, $vf2\n')
        self.assertIn('bkvu_cross $vf1, $vf2, $vf3', got)
        with self.assertRaises(ValueError):
            v.prepare(' vopmula.xyz $ACC, $vf2, $vf3\n vopmsub.xyz $vf1, $vf2, $vf3\n', strict=True)

    def test_closed_sum_preserves_nonx_lanes_when_read(self):
        got = v.prepare(' vadday.x $ACC, $vf2, $vf2y\n vmaddz.x $vf1, $vf3, $vf2z\n sqc2 $vf1, 0($a0)\n')
        self.assertIn('bkvu_sum_keep $vf1, $vf1, $vf2, $vf3', got)

    def test_cpu_or_label_barrier_prevents_fold(self):
        for barrier in [' nop\n', '.Lbranch:\n', ' b somewhere\n nop\n']:
            with self.assertRaises(ValueError):
                v.prepare(' vopmula.xyz $ACC, $vf2, $vf3\n' + barrier + ' vopmsub.xyz $vf1, $vf3, $vf2\n', strict=True)

    def test_closed_normalization_and_rejected_open_q(self):
        got = v.prepare(' vnop\n vnop\n vnop\n vrsqrt $Q, $vf0w, $vf2x\n vwaitq\n vmulq.xyz $vf1, $vf3, $Q\n')
        self.assertIn('bkvu_normalize $vf1, $vf3, $vf2', got)
        with self.assertRaises(ValueError):
            v.prepare(' vrsqrt $Q, $vf0w, $vf2x\n', strict=True)

    def test_microcalls_flags_and_generic_vf0_fail_closed(self):
        for code in [' vcallms 0x20\n', ' cfc2 $v0, $vi17\n', ' vadd.xyz $vf1, $vf0, $vf2\n']:
            with self.assertRaises(ValueError):
                v.prepare(code, strict=True)

    def test_unsupported_input_does_not_abort_a_batch(self):
        text = ' vcallms 0x20\n'
        self.assertEqual(v.prepare(text), text)

    def test_quad_source_cannot_be_invented_from_a_narrow_gpr(self):
        text = ' qmtc2.ni $a1, $vf2\n sqc2 $vf2, 0($a0)\n'
        with self.assertRaises(ValueError):
            v.prepare(text, strict=True)
        self.assertIn('qmtc2.ni', v.prepare(' lq $a1, 0($a2)\n' + text, strict=True))

    def test_complete_m2c_preserves_destination_w_or_reports_unset(self):
        tools = str(Path(v.__file__).resolve().parent)
        program = ('import sys; sys.path.insert(0, ' + repr(tools) + '); '
                   'import vu0_m2c; vu0_m2c.install(); from m2c.main import main; sys.exit(main())')
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / 'authored.s'
            for defined in (True, False):
                text = '.text\nglabel authored\n'
                if defined:
                    text += 'lqc2 $vf1, 0($a0)\n'
                text += ('lqc2 $vf2, 0($a1)\nlqc2 $vf3, 0($a2)\n'
                         'vadd.xyz $vf1, $vf2, $vf3\nsqc2 $vf1, 0($a0)\njr $ra\nnop\nendlabel authored\n')
                path.write_text(v.prepare(text))
                output = subprocess.run([sys.executable, '-c', program, '-t', 'mipsee-gcc-c',
                                         '--valid-syntax', '--no-cache', str(path)], capture_output=True, text=True)
                self.assertEqual(output.returncode, 0, output.stderr)
                self.assertIn('__ee_vu_add_keep', output.stdout)
                if defined:
                    self.assertNotIn('M2C_ERROR', output.stdout)
                    self.assertIn('s128', output.stdout)
                else:
                    self.assertIn('Read from unset register', output.stdout)

    def test_native128_transport_and_dependency_registration(self):
        from m2c.arch_mips import MipseeArch
        from m2c.asm_instruction import Register, AsmAddressMode, AsmLiteral
        from m2c.instruction import InstructionMeta
        v.install()
        v.install()
        meta = InstructionMeta.missing()
        memory = AsmAddressMode(AsmLiteral(0), Register('a0'), writeback=False)
        load = MipseeArch.parse('lqc2', [Register('vf1'), memory], meta)
        store = MipseeArch.parse('sqc2', [Register('vf1'), memory], meta)
        move = MipseeArch.parse('qmtc2.ni', [Register('a1'), Register('vf2')], meta)
        self.assertTrue(load.is_load)
        self.assertTrue(store.is_store)
        self.assertEqual(move.inputs, [Register('a1')])
        self.assertEqual(move.outputs, [Register('vf2')])
        self.assertIn(Register('vf31'), MipseeArch.temp_regs)
        self.assertEqual(MipseeArch.all_regs.count(Register('vf31')), 1)


if __name__ == '__main__':
    unittest.main()
