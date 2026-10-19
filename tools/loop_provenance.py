#!/usr/bin/env python3
"""Audit retail short-loop forms against the recovered TU and library map.

This is evidence collection, not assembler selection. Trailing NOPs cannot
establish their author or the assembler used to produce an executable.
"""
import argparse
import collections
import json
from pathlib import Path
import subprocess

import loop_padding


ROOT = Path(__file__).resolve().parents[1]


def number(value):
    return int(value, 0) if isinstance(value, str) else value


def form(row):
    """Do not classify naturally seven-word loops as seven-word padding."""
    return '%s%d' % ('candidate_padded_' if row['padded'] else 'unpadded_', row['length'])


def ambiguity(row):
    """Flag contents for which authored hardware/CFG NOPs are plausible.

    This only narrows a comparison; absence of these markers does not prove
    compiler-generated code or an assembler's historical padding threshold.
    """
    words = [number(w) for w in row.get('words', ())]
    reasons = []
    if any(w >> 26 == 16 for w in words):
        reasons.append('COP0/hardware sequence')
    if row.get('cop2'):
        reasons.append('COP2/vector sequence')
    if row.get('other_branch'):
        reasons.append('inner control instruction')
    if row.get('function') and number(row['target']) < number(row['function']):
        reasons.append('target precedes containing function')
    return reasons


def compact(row):
    """Metadata only: full instruction windows remain in ignored census data."""
    return {k: row.get(k) for k in ('addr', 'target', 'function', 'tu', 'library',
            'tu_confidence', 'tu_range', 'length', 'padding_nops', 'form',
            'provenance_ambiguities', 'source_unit', 'compiler_basis')}


def partition(rows, key):
    groups = collections.defaultdict(list)
    for row in rows:
        groups[row.get(key) or 'unmapped'].append(row)
    result = []
    for name, members in sorted(groups.items()):
        counts = collections.Counter(form(r) for r in members)
        six = sum(r['padded'] and r['length'] == 6 for r in members)
        seven = sum(r['padded'] and r['length'] == 7 for r in members)
        simple = [r for r in members if not r['provenance_ambiguities']]
        simple_six = sum(r['padded'] and r['length'] == 6 for r in simple)
        simple_seven = sum(r['padded'] and r['length'] == 7 for r in simple)
        six_functions = sorted({r['function'] for r in simple if r['padded'] and r['length'] == 6 and r.get('function')})
        seven_functions = sorted({r['function'] for r in simple if r['padded'] and r['length'] == 7 and r.get('function')})
        result.append(dict(name=name, branches=len(members), forms=dict(sorted(counts.items())),
                           candidate_six=six, candidate_seven=seven, mixed=bool(six and seven),
                           simple_candidate_six=simple_six, simple_candidate_seven=simple_seven,
                           simple_mixed=bool(simple_six and simple_seven),
                           simple_six_functions=six_functions, simple_seven_functions=seven_functions,
                           multiple_six_functions=len(six_functions) >= 2,
                           multiple_seven_functions=len(seven_functions) >= 2,
                           simple_below_six=sum(r['length'] < 6 for r in simple),
                           simple_below_seven=sum(r['length'] < 7 for r in simple),
                           confidence_counts=dict(collections.Counter(r.get('tu_confidence') for r in members))))
    return result


def annotate(rows, tus, libraries):
    tus_by_name = {tu['name']: tu for tu in tus}
    result = []
    for original in rows:
        row = dict(original)
        tu = tus_by_name.get(row.get('tu'), {})
        row['tu_range'] = tu.get('text')
        row['tu_evidence'] = tu.get('evidence', [])
        row['form'] = form(row)
        row['provenance_ambiguities'] = ambiguity(row)
        row['library_hulls'] = [lib['name'] for lib in libraries
                                if number(lib['text'][0]) <= number(row['addr']) < number(lib['text'][1])]
        result.append(row)
    return result


def recipe_controls(rows, audit):
    """Join prior independent source compilations to retail/TU metadata."""
    by_function = collections.defaultdict(list)
    for row in rows:
        by_function[row.get('function')].append(row)
    result = []
    for name, unit in sorted(audit.items()):
        for address, function in unit.get('functions', {}).items():
            baseline = function.get('baseline') or {}
            candidate = function.get('candidate') or {}
            if not baseline.get('exact') or candidate.get('exact'):
                continue
            matching = by_function.get(address, [])
            result.append(dict(unit=name, function=address, family=unit.get('family'),
                               differences=candidate.get('differences'),
                               padding_equivalent=bool(function.get('padding_equivalent_to_baseline')),
                               baseline_bytes=baseline.get('bytes'), candidate_bytes=candidate.get('bytes'),
                               loops=[compact(r) for r in matching]))
    return result


