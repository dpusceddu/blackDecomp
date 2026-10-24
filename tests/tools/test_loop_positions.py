"""Position inference checks on synthetic loops; no executable or SDK needed."""
import copy
from pathlib import Path
import sys
import unittest

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools' / 'studies'))
import loop_positions as positions


def loop(start=0x1020,length=6,padding=3,function=0x1000,tu_start=0x1000,body=None,sn=True):
    if body is None:
        body=[0x24840001]
    words=body+[0]*padding+[0x14800000|((1-length)&65535),0x24a50001]
    assert len(words)==length
    return dict(addr=hex(start+4*(length-2)),target=hex(start),function=hex(function) if function else None,
                tu='synthetic',tu_range=[hex(tu_start),hex(tu_start+0x100)] if tu_start else None,
                library='synthetic',sn=sn,tu_confidence='exact',length=length,padding_nops=padding,
                padded=bool(padding),words=[hex(w) for w in words],cop2=False,other_branch=False)


def feature(geometry='before_candidate_padding',origin='linked',point='start',operation='mod',modulus=64):
    return dict(name='synthetic',geometry=geometry,origin=origin,point=point,operation=operation,modulus=modulus)


class LoopPositionsTests(unittest.TestCase):
    def annotate(self,rows):
        return positions.annotate(rows,0x1000)

    def test_pre_padding_geometry_is_conditional_and_does_not_mutate_input(self):
        row=loop();snapshot=copy.deepcopy(row)
        result,=self.annotate([row])
        self.assertEqual(row,snapshot)
        self.assertEqual(result['positions']['observed']['linked'],dict(start=0x1020,branch=0x1030,delay=0x1034,end=0x1038))
        self.assertEqual(result['positions']['before_candidate_padding']['linked'],dict(start=0x1020,branch=0x1024,delay=0x1028,end=0x102c))
        self.assertEqual(result['positions']['before_candidate_padding']['function']['branch'],0x24)

    def test_complete_observed_endpoints_leak_length_but_normalized_inputs_collide(self):
        rows=self.annotate([loop(),loop(start=0x1120,length=7,padding=4,function=0x1100,tu_start=0x1100)])
        fs=[feature(point=p,modulus=256) for p in positions.POINTS]
        self.assertEqual(positions.partition(rows,fs)['mixed_groups'],1)
        observed=[dict(f,geometry='observed') for f in fs]
        self.assertEqual(positions.partition(rows,observed)['mixed_groups'],0)
        self.assertEqual(rows[0]['content_id'],rows[1]['content_id'])

    def test_half_open_end_does_not_count_landing_on_a_boundary(self):
        row,=self.annotate([loop(start=0x1008,length=6,padding=3)])
        f=dict(feature(geometry='observed',operation='cross',modulus=32),left='start',right='end')
        self.assertFalse(positions.feature_value(row,f))  # end=0x1020, last byte=0x101f
        row['positions']['observed']['linked']['end']+=4
        self.assertTrue(positions.feature_value(row,f))

    def test_branch_delay_boundary_is_distinct_from_loop_boundary(self):
        row,=self.annotate([loop(start=0x100c,length=6,padding=3)])
        f=dict(feature(geometry='observed',operation='cross',modulus=32),left='branch',right='delay')
        self.assertTrue(positions.feature_value(row,f))

    def test_content_key_preserves_internal_nops_and_delay(self):
        a=loop(length=7,padding=2,body=[0x24840001,0,0x24a50001])
        b=loop(length=6,padding=2,body=[0x24840001,0x24a50001])
        self.assertNotEqual(positions.content_key(a),positions.content_key(b))
        c=copy.deepcopy(a);c['words'][-1]='0x0'
        self.assertNotEqual(positions.content_key(a),positions.content_key(c))
        d=copy.deepcopy(a);d['words'][-3]='0x24840001'
        with self.assertRaises(ValueError):positions.content_key(d)

    def test_unpadded_controls_are_retained_and_not_assigned_an_assembler(self):
        rows=self.annotate([loop(),loop(start=0x1120,length=7,padding=0,body=[1,2,3,4,5])])
        result=positions.partition(rows,[feature()])
        self.assertEqual(result['known_sites'],2)
        self.assertEqual(result['cells'][0]['forms']['unpadded_7'],1)
        self.assertEqual(result['mixed_groups'],0)
        self.assertEqual(rows[1]['positions']['observed'],rows[1]['positions']['before_candidate_padding'])

    def test_unknown_section_origins_do_not_become_false_counterexamples(self):
        rows=self.annotate([loop(function=None),loop(length=7,padding=4,function=None)])
        result=positions.partition(rows,[feature(origin='function')])
        self.assertEqual(result['known_sites'],0)
        self.assertEqual(result['unknown_sites'],2)
        self.assertEqual(result['mixed_groups'],0)

    def test_thresholds_cannot_separate_identical_feature_values(self):
        rows=self.annotate([loop(),loop(start=0x1120,length=7,padding=4,function=0x1100,tu_start=0x1100),
                            loop(start=0x1224,length=7,padding=4,function=0x1200,tu_start=0x1200)])
        r=positions.threshold(rows,feature())
        self.assertEqual(r['best_cut']['errors'],1)
        self.assertEqual(r['best_constant_errors'],1)

    def test_simple_scope_excludes_hardware_but_keeps_raw_control(self):
        rows=[loop(),loop(start=0x1120,length=7,padding=4,function=0x1100,tu_start=0x1100)]
        rows[1]['words'][0]='0x40026000'  # mfc0
        tus=[dict(name='synthetic',text=['0x1000','0x1300'],confidence='exact')]
        result=positions.report(dict(loops=rows),tus,[],0x1000,moduli=(8,))
        self.assertEqual(result['scopes']['sn']['summary']['sites'],2)
        self.assertEqual(result['scopes']['sn_simple']['summary']['sites'],1)
        self.assertEqual(result['loops'][1]['provenance_ambiguities'],['COP0/hardware sequence'])
        self.assertIn('memorization',result['caveats'][9])

    def test_report_accounts_for_non_six_seven_candidates(self):
        rows=[loop(),loop(start=0x1120,length=5,padding=2,function=0x1100),
              loop(start=0x1220,length=7,padding=0,function=0x1200,body=[1,2,3,4,5])]
        tus=[dict(name='synthetic',text=['0x1000','0x1300'],confidence='exact')]
        result=positions.report(dict(loops=rows),tus,[],0x1000,moduli=(8,))
        self.assertIn('| sn | 3 | 1 | 0 | 1 | 1 |',positions.markdown(result))


if __name__=='__main__':
    unittest.main()
