#!/usr/bin/env python3
"""Measure campaign snapshots and large-function gains; output belongs under build/.

  campaign.py snapshot build/waves/wave1.before.json
  campaign.py report BEFORE AFTER [--agent-minutes N] [--attempted LARGE_ADDRESSES.json]

An attempted-address file is a JSON list of integer or hexadecimal function starts.
It records actual hand attempts, not merely functions selected for automatic drafting.
"""
import argparse
import json
import subprocess
import time
from pathlib import Path


def band(size):
    return '<100' if size < 100 else '100-300' if size <= 300 else '>300'


def snapshot():
    import autodecomp
    import yaml
    from units import ROOT
    functions = autodecomp.load_inventory()
    source = autodecomp.source_functions()
    layout = json.loads((ROOT / 'config/SLUS_213.76.layout.json').read_text())
    text = next(s for s in layout['sections'] if s['name'] == '.text')
    spans = {f['addr']: (functions[i + 1]['addr'] if i + 1 < len(functions) else
                        text['addr'] + text['orig_size']) - f['addr'] for i, f in enumerate(functions)}
    real = [f for f in functions if f['size'] > 4 and not autodecomp.is_orphan(f['words'])]
    tus = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())['tus']
    complete = []
    import bisect
    starts = [int(t['text'][0], 0) for t in tus]
    members = {}
    for f in real:
        i = bisect.bisect_right(starts, f['addr']) - 1
        if i >= 0 and f['addr'] < int(tus[i]['text'][1], 0):
            members.setdefault(i, []).append(f['addr'])
    for i, addresses in members.items():
        if tus[i]['kind'] == 'object' and all(a in source for a in addresses):
            complete.append(tus[i]['name'])
    return dict(timestamp=time.time(), revision=subprocess.check_output(
        ['git', 'rev-parse', 'HEAD'], text=True).strip(), text_bytes=text['orig_size'],
        source_functions=len(source), source_bytes=sum(spans.get(a, 0) for a in source),
        source_addresses=sorted(source), functions=[dict(addr=f['addr'], size=f['size'],
        span=spans[f['addr']], band=band(f['size'])) for f in real], complete_code_tus=complete)


def compare(before, after, agent_minutes=0, attempted=None):
    old, new = set(before['source_addresses']), set(after['source_addresses'])
    if old - new:
        raise ValueError('source regressions: ' + ', '.join(hex(a) for a in sorted(old - new)))
    functions = {f['addr']: f for f in before['functions']}
    large = {a for a, f in functions.items() if f['size'] > 300 and a not in old}
    attempts = None if attempted is None else {int(a, 0) if isinstance(a, str) else a for a in attempted}
    if attempts is not None and not attempts <= large:
        raise ValueError('attempted addresses must be previously unmatched functions over 300 bytes')
    bands = {}
    for name in ('<100', '100-300', '>300'):
        addresses = {a for a, f in functions.items() if f['band'] == name}
        eligible = addresses - old
        bands[name] = dict(total=len(addresses), source_before=len(addresses & old),
            source_after=len(addresses & new), newly_matched=len(eligible & new), previously_unmatched=len(eligible))
    gain = after['source_bytes'] - before['source_bytes']
    return dict(new_functions=len(new - old), new_text_bytes=gain,
        gain_percent=100 * gain / before['text_bytes'],
        under_one_percent=gain * 100 < before['text_bytes'],
        new_code_complete_tus=sorted(set(after['complete_code_tus']) - set(before['complete_code_tus'])),
        data_completion='requires separate ownership verification', bands=bands,
        large_new_matches=len(large & new), large_attempted=None if attempts is None else len(attempts),
        large_attempt_matches=None if attempts is None else len(attempts & new),
        bytes_per_agent_hour=None if agent_minutes <= 0 else gain * 60 / agent_minutes)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest='command', required=True)
    snap = sub.add_parser('snapshot')
    snap.add_argument('output', type=Path)
    report = sub.add_parser('report')
    report.add_argument('before', type=Path)
    report.add_argument('after', type=Path)
    report.add_argument('--agent-minutes', type=float, default=0)
    report.add_argument('--attempted', type=Path)
    args = parser.parse_args()
    if args.command == 'snapshot':
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(json.dumps(snapshot(), indent=1))
        print('saved campaign snapshot')
    else:
        attempts = json.loads(args.attempted.read_text()) if args.attempted else None
        print(json.dumps(compare(json.loads(args.before.read_text()), json.loads(args.after.read_text()),
                                 args.agent_minutes, attempts), indent=2))


if __name__ == '__main__':
    main()