def report(census, tus, libraries, audit=None):
    rows = annotate(census['loops'], tus, libraries)
    sn = [r for r in rows if r['sn']]
    high = [r for r in sn if r['tu_confidence'] in ('exact', 'high')]
    tables = {scope: {key: partition(selected, key) for key in ('library', 'tu', 'function')}
              for scope, selected in (('all', rows), ('sn', sn), ('sn_exact_or_high', high))}
    summary = {}
    for scope, selected in (('all', rows), ('sn', sn), ('sn_exact_or_high', high)):
        summary[scope] = dict(branches=len(selected), mapped=sum(bool(r.get('tu')) for r in selected),
                              forms=dict(sorted(collections.Counter(form(r) for r in selected).items())),
                              mixed_libraries=sum(r['mixed'] for r in tables[scope]['library']),
                              mixed_tus=sum(r['mixed'] for r in tables[scope]['tu']),
                              simple_mixed_tus=sum(r['simple_mixed'] for r in tables[scope]['tu']),
                              mixed_functions=sum(r['mixed'] for r in tables[scope]['function']))
        tu_table = tables[scope]['tu']
        summary[scope]['multi_function_six_only_tus'] = sum(t['multiple_six_functions'] and not t['simple_candidate_seven'] for t in tu_table)
        summary[scope]['multi_function_seven_only_tus'] = sum(t['multiple_seven_functions'] and not t['simple_candidate_six'] for t in tu_table)
        summary[scope]['multi_function_six_below_six_tus'] = sum(t['multiple_six_functions'] and not t['simple_candidate_seven'] and bool(t['simple_below_six']) for t in tu_table)
        summary[scope]['multi_function_seven_below_seven_tus'] = sum(t['multiple_seven_functions'] and not t['simple_candidate_six'] and bool(t['simple_below_seven']) for t in tu_table)
    mixed = [r for r in sn if any(t['name'] == r.get('tu') and t['mixed'] for t in tables['sn']['tu'])]
    candidates = []
    for table in tables['sn']['tu']:
        # Require independent functions, a reliable boundary, and no observed
        # ordinary short loop incompatible with the proposed minimum. This is
        # deliberately narrower than extrapolating a whole library's default.
        if (table['multiple_six_functions'] and not table['simple_candidate_seven']
                and not table['simple_below_six']
                and set(table['confidence_counts']) <= {'exact', 'high'}):
            members = [r for r in sn if r.get('tu') == table['name']]
            candidates.append(dict(tu=table['name'], text=members[0]['tu_range'],
                                   library=members[0]['library'], confidence=members[0]['tu_confidence'],
                                   assembler='sn-min6',
                                   basis='at least two distinct functions; all observed ordinary loops compatible; exact/high TU boundary',
                                   historical_identity_verified=False,
                                   evidence=[compact(r) for r in members if r['padded'] and r['length'] == 6
                                             and not r['provenance_ambiguities']]))
    return dict(summary=summary, tables=tables, mixed_tu_loops=[compact(r) for r in mixed],
                independent_regressions=recipe_controls(rows, audit or {}), loops=rows,
                conservative_assignment_candidates=candidates,
                caveats=[
                    'Candidate trailing NOPs are not proof of historical assembler padding.',
                    'Unpadded seven-word loops do not distinguish a six- from a seven-word minimum.',
                    'COP0, COP2 and inner-control examples are separated, not silently discarded.',
                    'Library hulls overlap; the TU library label is the partition used for tables.',
                    'The TU map is inferred; exact/high boundaries and source recipes are reported separately.',
                    'Pure TU/library cohorts show consistency, not the original assembler identity.'])


def markdown(result):
    lines = ['# Short-loop provenance', '',
             'Candidate padding is a binary observation, not proof of an assembler version.', '',
             '| SN-assigned library | Six-word candidates | Seven-word candidates | Other short sites |',
             '| --- | ---: | ---: | ---: |']
    for row in result['tables']['sn']['library']:
        lines.append('| %s | %d | %d | %d |' % (row['name'], row['candidate_six'], row['candidate_seven'],
                     row['branches'] - row['candidate_six'] - row['candidate_seven']))
    lines += ['', '| Subset | Sites | Mixed libraries | Mixed TUs | Mixed TUs after contents flags |',
              '| --- | ---: | ---: | ---: | ---: |']
    for name, row in result['summary'].items():
        lines.append('| %s | %d | %d | %d | %d |' % (name, row['branches'], row['mixed_libraries'],
                     row['mixed_tus'], row['simple_mixed_tus']))
    lines += ['', 'Mixed mapped TUs:', '']
    for tu in result['tables']['sn']['tu']:
        if tu['mixed']:
            lines.append('- `%s`: six=%d, seven=%d; after COP0/inner-control flags six=%d, seven=%d.' %
                         (tu['name'], tu['candidate_six'], tu['candidate_seven'],
                          tu['simple_candidate_six'], tu['simple_candidate_seven']))
    lines += ['', 'Limitations:', ''] + ['- ' + c for c in result['caveats']]
    return '\n'.join(lines) + '\n'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', default='build/loop-provenance/report.json')
    parser.add_argument('--census', help='reuse an ignored tools/loop_padding.py --classify result')
    parser.add_argument('--control-audit', default='build/assembler-rule/control-audit/results.json')
    args = parser.parse_args()
    ignored = subprocess.run(['git', '-C', str(ROOT), 'check-ignore', '--quiet', args.output], capture_output=True)
    if ignored.returncode:
        parser.error('--output must name a Git-ignored path')
    import yaml
    mapping = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())
    census = json.loads(Path(args.census).read_text()) if args.census else loop_padding.classification()
    audit_path = Path(args.control_audit)
    audit = json.loads(audit_path.read_text()) if audit_path.exists() else {}
    result = report(census, mapping['tus'], mapping['libraries'], audit)
    output = Path(args.output)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + '\n')
    output.with_suffix('.md').write_text(markdown(result))
    print(json.dumps(result['summary'], indent=2))


if __name__ == '__main__':
    main()
