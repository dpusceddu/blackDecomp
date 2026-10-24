"""Queue, checkpoint and scoring safeguards for the durable permuter service."""
import io
import contextlib
import json
import struct
from pathlib import Path
import sys
import tarfile
import tempfile
import unittest
import types
import time
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[2] / 'tools' / d) for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp
import permuter_service
import permuter_worker
import permuter_lanes


class PermuterServiceTests(unittest.TestCase):
    def test_typed_temporaries_retain_native_load_width_and_restore_upstream(self):
        if not autodecomp.PERMUTER.is_dir():
            self.skipTest('pinned permuter checkout is not installed')
        sys.path.insert(0, str(autodecomp.PERMUTER))
        import src.randomizer as randomizer
        from src.candidate import Candidate
        from src.perm.perm import EvalState
        weights = {name: 0 for name in permuter_worker.gcc_weights()}
        weights['perm_temp_for_expr'] = 1
        # SN's native long is 64 bits; a temporary char/short/int would truncate it.
        source = ('unsigned long work(unsigned long *input,unsigned long addend)'
                  '{unsigned long total=*input+addend;return total;}')
        previous = randomizer.PROB_RANDOMIZE_TYPE, randomizer.PROB_REUSE_VAR
        introduced = 0
        unrestricted_narrow = 0
        for seed in range(1, 129):
            candidate = Candidate.from_source(source, EvalState(), 'work', weights, rng_seed=seed)
            permuter_worker.randomize_candidate(candidate, 1, True)
            text = candidate.get_source()
            introduced += 'new_var' in text
            self.assertNotRegex(text, r'\b(?:char|short|float|double)\b')
            def check_types(node):
                if type(node).__name__ == 'Decl' and (node.name or '').startswith('new_var'):
                    base = node.type
                    while hasattr(base, 'type'):
                        base = base.type
                    self.assertEqual(base.names, ['unsigned', 'long'])
                for _, child in node.children():
                    check_types(child)
            check_types(candidate.ast)
            self.assertEqual((randomizer.PROB_RANDOMIZE_TYPE, randomizer.PROB_REUSE_VAR), previous)
            unrestricted = Candidate.from_source(source, EvalState(), 'work', weights, rng_seed=seed)
            permuter_worker.randomize_candidate(unrestricted, 1)
            unrestricted_narrow += any(word in unrestricted.get_source()
                                       for word in ('char', 'short', 'float', 'double'))
        self.assertGreater(introduced, 100)
        self.assertGreater(unrestricted_narrow, 0)
        broken = types.SimpleNamespace(randomize_ast=lambda: (_ for _ in ()).throw(ValueError('failure')))
        with self.assertRaisesRegex(ValueError, 'failure'):
            permuter_worker.randomize_candidate(broken, 1, True)
        self.assertEqual((randomizer.PROB_RANDOMIZE_TYPE, randomizer.PROB_REUSE_VAR), previous)

    def test_typed_temporary_seed_policy_survives_replay_and_keeps_lifetime_passes(self):
        record = dict(key='x', input_hash='typed', submitted_unix_ns=10,
                      function=dict(size=732), saved_differing_instructions=15,
                      typed_temporaries=True)
        with tempfile.TemporaryDirectory() as directory:
            inbox = Path(directory)
            (inbox/'seed.json').write_text(json.dumps(record))
            first, replay = {}, {}
            permuter_worker.ingest_submissions(first, inbox)
            permuter_worker.ingest_submissions(replay, inbox)
        self.assertEqual(first, replay)
        base = dict(perm_randomize_internal_type=10, perm_cast_simple=10,
                    perm_temp_for_expr=120, perm_reorder_decls=35)
        filtered = permuter_worker.candidate_weights(base, typed_temporaries=replay['x']['typed_temporaries'])
        self.assertEqual(filtered['perm_randomize_internal_type'], 0)
        self.assertEqual(filtered['perm_cast_simple'], 0)
        self.assertEqual(filtered['perm_temp_for_expr'], 120)
        self.assertEqual(filtered['perm_reorder_decls'], 35)
        self.assertEqual(base['perm_randomize_internal_type'], 10)

    def test_protected_prefix_allows_only_inert_declarations(self):
        from pycparser import c_parser

        def candidate(before='', literal='AAA'):
            source = ('void work(int count){\n' + before + '\n#pragma _permuter b64literal '
                      + literal + '\nreturn;\n}')
            return types.SimpleNamespace(ast=c_parser.CParser().parse(source), fn_name='work')

        expected = permuter_worker.protected_prefix(candidate())
        self.assertEqual(expected, '_permuter b64literal AAA')
        for before in ('int scalar;', 'int *pointer;', 'int array[4];',
                       'int array[1+2];', 'int (*callback)(int);'):
            self.assertTrue(permuter_worker.prefix_preserved(candidate(before), expected), before)
        for before in ('int scalar=1;', 'count=2;', 'if(0){}', 'int array[count];',
                       'int (*pointer)[count];', 'int array[count++];', 'int array[get_count()];'):
            self.assertFalse(permuter_worker.prefix_preserved(candidate(before), expected), before)
        self.assertFalse(permuter_worker.prefix_preserved(candidate(literal='BBB'), expected))
        self.assertTrue(permuter_worker.prefix_preserved(candidate('count=2;'), None))

    def test_reviewed_seed_refresh_archives_and_retains_accounting_once(self):
        record = dict(key='x', input_hash='new-eight', function=dict(size=1508),
                      saved_differing_instructions=8, preserve_search_accounting=True)
        old = dict(state='running', input_hash='old-eleven', tried=42000,
                   elapsed_seconds=2592.5, rng_state=[3, [1, 2], None],
                   best_rank=[11, 26], best_source='old source', seed_refreshes=2)
        original = json.loads(json.dumps(old))
        with tempfile.TemporaryDirectory() as directory, patch('permuter_worker.time.time_ns', return_value=99):
            root = Path(directory)
            for name in ('baseline.c', 'best.c', 'best.o', 'best.permuter.c', 'best.repository.c'):
                (root/name).write_text('old-'+name)
            refreshed = permuter_lanes.reconcile_state(record, old, set(), 2, root)
            archive = root/'reviewed-seeds'/'99'
            self.assertEqual(json.loads((archive/'state.json').read_text()), original)
            self.assertEqual((archive/'baseline.c').read_text(), 'old-baseline.c')
            self.assertEqual((archive/'best.o').read_text(), 'old-best.o')
            self.assertFalse((root/'best.repository.c').exists())
            # Durable replay of the same accepted submission does not refresh twice.
            self.assertEqual(permuter_lanes.reconcile_state(record, refreshed, set(), 2, root), refreshed)
        self.assertEqual(old, original)
        for field in ('tried', 'elapsed_seconds', 'rng_state'):
            self.assertEqual(refreshed[field], old[field])
        self.assertEqual(refreshed['seed_refreshes'], 3)
        self.assertEqual(refreshed['input_hash'], 'new-eight')
        self.assertNotIn('best_rank', refreshed)
        self.assertNotIn('best_source', refreshed)
        self.assertEqual(refreshed['saved_differing_instructions'], 8)

    def test_changed_seed_resets_accounting_by_default(self):
        record = dict(key='x', input_hash='new', function=dict(size=100), saved_differing_instructions=4)
        old = dict(state='running', input_hash='old', tried=42, elapsed_seconds=55,
                   rng_state=[3, [1, 2], None], best_rank=[3, 9])
        fresh = permuter_worker.refresh_record_state(record, old)
        self.assertEqual(fresh['tried'], 0)
        self.assertEqual(fresh['elapsed_seconds'], 0)
        self.assertNotIn('rng_state', fresh)
        self.assertNotIn('best_rank', fresh)

    def test_target_declarator_freezes_interface_but_allows_local_types(self):
        from pycparser import c_parser

        def signature(source):
            candidate = types.SimpleNamespace(ast=c_parser.CParser().parse(source), fn_name='work')
            return permuter_worker.target_declarator(candidate)

        baseline = signature('int work(unsigned flags,const void*data){int n=0;return n;}')
        self.assertEqual(baseline, signature(
            'int work(register unsigned renamed,const void*pointer){short local=1;return local;}'))
        for changed in (
                'int work(unsigned char flags,const void*data){return 0;}',
                'float work(unsigned flags,const void*data){return 0;}',
                'int work(unsigned flags,void*data){return 0;}',
                'int work(unsigned flags,const void**data){return 0;}'):
            self.assertNotEqual(baseline, signature(changed))

    def test_abi_rebase_archives_diagnostic_and_preserves_search_accounting(self):
        state = dict(state='running', tried=456, elapsed_seconds=123.5, rng_state=[3, [1, 2], None],
                     input_hash='same-seed', size=732, baseline_rank=[16, 22], best_rank=[7, 30],
                     object_sha256='raw-seven', best_source='invalid ABI',
                     best_parser_source='invalid parser ABI', differing_instructions=7, note='operands')
        original = json.loads(json.dumps(state))
        with tempfile.TemporaryDirectory() as directory, patch('permuter_worker.time.time_ns', return_value=99):
            root = Path(directory)
            for name in ('best.c', 'best.o', 'best.permuter.c', 'best.repository.c'):
                (root/name).write_bytes(('diagnostic-'+name).encode())
            archive = permuter_worker.rebase_abi_best(state, root)
            self.assertEqual(archive, root/'rejected-abi'/'99')
            self.assertEqual(json.loads((archive/'state.json').read_text()), original)
            for name in ('best.c', 'best.o', 'best.permuter.c', 'best.repository.c'):
                self.assertEqual((archive/name).read_bytes(), ('diagnostic-'+name).encode())
            self.assertFalse((root/'best.repository.c').exists())
        for field in ('tried', 'elapsed_seconds', 'rng_state', 'input_hash', 'size', 'baseline_rank'):
            self.assertEqual(state[field], original[field])
        for field in ('best_rank', 'best_source', 'best_parser_source', 'object_sha256',
                      'differing_instructions', 'note'):
            self.assertNotIn(field, state)
        self.assertEqual(state['abi_rebases'], 1)

    def test_internal_type_mutator_parameter_drift_is_detected(self):
        if not autodecomp.PERMUTER.is_dir():
            self.skipTest('pinned permuter checkout is not installed')
        sys.path.insert(0, str(autodecomp.PERMUTER))
        from src.candidate import Candidate
        from src.perm.perm import EvalState
        weights = {name: 0 for name in permuter_worker.gcc_weights()}
        weights['perm_randomize_internal_type'] = 1
        source = 'int work(unsigned flags){return flags+1;}'
        baseline = Candidate.from_source(source, EvalState(), 'work', weights, rng_seed=1)
        signature = permuter_worker.target_declarator(baseline)
        rejected = 0
        for seed in range(1, 17):
            candidate = Candidate.from_source(source, EvalState(), 'work', weights, rng_seed=seed)
            candidate.randomize_ast()
            rejected += permuter_worker.target_declarator(candidate) != signature
        self.assertEqual(rejected, 16)

    def test_candidate_randomizer_exclusions_are_scoped_and_strict(self):
        base = {'perm_var_cond_block': 20, 'perm_reorder_decls': 30}
        filtered = permuter_worker.candidate_weights(base, ['perm_var_cond_block'])
        self.assertEqual(filtered, {'perm_var_cond_block': 0, 'perm_reorder_decls': 30})
        self.assertEqual(base['perm_var_cond_block'], 20)
        self.assertEqual(permuter_worker.candidate_weights(base), base)
        with self.assertRaisesRegex(ValueError, 'unknown randomizer'):
            permuter_worker.candidate_weights(base, ['typo'])
        with self.assertRaisesRegex(ValueError, 'must remain enabled'):
            permuter_worker.candidate_weights(base, list(base))

    def test_real_randomizer_receives_zero_weight_for_redundant_conditional(self):
        if not autodecomp.PERMUTER.is_dir():
            self.skipTest('pinned permuter checkout is not installed')
        sys.path.insert(0, str(autodecomp.PERMUTER))
        from src.randomizer import Randomizer
        base = permuter_worker.gcc_weights()
        weights = permuter_worker.candidate_weights(base, ['perm_var_cond_block'])
        methods = {method.__name__: value for method, value in Randomizer(weights, 1).methods}
        self.assertEqual(base['perm_var_cond_block'], 0)
        self.assertEqual(methods['perm_var_cond_block'], 0)
        for name in ('perm_empty_stmt', 'perm_ins_block'):
            self.assertEqual(base[name], 0)
            self.assertEqual(methods[name], 0)
        self.assertGreater(methods['perm_reorder_decls'], 0)

    def test_focused_weight_override_survives_durable_replay_with_checkpoint(self):
        record = dict(key='0x1000', input_hash='focused', submitted_unix_ns=10,
                      function=dict(size=732), saved_differing_instructions=16,
                      disabled_randomizers=['perm_split_assignment'],
                      expanded_source='#pragma _permuter randomizer start\nwork();\n'
                                      '#pragma _permuter randomizer end\n')
        checkpoint = dict(state='running', input_hash='focused', tried=456,
                          elapsed_seconds=123, rng_state=[3, [1, 2], None], best_rank=[2, 6])
        with tempfile.TemporaryDirectory() as directory:
            inbox = Path(directory)
            (inbox/'seed.json').write_text(json.dumps(record))
            first = {}
            permuter_worker.ingest_submissions(first, inbox)
            replay = {}
            permuter_worker.ingest_submissions(replay, inbox)
        self.assertEqual(first, replay)
        self.assertEqual(replay['0x1000'], record)
        self.assertEqual(permuter_lanes.reconcile_state(record, checkpoint, set(), 2),
                         dict(checkpoint, state='queued'))
        base = {'perm_split_assignment': 20, 'perm_reorder_decls': 35}
        self.assertEqual(permuter_worker.candidate_weights(base, record['disabled_randomizers']),
                         {'perm_split_assignment': 0, 'perm_reorder_decls': 35})
        self.assertEqual(base['perm_split_assignment'], 20)

    def test_lanes_dispatch_distinct_largest_keys_and_preempt_smallest_only(self):
        records = {key: dict(function=dict(size=size), saved_differing_instructions=3)
                   for key, size in [('huge', 2000), ('large', 1500), ('small', 800), ('unsupported', 4000)]}
        states = {key: dict(state='queued') for key in records}
        states['unsupported']['state'] = 'unsupported'
        self.assertEqual(permuter_lanes.pending_keys(records, states, {'huge'}), ['large', 'small'])
        self.assertEqual(permuter_lanes.preemption_key(records, states, {'large', 'small'}), 'small')
        self.assertIsNone(permuter_lanes.preemption_key(records, states, {'huge', 'large'}))

    def test_lane_restart_preserves_checkpoint_and_absolute_budget(self):
        record = dict(key='x', input_hash='same', function=dict(size=100), saved_differing_instructions=3)
        checkpoint = dict(state='running', input_hash='same', tried=123, elapsed_seconds=720,
                          rng_state=[3, [10, 20], None], best_rank=[1, 2], best_source='retained')
        resumed = permuter_lanes.reconcile_state(record, checkpoint, set(), 2)
        self.assertEqual(resumed, dict(checkpoint, state='queued'))
        manifest = dict(total_hours=10, deadline_unix=2000)
        self.assertFalse(permuter_lanes.budget_finished(manifest, 1000, 1999))
        self.assertTrue(permuter_lanes.budget_finished(manifest, 1000, 2000))
        self.assertTrue(permuter_lanes.budget_finished(manifest, 36000, 1999))

    def test_actual_lane_children_are_exclusive_and_resume_without_sdk(self):
        # A pure Python stand-in exercises real process separation, graceful
        # checkpoint shutdown and restart. No compiler or SDK fixture is used.
        worker = '''import argparse,json,os,signal,time
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--work');p.add_argument('--output');p.add_argument('--status-file');p.add_argument('--no-wins-index',action='store_true');a=p.parse_args()
record=json.loads((Path(a.work)/'queue.json').read_text())['queue'][0]
folder=Path(a.output)/record['key'];folder.mkdir(exist_ok=True)
lease=folder/'exclusive';fd=os.open(lease,os.O_CREAT|os.O_EXCL|os.O_WRONLY);os.close(fd)
path=folder/'state.json';state=json.loads(path.read_text());state.update(state='running',best_rank=[3,8],baseline_rank=[3,8],rng_state=['retained-stream'])
stop=[False]
signal.signal(signal.SIGTERM,lambda *_:stop.__setitem__(0,True))
try:
 while not stop[0]:
  state['tried']=state.get('tried',0)+1;state['elapsed_seconds']=state.get('elapsed_seconds',0)+.05
  temp=path.with_suffix('.tmp');temp.write_text(json.dumps(state));temp.replace(path);time.sleep(.05)
finally:
 lease.unlink()
'''
        handlers = {sig: __import__('signal').getsignal(sig) for sig in
                    (__import__('signal').SIGTERM, __import__('signal').SIGINT)}
        try:
            with tempfile.TemporaryDirectory() as temporary:
                work = Path(temporary)
                for name in ('tools', 'vendor', 'include', 'inbox'):
                    (work/name).mkdir()
                (work/'tools/permuter_worker.py').write_text(worker)
                records = [dict(key=key, input_hash=key, saved_differing_instructions=3,
                                function=dict(size=size)) for key, size in
                           [('large', 2000), ('medium', 1000), ('small', 728)]]
                manifest = dict(queue=records, integrated_addresses=[], lanes=2, seed=1,
                                total_hours=1, hours_per_function=2, permuter_commit='fixture',
                                deadline_unix=time.time()+1.2)
                permuter_lanes.supervise(work, manifest)
                first = json.loads((work/'output/status.json').read_text())
                before = {r['key']: json.loads((work/'output'/r['key']/'state.json').read_text()) for r in records}
                self.assertEqual(first['state'], 'budget-exhausted')
                self.assertTrue(all(before[key]['tried'] > 0 for key in ('large', 'medium')))
                self.assertEqual(before['small']['tried'], 0)
                self.assertEqual(set(first['lane_wall_seconds']), {'0', '1'})
                self.assertGreater(sum(first['lane_wall_seconds'].values()), first['container_wall_seconds'])
                manifest['deadline_unix'] = time.time()+1.0
                manifest['lanes'] = 3
                permuter_lanes.supervise(work, manifest)
                second = json.loads((work/'output/status.json').read_text())
                self.assertGreater(second['elapsed_seconds'], first['elapsed_seconds']+.7)
                self.assertEqual(second['lanes'], 3)
                for lane in ('0', '1'):
                    self.assertGreater(second['lane_wall_seconds'][lane], first['lane_wall_seconds'][lane])
                self.assertGreater(second['lane_wall_seconds']['2'], 0)
                for record in records:
                    state = json.loads((work/'output'/record['key']/'state.json').read_text())
                    self.assertGreater(state['tried'], before[record['key']]['tried'])
                    self.assertGreater(state['elapsed_seconds'], before[record['key']]['elapsed_seconds'])
                    self.assertEqual(state['rng_state'], ['retained-stream'])
                    self.assertEqual(state['best_rank'], [3, 8])
                    self.assertFalse((work/'output'/record['key']/'exclusive').exists())
        finally:
            for sig, handler in handlers.items():
                __import__('signal').signal(sig, handler)

    def test_explicit_bindings_reject_bad_and_conflicting_addresses(self):
        self.assertEqual(permuter_service.parse_bindings(['sqrtf=0x29eb90', 'sqrtf=2747280']),
                         {'sqrtf': 0x29eb90})
        for values in (['sqrtf'], ['sqrtf=garbage'], ['bad name=0x1000'], ['f=-1'],
                       ['f=0x100000000'], ['sqrtf=0x29eb90', 'sqrtf=0x29eb94']):
            with self.subTest(values=values), self.assertRaises(ValueError):
                permuter_service.parse_bindings(values)

    def test_worker_symbol_binding_resolves_real_jal_and_wrong_binding_stays_mismatched(self):
        sections = [dict(index=0, name='', type=0), dict(index=1, name='.text', type=1),
                    dict(index=2, name='.rel.text', type=9, info=1)]
        symbols = [dict(name='', shndx=0, value=0, size=0),
                   dict(name='func_00306538', shndx=1, value=0, size=4, type=2),
                   dict(name='sqrtf', shndx=0, value=0, size=0, type=2)]
        content = {1: struct.pack('<I', 0x0c000000),
                   2: struct.pack('<II', 0, 2 << 8 | autodecomp.J26)}
        obj = types.SimpleNamespace(sections=sections, symbols=lambda: symbols,
                                    content=lambda section: content[section['index']])
        target = autodecomp.Target(dict(words=[0x0c000000],
                                        rel={'0': ['jal', 0x29eb90, 0]}), None)
        record = {'function': {'name': 'func_00306538'}}
        with patch.object(autodecomp, 'Elf', return_value=obj):
            unresolved, _ = permuter_worker.candidate_tokens(autodecomp, b'fixture', record)
            record['bindings'] = {'sqrtf': 0x29eb90}
            exact, _ = permuter_worker.candidate_tokens(autodecomp, b'fixture', record)
            record['bindings']['sqrtf'] += 4
            wrong, _ = permuter_worker.candidate_tokens(autodecomp, b'fixture', record)
        self.assertFalse(autodecomp.score(target, unresolved, lambda _: None)[0])
        self.assertTrue(autodecomp.score(target, exact, lambda _: None)[0])
        self.assertFalse(autodecomp.score(target, wrong, lambda _: None)[0])

    def test_instruction_threshold_includes_legacy_mismatch_and_orders_by_bytes(self):
        results = {
            '0x1000': dict(status='near', score=4, source='x', size=128),
            '0x2000': dict(status='mismatch', score=29, source='x', size=876),
            '0x3000': dict(status='mismatch', score=30, source='x', size=2048),
            '0x4000': dict(status='near', score=1, source='x', size=4096),
            '0x5000': dict(status='matched', score=0, source='x', size=8192),
        }
        self.assertEqual([key for key, _ in permuter_service.selected_records(results, {0x4000})],
                         ['0x2000', '0x1000'])

    def test_rank_keeps_differing_count_ahead_of_bit_distance(self):
        target = type('Target', (), {'tokens': [(0, None)]})()
        self.assertLess(permuter_worker.rank(False, 2, [(0xffffffff, None)], target),
                        permuter_worker.rank(False, 3, [(0, None)], target))

    def test_nested_field_macro_expands_completely(self):
        source = '#include "ps2/prelude.h"\ns32 f(void *p) { return M2C_FIELD(M2C_FIELD(p, void **, 0), s32 *, 4); }\n'
        expanded = autodecomp.expand_macros(source)
        self.assertNotIn('M2C_FIELD(', expanded)
        self.assertIn('(void **)', expanded)
        self.assertIn('(s32 *)', expanded)

    def test_repository_form_preserves_complete_user_typedef_and_native_prelude(self):
        source = '''typedef int s32;
typedef int s128;
typedef unsigned int u128;
typedef struct { s64 v; } __attribute__((packed)) M2C_U64;
typedef struct Recovered_View
{
    s32 field;
} Recovered_View;
typedef unsigned int UserHandle;
s32 f(Recovered_View *p) { return p->field; }
'''
        restored = autodecomp.committed_form(source)
        self.assertIn('#include "ps2/prelude.h"', restored)
        self.assertNotIn('typedef int s128;', restored)
        self.assertNotIn('typedef unsigned int u128;', restored)
        self.assertNotIn('M2C_U64;', restored)
        self.assertIn('typedef struct Recovered_View\n{', restored)
        self.assertIn('typedef unsigned int UserHandle;', restored)

    def test_snapshot_refuses_parent_traversal_and_links(self):
        for name, kind in (('output/../../escape', tarfile.REGTYPE), ('output/link', tarfile.SYMTYPE)):
            data = io.BytesIO()
            with tarfile.open(fileobj=data, mode='w:gz') as archive:
                item = tarfile.TarInfo(name)
                item.type = kind
                archive.addfile(item, io.BytesIO())
            with tempfile.TemporaryDirectory() as directory:
                with self.assertRaises(ValueError):
                    permuter_service.unpack_snapshot(data.getvalue(), Path(directory))

    def test_rng_checkpoint_replays_next_draw(self):
        import random
        rng = random.Random(42)
        saved = json.loads(json.dumps(rng.getstate()))
        expected = rng.randrange(2**63)
        rng.setstate(permuter_worker.tuple_state(saved))
        self.assertEqual(rng.randrange(2**63), expected)

    def test_restart_replays_accepted_latest_submission_over_manifest(self):
        with tempfile.TemporaryDirectory() as directory:
            inbox = Path(directory)
            original = dict(key='0x1000', input_hash='automatic')
            older = dict(key='0x1000', input_hash='manual-old', submitted_unix_ns=10)
            newer = dict(key='0x1000', input_hash='manual-new', submitted_unix_ns=20)
            # Filename order deliberately opposes submission time.
            (inbox / 'z.json').write_text(json.dumps(older))
            (inbox / 'a.json').write_text(json.dumps(newer))
            live = {'0x1000': original}
            permuter_worker.ingest_submissions(live, inbox)
            self.assertEqual(live['0x1000']['input_hash'], 'manual-new')
            self.assertFalse(list(inbox.glob('*.json')))
            restarted = {'0x1000': original}
            permuter_worker.ingest_submissions(restarted, inbox)
            self.assertEqual(restarted['0x1000']['input_hash'], 'manual-new')
            permuter_worker.ingest_submissions(restarted, inbox)
            self.assertEqual(restarted['0x1000']['input_hash'], 'manual-new')

    def test_new_larger_search_preempts_but_unsupported_and_smaller_do_not(self):
        records = {key: {'function': {'size': size}} for key, size in
                   [('active', 876), ('large', 1944), ('small', 300)]}
        states = {'active': {'state': 'running'}, 'large': {'state': 'unsupported'},
                  'small': {'state': 'queued'}}
        self.assertFalse(permuter_worker.larger_queued(records, states, 'active'))
        states['large']['state'] = 'queued'
        self.assertTrue(permuter_worker.larger_queued(records, states, 'active'))

    def test_restart_retires_manually_integrated_receipt_but_preserves_win(self):
        state = {'state': 'queued', 'tried': 100, 'best_rank': [11, 300]}
        self.assertTrue(permuter_worker.reconcile_integrated(state, '0x1000', {'0x1000'}))
        self.assertEqual(state['state'], 'integrated')
        self.assertEqual(state['tried'], 100)
        self.assertEqual(state['best_rank'], [11, 300])
        self.assertFalse(permuter_worker.reconcile_integrated(state, '0x1000', {'0x1000'}))
        winner = {'state': 'exact', 'best_rank': [0, 0]}
        self.assertFalse(permuter_worker.reconcile_integrated(winner, '0x1000', {'0x1000'}))
        self.assertEqual(winner['state'], 'exact')

    def test_retired_win_survives_queue_removal_but_exact_control_is_not_a_win(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory)
            for key, baseline, digest in [('0x1000', [29, 300], 'valid'),
                                           ('0x2000', [0, 0], 'control'),
                                           ('0x3000', [12, 50], None),
                                           ('0x4000', [14, 80], None)]:
                path = output / key
                path.mkdir()
                (path / 'state.json').write_text(json.dumps(dict(
                    state='exact', baseline_rank=baseline, best_rank=[0, 0], object_sha256=digest)))
            (output / '0x4000/best.o').write_bytes(b'legacy exact artifact')
            wins = permuter_worker.retained_wins(output)
            self.assertEqual(set(wins), {'0x1000', '0x4000'})
            self.assertEqual(len(wins['0x4000']['object_sha256']), 64)
            (output / 'wins.json').write_text(json.dumps(wins))
            (output / '0x1000/state.json').unlink()
            self.assertEqual(set(permuter_worker.retained_wins(output)), {'0x1000', '0x4000'})

    @unittest.skipUnless((autodecomp.PERMUTER / 'src/candidate.py').is_file(), 'permuter setup is optional')
    def test_ignored_cpp_survives_raw_ast_checkpoint_roundtrip(self):
        sys.path.insert(0, str(autodecomp.PERMUTER))
        from src.ast_util import to_c_raw
        from src.candidate import Candidate
        from src.helpers import get_default_randomization_weights
        from src.perm.eval import perm_evaluate_one
        from src.perm.parse import perm_parse
        from src.perm.perm import EvalState
        source = 'PERM_IGNORE(extern "C" {)\nint f(int x) { return x; }\nPERM_IGNORE(})\n'
        with contextlib.redirect_stdout(io.StringIO()):
            parsed = perm_evaluate_one(perm_parse(source))[0]
            first = Candidate.from_source(parsed, EvalState(), 'f', get_default_randomization_weights('gcc'), rng_seed=1)
            checkpoint = to_c_raw(first.ast)
            second = Candidate.from_source(checkpoint, EvalState(), 'f', get_default_randomization_weights('gcc'), rng_seed=2)
        self.assertIn('extern "C" {', first.get_source())
        self.assertIn('extern "C" {', second.get_source())
        self.assertIn('b64literal', checkpoint)

    @unittest.skipUnless((autodecomp.PERMUTER / 'src/candidate.py').is_file(), 'permuter setup is optional')
    def test_native_width_attribute_survives_parser_generation(self):
        sys.path.insert(0, str(autodecomp.PERMUTER))
        from src.candidate import Candidate
        from src.helpers import get_default_randomization_weights
        from src.perm.eval import perm_evaluate_one
        from src.perm.parse import perm_parse
        from src.perm.perm import EvalState
        source = permuter_service.preserve_native_typedefs(
            'typedef int s128 __attribute__((mode(TI)));\n'
            's128 f(s128 x) { return x; }\n')
        with contextlib.redirect_stdout(io.StringIO()):
            parsed = perm_evaluate_one(perm_parse(source))[0]
            candidate = Candidate.from_source(parsed, EvalState(), 'f', get_default_randomization_weights('gcc'), rng_seed=1)
        self.assertIn('typedef int s128 __attribute__((mode(TI)));', candidate.get_source())


if __name__ == '__main__':
    unittest.main()
