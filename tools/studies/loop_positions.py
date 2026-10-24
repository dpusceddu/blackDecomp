#!/usr/bin/env python3
"""Read-only address-position study of retail SN-assigned short loops.

Run with the repository Python environment. Detailed output must stay ignored:
  tools/studies/loop_positions.py --output build/loop-positions/report.json

Observed endpoints contain the emitted length, so their apparent ability to
separate six/seven forms is outcome leakage. Also test the hypothetical input
geometry before the candidate trailing NOPs, without deleting or rewriting any
instruction. Candidate NOP origin and original input-section starts are unknown.
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path[:0] = [str(_Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]  # the core tools
import argparse
import collections
import hashlib
import json
from pathlib import Path
import subprocess

import loop_padding
import loop_provenance as provenance


ROOT = Path(__file__).resolve().parents[2]
MODULI = (8, 16, 32, 64, 128, 256, 512, 1024, 4096)
POINTS = ('start', 'branch', 'delay', 'end')
ORIGINS = ('linked', 'function', 'tu', 'text')
GEOMETRIES = ('observed', 'before_candidate_padding')


def content_key(row):
    """Preserve all words except the candidate NOP run and branch displacement.

    Unlike dropping every NOP, this retains authored-looking internal NOPs and
    other controls' delay NOPs. The preceding classifier supplies the candidate
    count. Registers, immediates, other branch words and delay slot stay exact.
    """
    words = [provenance.number(w) for w in row['words']]
    padding = row['padding_nops']
    if not 0 <= padding <= len(words) - 2:
        raise ValueError('candidate padding is outside the loop body')
    if padding and any(words[-2-padding:-2]):
        raise ValueError('candidate padding contains a non-NOP word')
    return tuple(words[:-2-padding]) + (words[-2] & 0xffff0000, words[-1])


def positions(row, text_base):
    start, branch = map(provenance.number, (row['target'], row['addr']))
    bases = dict(linked=0, function=provenance.number(row['function']) if row.get('function') else None,
                 tu=provenance.number(row['tu_range'][0]) if row.get('tu_range') else None,
                 text=text_base)
    result = {}
    for geometry in GEOMETRIES:
        # This is a conditional hypothesis, not reconstruction of source bytes.
        b = branch - (4 * row['padding_nops'] if geometry == 'before_candidate_padding' else 0)
        values = dict(start=start, branch=b, delay=b+4, end=b+8)
        result[geometry] = {origin: {point: value-base if base is not None else None
                                    for point, value in values.items()}
                            for origin, base in bases.items()}
    return result


def annotate(rows, text_base):
    result = []
    for original in rows:
        row = dict(original)
        row['form'] = provenance.form(row)
        row['provenance_ambiguities'] = provenance.ambiguity(row)
        row['positions'] = positions(row, text_base)
        row['content_id'] = hashlib.sha256(repr(content_key(row)).encode()).hexdigest()[:16]
        result.append(row)
    return result


def feature_catalog(moduli=MODULI):
    result = []
    for geometry in GEOMETRIES:
        for origin in ORIGINS:
            for point in POINTS:
                if origin != 'linked':
                    result.append(dict(name=f'{geometry}.{origin}.{point}.distance', geometry=geometry,
                                       origin=origin, point=point, operation='distance'))
                for modulus in moduli:
                    result.append(dict(name=f'{geometry}.{origin}.{point}.mod{modulus}', geometry=geometry,
                                       origin=origin, point=point, operation='mod', modulus=modulus))
            for left, right in (('start', 'branch'), ('branch', 'delay'), ('start', 'end')):
                for modulus in moduli:
                    result.append(dict(name=f'{geometry}.{origin}.{left}_{right}.cross{modulus}',
                                       geometry=geometry, origin=origin, left=left, right=right,
                                       operation='cross', modulus=modulus))
    return result


def feature_value(row, feature):
    p = row['positions'][feature['geometry']][feature['origin']]
    if feature['operation'] in ('distance', 'mod'):
        value = p[feature['point']]
        return value if value is None or feature['operation'] == 'distance' else value % feature['modulus']
    left, right = p[feature['left']], p[feature['right']]
    if left is None or right is None:
        return None
    # End is exclusive; landing exactly on a boundary does not cross it.
    right -= feature['right'] == 'end'
    return right // feature['modulus'] != left // feature['modulus']


def compact(row):
    return {k: row.get(k) for k in ('addr', 'target', 'function', 'tu', 'library', 'tu_confidence',
                                   'form', 'padding_nops', 'content_id', 'provenance_ambiguities')}


def partition(rows, features, with_content=False, examples=3):
    """Test deterministic position separation, retaining every unpadded control.

    A mixed cell contains both candidate-padded six and seven forms. Unknown
    positions are accounted for separately and cannot be counterexamples.
    """
    groups = collections.defaultdict(list)
    unknown = []
    for row in rows:
        key = tuple(feature_value(row, f) for f in features)
        if any(v is None for v in key):
            unknown.append(row)
            continue
        if with_content:
            key += (row['content_id'],)
        groups[key].append(row)
    mixed, cells = [], []
    candidate_groups = multi_function = singleton_sites = 0
    minority_errors = 0
    for key, members in sorted(groups.items(), key=lambda x: repr(x[0])):
        counts = collections.Counter(r['form'] for r in members)
        six, seven = counts['candidate_padded_6'], counts['candidate_padded_7']
        candidates = [r for r in members if r['form'] in ('candidate_padded_6', 'candidate_padded_7')]
        candidate_groups += bool(candidates)
        singleton_sites += len(candidates) == 1
        multi_function += len({r['function'] for r in candidates if r.get('function')}) >= 2
        cell = dict(value=list(key), forms=dict(sorted(counts.items())), sites=len(members))
        cells.append(cell)
        if six and seven:
            a = next(r for r in members if r['form'] == 'candidate_padded_6')
            b = next((r for r in members if r['form'] == 'candidate_padded_7'
                      and r.get('function') != a.get('function')), None)
            b = b or next(r for r in members if r['form'] == 'candidate_padded_7')
            mixed.append(dict(cell, six_example=compact(a), seven_example=compact(b)))
            minority_errors += min(six, seven)
    return dict(features=[f['name'] for f in features], with_identical_content=with_content,
                known_sites=sum(len(v) for v in groups.values()), unknown_sites=len(unknown),
                unknown_forms=dict(collections.Counter(r['form'] for r in unknown)),
                groups=len(groups), candidate_groups=candidate_groups,
                candidate_singleton_sites=singleton_sites,
                candidate_groups_with_multiple_functions=multi_function,
                mixed_groups=len(mixed), mixed_sites=sum(c['sites'] for c in mixed),
                minimum_six_seven_classification_errors=minority_errors,
                counterexamples=mixed[:examples],
                cells=cells if len(cells) <= 64 else None)


def threshold(rows, feature):
    """Best single numeric cut, tested both ways; no claim of causation."""
    groups = collections.defaultdict(collections.Counter)
    unknown = 0
    for row in rows:
        value = feature_value(row, feature)
        if value is None:
            unknown += 1
        else:
            groups[value][row['form']] += 1
    total = sum(groups.values(), collections.Counter())
    six, seven = 'candidate_padded_6', 'candidate_padded_7'
    ordered = sorted(v for v, count in groups.items() if count[six] or count[seven])
    left = collections.Counter()
    best = None
    for value in ordered[:-1]:
        left.update(groups[value]);right=total-left
        for low, high in ((six,seven),(seven,six)):
            errors=left[high]+right[low]
            if best is None or errors < best['errors']:
                best=dict(cut=value, comparison='<=', low_form=low, high_form=high, errors=errors)
    return dict(feature=feature['name'], unknown_sites=unknown,
                candidate_sites=total[six]+total[seven],
                best_constant_errors=min(total[six],total[seven]), best_cut=best)


def content_groups(rows, moduli=MODULI):
    groups = collections.defaultdict(list)
    for row in rows:
        groups[row['content_id']].append(row)
    result = []
    for key, members in sorted(groups.items()):
        forms = {r['form'] for r in members}
        if not {'candidate_padded_6', 'candidate_padded_7'} <= forms:
            continue
        collisions = []
        for modulus in moduli:
            fs = [dict(name=f'pre.linked.{p}.mod{modulus}', geometry='before_candidate_padding',
                       origin='linked', point=p, operation='mod', modulus=modulus) for p in POINTS]
            part = partition(members, fs)
            if part['mixed_groups']:
                collisions.append(dict(modulus=modulus, **{k: part[k] for k in
                                       ('mixed_groups', 'minimum_six_seven_classification_errors', 'counterexamples')}))
        result.append(dict(content_id=key, forms=dict(collections.Counter(r['form'] for r in members)),
                           members=[compact(r) for r in members], linked_pre_padding_collisions=collisions))
    return result


def scope_report(rows, catalog, moduli=MODULI):
    singles = {f['name']: partition(rows, [f]) for f in catalog}
    combinations = {}
    for geometry in GEOMETRIES:
        for modulus in moduli:
            for origin in (*ORIGINS, 'linked_function_tu'):
                origins = ('linked', 'function', 'tu') if origin == 'linked_function_tu' else (origin,)
                fs = [f for f in catalog if f['geometry'] == geometry and f['origin'] in origins
                      and f['operation'] == 'mod' and f['modulus'] == modulus]
                name = f'{geometry}.{origin}.all_points.mod{modulus}'
                combinations[name] = partition(rows, fs)
                if geometry == 'before_candidate_padding':
                    combinations[name+'.identical_content'] = partition(rows, fs, with_content=True)
        combinations[geometry+'.complete_address_tuple'] = partition(
            rows, [f for f in catalog if f['geometry'] == geometry])
        combinations[geometry+'.residues_and_crossings_tuple'] = partition(
            rows, [f for f in catalog if f['geometry'] == geometry and f['operation'] != 'distance'])
    return dict(summary=dict(sites=len(rows), forms=dict(sorted(collections.Counter(r['form'] for r in rows).items())),
                             functions=len({r.get('function') for r in rows if r.get('function')}),
                             tus=len({r.get('tu') for r in rows if r.get('tu')})),
                single_features=singles, combined_features=combinations,
                single_thresholds={f['name']:threshold(rows,f) for f in catalog
                                   if f['operation'] in ('mod','distance')},
                content_identical_counterexamples=content_groups(rows, moduli))


def report(census, tus, libraries, text_base, moduli=MODULI):
    rows = annotate(provenance.annotate(census['loops'], tus, libraries), text_base)
    sn = [r for r in rows if r['sn']]
    simple = [r for r in sn if not r['provenance_ambiguities']]
    high = [r for r in sn if r.get('tu_confidence') in ('exact', 'high')]
    catalog = feature_catalog(moduli)
    scopes = {'sn': sn, 'sn_simple': simple, 'sn_exact_high': high,
              'sn_simple_exact_high': [r for r in high if not r['provenance_ambiguities']]}
    return dict(schema=1, text_base=hex(text_base), moduli=list(moduli),
                feature_definitions=catalog,
                scopes={name: scope_report(selected, catalog, moduli) for name, selected in scopes.items()},
                excluded_non_sn=len(rows)-len(sn), loops=rows,
                caveats=[
                    'Trailing NOPs are padding candidates, not proof they were inserted by an assembler.',
                    'All SN-assigned sites and all unpadded controls remain in the raw scope.',
                    'The simple scope excludes COP0, COP2, inner control and cross-function targets; it does not prove C origin.',
                    'Linked addresses and distances from final .text start are unknown to a relocatable assembler.',
                    'With -ffunction-sections an assembler knows function-section offsets, not eventual function addresses.',
                    'Current source flags do not establish historical -ffunction-sections use.',
                    'TU-relative offsets are a monolithic-input-section hypothesis; even exact TU bounds need not be exact section starts.',
                    'Before-candidate-padding positions subtract only this site\'s candidate NOP count, without changing input bytes.',
                    'Observed multi-endpoint tuples encode emitted loop length; zero collisions there are outcome leakage.',
                    'The complete tuple includes exact text offsets, making each site unique; this is memorization, not an inferred rule.',
                    'Even a single observed branch offset can encode the output length when the loop label is aligned.',
                    'Large moduli and function/TU offsets can produce singleton cells; zero observed collisions is then weak evidence.',
                    'A position correlation alone cannot justify a production patch without a verified static assembler mechanism.'])


def markdown(result):
    lines = ['# Short-loop position study', '',
             'Read-only observations. Six/seven labels are candidate padding, not recovered assembler identities.', '',
             '| Scope | Sites | Six candidates | Seven candidates | Unpadded controls | Other candidate forms |',
             '| --- | ---: | ---: | ---: | ---: | ---: |']
    for name, scope in result['scopes'].items():
        s = scope['summary']; forms = s['forms']
        lines.append('| %s | %d | %d | %d | %d | %d |' % (name, s['sites'], forms.get('candidate_padded_6', 0),
                     forms.get('candidate_padded_7', 0), sum(v for k, v in forms.items() if k.startswith('unpadded_')),
                     sum(v for k,v in forms.items() if k.startswith('candidate_') and k not in
                         ('candidate_padded_6','candidate_padded_7'))))
    lines += ['', 'Complete tuples containing exact text offsets uniquely identify addresses. Observed endpoints also encode',
              'the emitted length. Neither is an input-state rule.', '',
              '| Before candidate padding, all linked/function/TU positions | Raw mixed cells | Simple mixed cells | Simple candidate singleton sites |',
              '| --- | ---: | ---: | ---: |']
    for modulus in result['moduli']:
        key=f'before_candidate_padding.linked_function_tu.all_points.mod{modulus}'
        a=result['scopes']['sn']['combined_features'][key]
        b=result['scopes']['sn_simple']['combined_features'][key]
        lines.append('| mod %d | %d | %d | %d |' % (modulus,a['mixed_groups'],b['mixed_groups'],b['candidate_singleton_sites']))
    lines += ['', 'Concrete simple-loop collisions before candidate padding:', '']
    key='before_candidate_padding.linked_function_tu.all_points.mod256'
    if key not in result['scopes']['sn_simple']['combined_features']:
        key=f'before_candidate_padding.linked_function_tu.all_points.mod{result["moduli"][0]}'
    for c in result['scopes']['sn_simple']['combined_features'][key]['counterexamples']:
        a,b=c['six_example'],c['seven_example']
        lines.append('- Branch `%s` (%s, %s) versus `%s` (%s, %s).' %
                     (a['addr'],a['tu'],a['form'],b['addr'],b['tu'],b['form']))
    lines += ['', 'Limits:', '']+['- '+c for c in result['caveats']]
    return '\n'.join(lines)+'\n'


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',default='build/loop-positions/report.json')
    parser.add_argument('--census',help='reuse an ignored loop_padding classification/provenance JSON')
    args=parser.parse_args()
    if subprocess.run(['git','-C',str(ROOT),'check-ignore','--quiet',args.output],capture_output=True).returncode:
        parser.error('--output must name a Git-ignored path')
    import yaml
    from elfinfo import Elf
    original=Elf((ROOT/'orig/SLUS_213.76/SLUS_213.76').read_bytes())
    mapping=yaml.safe_load((ROOT/'config/tus.yaml').read_text())
    census=json.loads(Path(args.census).read_text()) if args.census else loop_padding.classification()
    result=report(census,mapping['tus'],mapping['libraries'],original.section('.text')['addr'])
    output=Path(args.output);output.parent.mkdir(parents=True,exist_ok=True)
    output.write_text(json.dumps(result,indent=2)+'\n')
    output.with_suffix('.md').write_text(markdown(result))
    print(json.dumps({name:scope['summary'] for name,scope in result['scopes'].items()},indent=2))


if __name__=='__main__':
    main()
