"""Authored disassembly fixtures only: no SDK or game bytes needed."""
import sys
from pathlib import Path
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
import vu0_patterns as p


def sequence(*lines):
    return [p.parse_instruction(line, n * 4) for n, line in enumerate(lines)]


class PatternsTests(unittest.TestCase):
    def families(self, *lines):
        return [op['family'] for op in p.semantic_operations(sequence(*lines))]

    def test_alpha_rename_preserves_hardware_zero_masks_lanes_and_aliases(self):
        a = sequence('vadd.xyz $vf7, $vf9, $vf0', 'vmulx.xy $vf9, $vf7, $vf9x')
        b = sequence('vadd.xyz $vf2, $vf4, $vf0', 'vmulx.xy $vf4, $vf2, $vf4x')
        self.assertEqual(p.normalize(a), p.normalize(b))
        self.assertIn('$vf0', p.normalize(a)[0])
        self.assertNotEqual(p.normalize(a), p.normalize(sequence('vadd.xyzw $vf7, $vf9, $vf0', 'vmulx.xy $vf9, $vf7, $vf9x')))
        self.assertNotEqual(p.normalize(a), p.normalize(sequence('vadd.xyz $vf7, $vf9, $vf0', 'vmulx.xy $vf9, $vf7, $vf7x')))

    def test_memory_offsets_and_stack_identity_stay_in_shape(self):
        a = p.normalize(sequence('lqc2 $vf2, 0x10($sp)', 'sqc2 $vf2, 0x20($a0)'))
        b = p.normalize(sequence('lqc2 $vf8, 0x10($sp)', 'sqc2 $vf8, 0x20($s1)'))
        self.assertEqual(a, b)
        self.assertNotEqual(a, p.normalize(sequence('lqc2 $vf8, 0x0($sp)', 'sqc2 $vf8, 0x20($s1)')))

    def test_control_register_numbers_are_fixed_architectural_inputs(self):
        a = sequence('cfc2 $v0, $vi17', 'ctc2 $a0, $vi18')
        self.assertEqual(p.normalize(a), ('cfc2 $gn0,$vi17', 'ctc2 $gn1,$vi18'))
        self.assertIn('vi17', p.architectural_state(a)['inputs'])
        self.assertIn('vi18', p.architectural_state(a)['possible_writes'])
        self.assertNotIn('vi18', p.architectural_state(a)['inputs'])
        reads, writes = p.register_effects(sequence('qmtc2.ni $a0, $vf7')[0])
        self.assertIn('a0', reads)
        self.assertIn('vf7.w', writes)

    def test_projection_stops_at_control_and_delay_slot(self):
        ins = sequence('vadd.xyz $vf1, $vf2, $vf3', 'addiu $a0, $a0, 4',
                       'vsub.xyz $vf4, $vf5, $vf6', 'bnez $a0, somewhere',
                       'vmul.xyz $vf7, $vf8, $vf9', 'vadd.xyz $vf1, $vf2, $vf3')
        self.assertEqual([len(b) for b in p.blocks(ins)], [1, 1, 1, 1])
        self.assertEqual([len(b) for b in p.blocks(ins, projected=True)], [2, 1, 1])

    def test_incoming_branch_target_also_splits_projection(self):
        ins = sequence('vadd.xyz $vf1, $vf2, $vf3', 'vsub.xyz $vf4, $vf5, $vf6', 'bnez $a0, somewhere', 'nop')
        ins[2] = p.dataclasses.replace(ins[2], target=4)
        self.assertEqual([len(b) for b in p.blocks(ins, projected=True)], [1, 1])

    def test_cross_requires_reversed_sources(self):
        self.assertIn('cross3', self.families('vopmula.xyz $ACC, $vf3, $vf4', 'vopmsub.xyz $vf5, $vf4, $vf3'))
        self.assertNotIn('cross3', self.families('vopmula.xyz $ACC, $vf3, $vf4', 'vopmsub.xyz $vf5, $vf3, $vf4'))

    def test_dot_requires_proved_coefficient_and_matching_product(self):
        body = ['vmul.xyz $vf1, $vf2, $vf3', 'vadday.x $ACC, $vf1, $vf1y', 'vmaddz.x $vf1, $vf7, $vf1z']
        self.assertIn('dot3-reduction-candidate', self.families(*body))
        self.assertIn('dot3', self.families('vaddw.x $vf7, $vf0, $vf0w', *body))
        self.assertNotIn('dot3', self.families('vaddw.x $vf7, $vf0, $vf0w', body[0], body[1], 'vmaddz.x $vf1, $vf7, $vf4z'))
        self.assertIn('squared-length3', self.families('vaddw.x $vf7, $vf0, $vf0w', body[0].replace('$vf3', '$vf2'), *body[1:]))

    def test_intervening_load_cannot_be_dropped_for_semantic_chain(self):
        body = ['vaddw.x $vf7, $vf0, $vf0w', 'vmul.xyz $vf1, $vf2, $vf3',
                'lqc2 $vf1, 0x0($sp)', 'vadday.x $ACC, $vf1, $vf1y', 'vmaddz.x $vf1, $vf7, $vf1z']
        self.assertNotIn('dot3', self.families(*body))

    def test_affine_transform_requires_shared_input_and_masks(self):
        body = ['vmulax.xyz $ACC, $vf2, $vf7x', 'vmadday.xyz $ACC, $vf3, $vf7y',
                'vmaddaz.xyz $ACC, $vf4, $vf7z', 'vmaddw.xyz $vf8, $vf5, $vf0w']
        self.assertIn('affine-transform', self.families(*body))
        self.assertNotIn('affine-transform', self.families(body[0], body[1].replace('$vf7y', '$vf6y'), *body[2:]))
        self.assertNotIn('affine-transform', self.families(body[0], body[1].replace('.xyz', '.xyzw'), *body[2:]))

    def test_partial_dest_and_q_acc_state_are_explicit(self):
        reads, writes = p.register_effects(sequence('vmaddz.xyz $vf3, $vf4, $vf5z')[0])
        self.assertIn('vf3.w', reads)
        self.assertIn('ACC', reads)
        self.assertIn('vf5.z', reads)
        self.assertIn('vf3.x', writes)
        self.assertNotIn('vf3.w', writes)
        reads, writes = p.register_effects(sequence('vrsqrt $Q, $vf0w, $vf1x')[0])
        self.assertIn('Q', writes)
        self.assertIn('vf0.w', reads)
        self.assertEqual(p.register_effects(sequence('vcallms 0x20')[0]),
                         ({'microprogram inputs: unknown'}, {'microprogram clobbers: unknown'}))

    def test_nonoverlapping_counts_by_function(self):
        rows = [dict(function=1, start=0, end=12), dict(function=1, start=4, end=16),
                dict(function=1, start=12, end=24), dict(function=2, start=0, end=12)]
        self.assertEqual(len(p.nonoverlapping(rows)), 3)

    def test_projection_retains_cpu_gaps(self):
        ins = sequence('vadd.xyz $vf1, $vf2, $vf3', 'addiu $a0, $a0, 4', 'vsub.xyz $vf1, $vf1, $vf2')
        shapes, _ = p.analyze_function(ins, dict(address=0), 2, 2)
        self.assertEqual(len(shapes), 1)
        self.assertEqual(shapes[0]['mode'], 'projected')
        self.assertEqual(shapes[0]['cpu_gaps'][0]['address'], 4)

    def test_normalization_requires_squared_norm_and_q_not_overwritten(self):
        prefix = ['vaddw.x $vf7, $vf0, $vf0w', 'vmul.xyz $vf1, $vf2, $vf2',
                  'vadday.x $ACC, $vf1, $vf1y', 'vmaddz.x $vf1, $vf7, $vf1z',
                  'vnop', 'vrsqrt $Q, $vf0w, $vf1x', 'vwaitq']
        self.assertIn('normalize3', self.families(*prefix, 'vmulq.xyz $vf2, $vf2, $Q'))
        self.assertNotIn('normalize3', self.families(*prefix, 'vdiv $Q, $vf0w, $vf3x', 'vmulq.xyz $vf2, $vf2, $Q'))
        self.assertNotIn('normalize3', self.families(*prefix, 'vmulq.xyz $vf2, $vf3, $Q'))

    def test_quaternion_requires_full_ordered_hamilton_product(self):
        body = ['vmul.xyzw $vf8, $vf5, $vf6', 'vsubay.w $ACC, $vf8, $vf8y',
                'vmsubaz.w $ACC, $vf0, $vf8z', 'vmsubx.w $vf7, $vf0, $vf8x',
                'vopmula.xyz $ACC, $vf5, $vf6', 'vopmsub.xyz $vf7, $vf6, $vf5',
                'vmulaw.xyz $ACC, $vf6, $vf5w', 'vmaddaw.xyz $ACC, $vf5, $vf6w',
                'vmaddw.xyz $vf7, $vf7, $vf0w']
        self.assertIn('quaternion-product', self.families(*body))
        self.assertNotIn('quaternion-product', self.families(*body[:5], body[5].replace('$vf6, $vf5', '$vf5, $vf6'), *body[6:]))


if __name__ == '__main__':
    unittest.main()
