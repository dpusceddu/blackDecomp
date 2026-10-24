#!/usr/bin/env python3
"""Verify the shared mod context using real PS2 source consumers and the full image."""
import argparse
import json
from pathlib import Path
import shared_context

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['list', 'verify'])
    args = parser.parse_args()
    config = json.loads((ROOT / 'config/SLUS_213.76/native_header_evidence.json').read_text())
    if config.get('version') != 1:
        raise SystemExit('unsupported mod context version')
    # Instruction-only views are useful context, but never become exact controls
    # merely because a placed function includes their header transitively.
    for view in config.get('instruction_views', []):
        if view.get('source_verified') is not False or not view.get('evidence'):
            raise SystemExit('instruction view needs explicit qualification and evidence')
        if not (ROOT / view['header']).is_file():
            raise SystemExit('missing instruction-view header: ' + view['header'])
    if args.command == 'list':
        for area in config['subsystems']:
            print(area['area'] + ': ' + ', '.join(area['headers']))
        return
    result = shared_context.verify(config)
    result['instruction_only_view_families'] = len(config.get('instruction_views', []))
    output = ROOT / 'build/mod-context/verification.json'
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + '\n')
    print('OK mod context: %d headers, %d exact consumers; %d HEAD source addresses preserved' %
          (result['layers'], len(result['controls']), result['source_addresses_preserved']))


if __name__ == '__main__':
    main()
