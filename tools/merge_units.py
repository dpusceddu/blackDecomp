#!/usr/bin/env python3
"""Regenerate disjoint unit edits during merges/rebases with the owning serializer.

  merge_units.py BASE OURS THEIRS

Arguments are Git revisions. Overlapping edits fail before writing; source/header
conflicts must be resolved before settling. Regenerate tus.yaml with tus.py all.
"""
import sys as _sys
if __name__ == '__main__' and _sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    raise SystemExit(0)
import copy
import subprocess
import sys

import yaml


def records(units):
    result = {}
    for original in units:
        unit = copy.deepcopy(original)
        name = unit['name']
        if name in result:
            raise ValueError('duplicate unit name: ' + name)
        unit.setdefault('compiler', 'ee-gcc2.95.3-136')
        unit.setdefault('flags', ['-O2', '-G0', '-snas'])
        unit['externs'] = {k: int(v, 0) if isinstance(v, str) else v for k, v in unit.get('externs', {}).items()}
        for function in unit['functions']:
            if isinstance(function['addr'], str):
                function['addr'] = int(function['addr'], 0)
        result[name] = unit
    return result


def equivalent(left, right):
    """Assembly claims may acquire inventory sizes without changing ownership.

    Source sizes affect placement and must remain part of the comparison.
    Keep the original records for output; normalize only the comparison views.
    """
    def view(unit):
        if unit is None:
            return None
        result = copy.deepcopy(unit)
        for function in result['functions']:
            if function.get('status') == 'asm':
                function.pop('size', None)
        return result
    return view(left) == view(right)


def merge(base_units, our_units, their_units):
    base, ours, theirs = map(records, (base_units, our_units, their_units))
    result = copy.deepcopy(ours)
    for name in dict.fromkeys([*base, *theirs]):
        before, left, right = base.get(name), ours.get(name), theirs.get(name)
        if equivalent(right, before):
            continue
        if not equivalent(left, before) and not equivalent(left, right):
            raise ValueError('overlapping unit edit requires ownership review: ' + name)
        if right is None:
            result.pop(name, None)
        else:
            result[name] = copy.deepcopy(right)
    source = {}
    for unit in result.values():
        for function in unit['functions']:
            if function.get('status') == 'source':
                address = function['addr']
                if address in source:
                    raise ValueError('duplicate source address: ' + hex(address))
                source[address] = unit['name']
    return list(result.values())


def read_revision(ref):
    text = subprocess.check_output(['git', 'show', ref + ':config/units.yaml'], text=True)
    return yaml.safe_load(text)['units']


def main():
    if len(sys.argv) != 4:
        raise SystemExit(__doc__)
    from units_verify import save
    units = merge(*(read_revision(ref) for ref in sys.argv[1:]))
    save(units)
    print('regenerated %d unit records; run settle_units.py and tus.py all' % len(units))


if __name__ == '__main__':
    main()
