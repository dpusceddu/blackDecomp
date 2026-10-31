"""Candidate contracts retain exact-source evidence without inventing void returns or widths."""
from contextlib import redirect_stdout
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path[:0] = [str(Path(__file__).resolve().parents[1] / 'tools' / d)
                for d in ('', 'build', 'pipeline', 'maint')]
import autodecomp as A
import context_recovery as cr
import trysrc


class ContractAudit(unittest.TestCase):
    def setUp(self):
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        self.root = root = Path(directory.name)
        (root / 'src').mkdir()
        (root / 'include').mkdir()
        (root / 'src/provider.c').write_text('''void func_00100000(void* self) {}
void* func_00100200(void* self) { return self; }
void func_00100300(void* self, unsigned long long payload) { }
''')
        self.inventory = [
            dict(addr=0x100000, name='func_00100000', words=[0x24020001, 0x03e00008, 0], rel={}),
            dict(addr=0x100100, name='func_00100100',
                 words=[0x0c040080, 0, 0x0c040000, 0, 0x0c0400c0, 0, 0x03e00008, 0],
                 rel={'0': ['jal', 0x100200, 0], '2': ['jal', 0x100000, 0], '4': ['jal', 0x100300, 0]}),
            dict(addr=0x100200, name='func_00100200', words=[0x00801021, 0x03e00008, 0], rel={}),
            dict(addr=0x100300, name='func_00100300', words=[0x7c850000, 0x03e00008, 0], rel={})]
        units = [dict(source='src/provider.c', externs={}, functions=[dict(addr=a, status='source')
                 for a in (0x100000, 0x100200, 0x100300)])]
        with patch('units.load_units', return_value=units), patch('units.dependencies', side_effect=lambda p: [p]):
            self.context = cr.recover(self.inventory, root)
        self.source = '#include "contracts.h"\nvoid func_00100100(void* self) { SetMode(self); }\n'
        self.header = root / 'include/contracts.h'
        self.header.write_text('''/* multiline comment
   preserves declaration line numbers */
typedef unsigned int Payload;
extern int SetMode(void*) __asm__("func_00100000");
extern void* Allocate(void*) __asm__("func_00100200");
extern void Store(void*, Payload) __asm__("func_00100300");
''')

    def audit(self):
        with patch.object(A, 'ROOT', self.root):
            return cr.audit_candidate(self.context, [0x100100], self.source, 'seed.c',
                                       dependencies=A.compile_dependencies(self.source))

    def test_header_alias_void_conflict_full_width_and_unobserved_factory(self):
        before = self.header.read_bytes()
        report = self.audit()
        findings = report['findings']
        mode, = [f for f in findings if f['function'] == 'func_00100000' and f['level'] == 'warning']
        self.assertEqual(mode['kind'], 'exact-source-contract')
        self.assertEqual(mode['evidence']['expected_return'], 'void')
        self.assertEqual(mode['candidate']['line'], 4)
        self.assertEqual(mode['candidate']['path'], 'include/contracts.h')
        self.assertEqual(mode['evidence']['source']['path'], 'src/provider.c')
        width, = [f for f in findings if f['kind'] == 'native-argument-width']
        self.assertEqual((width['evidence']['candidate_bytes'], width['evidence']['bytes']), (4, 16))
        factory = [f for f in findings if f['function'] == 'func_00100200']
        self.assertEqual(factory, [])  # exact pointer contract needs no speculative return advice
        import copy
        uncertain = copy.deepcopy(self.context)
        uncertain['signatures'][str(0x100200)]['source_evidence']['owner_definition'] = False
        lead = cr.audit_candidate(uncertain, [0x100200],
                                  'void* Allocate(void*) __asm__("func_00100200");', 'lead.c')
        self.assertEqual(lead['findings'][0]['level'], 'review')
        self.assertIn('does not prove a void return', lead['findings'][0]['message'])
        self.assertEqual(before, self.header.read_bytes())
        self.assertEqual(report, json.loads(json.dumps(report)))
        old_dependencies = report['dependencies']
        self.header.write_text(self.header.read_text().replace('extern int SetMode', 'extern void SetMode')
                               .replace('typedef unsigned int Payload', 'typedef unsigned long long Payload'))
        fixed = self.audit()
        self.assertFalse([f for f in fixed['findings'] if f['level'] == 'warning'])
        self.assertNotEqual(old_dependencies, fixed['dependencies'])

    def test_unknown_aggregate_and_overloaded_method_stay_unresolved(self):
        source = '''class AuditObject { void Mode(int); void Mode(float); };
extern UnknownAggregate Create(int) __asm__("func_00100200");
'''
        bindings = {'Mode__11AuditObjectFi': 0x100000, 'Mode__11AuditObjectFf': 0x100200}
        report = cr.audit_candidate(self.context, [0x100100], source, 'seed.cpp', bindings)
        self.assertTrue(report['findings'])
        self.assertTrue(all(f['kind'] == 'unresolved-contract' for f in report['findings']))
        self.assertTrue(any('overloaded' in str(f['evidence']) for f in report['findings']))

    def test_audit_scope_is_independent_of_previous_candidates_or_cold_recovery(self):
        source = '''namespace AuditScope { int Set(void*) __asm__("func_00100000"); }
int AuditScope::Set(void* self) { return 1; }
'''
        clean = cr.audit_candidate(self.context, [0x100000], source, 'scope.cpp')
        self.assertTrue(all(f['kind'] == 'exact-source-contract' for f in clean['findings']))
        self.assertEqual(len(clean['findings']), 2)
        cr.CLASS_NAMES.add('AuditScope')
        cr.POINTER_ALIASES.add('UnrelatedCandidateAlias')
        try:
            polluted = cr.audit_candidate(self.context, [0x100000], source, 'scope.cpp')
            self.assertEqual(clean, polluted)
        finally:
            cr.CLASS_NAMES.discard('AuditScope')
            cr.POINTER_ALIASES.discard('UnrelatedCandidateAlias')

    def test_width_proof_excludes_stack_homing_scalar_copies_and_partial_packed_ops(self):
        # sq a1,0(sp); addu t0,a1,zero; sq t0,0(a0); pextlw t1,a1,a1; jr ra; nop
        f = dict(addr=0x100000, words=[0x7fa50000, 0x03a0f021, 0x7fc50000, 0x00a04021, 0x7c880000, 0x70a54c88, 0x03e00008, 0], rel={})
        self.assertEqual(cr.argument_width_requirements(f), [])
        # por t0,a1,zero; sq t0,0(a0) preserves the whole incoming payload.
        f['words'] = [0x70a044a9, 0x7c880000, 0x03e00008, 0]
        self.assertEqual(cr.argument_width_requirements(f), [(1, 16, 1)])

    def test_trysrc_audits_once_per_source_and_preserves_findings_with_failed_experiment(self):
        candidates = [(Path('seed.c'), self.source, ['-O1']), (Path('seed.c'), self.source, ['-O2'])]
        with patch.object(A, 'ROOT', self.root), patch.object(cr, 'recover', return_value=self.context), \
                redirect_stdout(io.StringIO()) as output:
            audits = trysrc.audit_candidates(self.inventory[1], candidates, {}, self.inventory)
        self.assertEqual(len(audits), 1)
        self.assertEqual(output.getvalue().count('contract audit:'), 1)
        from types import SimpleNamespace
        image = SimpleNamespace(e=SimpleNamespace(data=b'reference image'), word=lambda addr: None)
        with patch.object(A, 'ROOT', self.root), patch.object(A, 'OrigImage', return_value=image), \
                patch.object(A, 'worker_compile', return_value={i: (1, 'compile failed', b'') for i in range(2)}):
            record, directory, _ = trysrc.run_batch(self.inventory[1], candidates, {}, {}, 'contracts',
                                                   self.root / 'experiments', audits=audits)
        saved = json.loads((directory / 'results.json').read_text())
        self.assertEqual(saved['contract_audits'], audits)
        self.assertTrue(next(iter(saved['contract_audits'].values()))['report']['findings'])
        self.assertIsNone(record['best'])


if __name__ == '__main__':
    unittest.main()
