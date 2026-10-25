#!/usr/bin/env python3
"""Linker alias helpers for compiler-owned data and labels referenced by assembly."""
import bisect

def migrated_data_aliases(placement, labels, replaced, layout):
    """Keep names referenced by retained objects when source replaces owned constants.

    Compiler-generated tables usually expose different local names. Their original
    labels retain section-relative positions; full-image comparison still verifies
    every byte and relocation. PROVIDE leaves an explicit source definition intact.
    """
    aliases = []
    addresses = [address for address, _ in labels]
    for section in layout['sections']:
        name = section['name']
        if name not in ('.rodata', '.lit4', '.gcc_except_table'):
            continue
        entries = placement['sections'].get(name, [])
        for index, entry in enumerate(entries):
            owner = entry.get('owner')
            if owner not in replaced:
                continue
            start = entry['key']
            end = entries[index + 1]['key'] if index + 1 < len(entries) else section['addr'] + section['orig_size']
            for address, label in labels[bisect.bisect_left(addresses, start):bisect.bisect_left(addresses, end)]:
                if not label.startswith(('.', '$')):
                    aliases.append('PROVIDE(%s = ADDR(%s) + 0x%X);' %
                                   (label, name, address - section['addr']))
    return aliases


def explicit_data_aliases(ranges, labels, layout):
    """Retain all original labels inside explicitly replaced source storage."""
    bases = {s['name']: s['addr'] for s in layout['sections']}
    return ['PROVIDE(%s = ADDR(%s) + 0x%X);' % (label, r['section'], address - bases[r['section']])
            for r in ranges for address, label in labels
            if r['start'] <= address < r['end'] and not label.startswith(('.', '$'))]


if __name__=='__main__':
    import argparse
    argparse.ArgumentParser(description=__doc__).parse_args()
