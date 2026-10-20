#!/usr/bin/env python3
"""Verify the shared mod context using real PS2 source consumers and the full image."""
import argparse
import json
from pathlib import Path
import shared_context

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['list', 'verify'])
    args = parser.parse_args()
    config = json.loads((ROOT / 'config/mod_context.json').read_text())
    if config.get('version') != 1:
        raise SystemExit('unsupported mod context version')
    if args.command == 'list':
        for area in config['subsystems']:
            print(area['area'] + ': ' + ', '.join(area['headers']))
        return
    result = shared_context.verify(config)
    output = ROOT / 'build/mod-context/verification.json'
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + '\n')
    print('OK mod context: %d headers, %d exact consumers; %d HEAD source addresses preserved' %
          (result['layers'], len(result['controls']), result['source_addresses_preserved']))


if __name__ == '__main__':
    main()
