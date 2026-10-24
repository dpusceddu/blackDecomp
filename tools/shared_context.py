#!/usr/bin/env python3
"""Verify the shared PS2 inline context against its real source consumers.

Runs ninja through the existing isolated build, checks full-image equality and the
HEAD source-address ledger, then scores each configured consumer with relocations.
No compiler or SDK binary is executed by this process.
"""
import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

import yaml

import autodecomp
import units
import units_verify

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / 'config/shared_context.json'


def source_body(source, name):
    """Select one C/C++ definition, excluding declarations and adjacent methods."""
    # Preserve offsets while excluding comments/string literals from definitions and use checks.
    token = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
    code = token.sub(lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), source)
    match = re.search(r'\b' + re.escape(name) + r'\s*\([^;{}]*\)[^;{}]*\{', code)
    if not match:
        raise ValueError('missing source definition: ' + name)
    start = match.end()
    depth, pos = 1, start
    while depth and pos < len(code):
        depth += (code[pos] == '{') - (code[pos] == '}')
        pos += 1
    if depth:
        raise ValueError('unterminated definition: ' + name)
    return code[start:pos - 1]


def original_source_addresses():
    return units.committed_source_addresses()


def verify(config):
    subprocess.run(['ninja'], cwd=ROOT, check=True)
    built = ROOT / 'build/SLUS_213.76/SLUS_213.76.elf'
    original = ROOT / 'orig/SLUS_213.76/SLUS_213.76'
    if built.read_bytes() != original.read_bytes():
        raise ValueError('the full USA image is not identical')
    all_units = units.load_units()
    owners = {}
    symbols = {}
    for unit in all_units:
        for function in unit['functions']:
            if function.get('symbol'):
                symbols[function['symbol']] = function['addr']
            if function.get('status') == 'source':
                if function['addr'] in owners:
                    raise ValueError('duplicate source address: ' + hex(function['addr']))
                owners[function['addr']] = (unit, function)
    lost = original_source_addresses() - owners.keys()
    if lost:
        raise ValueError('original source addresses lost: ' + ', '.join(map(hex, sorted(lost))))
    inventory = {f['addr']: f for f in autodecomp.load_inventory()}
    image = autodecomp.OrigImage()
    imported = units_verify.bindings()
    results = []
    for control in config['controls']:
        address = int(control['address'], 0)
        if address not in owners:
            raise ValueError('control is not source: ' + control['address'])
        unit, function = owners[address]
        dependencies = {p.as_posix() for p in units.dependencies(unit['source'])}
        for header in control['headers']:
            if header not in dependencies:
                raise ValueError(f'{control["address"]} does not consume {header}')
        body = source_body((ROOT / unit['source']).read_text(), control['source_function'])
        for spelling in control['uses']:
            if spelling not in body:
                raise ValueError(f'{control["address"]} does not use {spelling} in its body')
        obj = units_verify.cached_object(unit['name'])
        if obj is None:
            raise ValueError('missing compiled unit: ' + unit['name'])
        bindings = dict(symbols)
        bindings.update(imported.get(unit['name'], {}))
        bindings.update(unit.get('externs', {}))
        tokens, error = autodecomp.compiled_tokens(obj.data, function['symbol'], bindings=bindings)
        if error or tokens is None:
            raise ValueError(f'{control["address"]}: {error or "missing symbol"}')
        exact, diff, reason = autodecomp.score(autodecomp.Target(inventory[address], image), tokens, image.word)
        if not exact:
            raise ValueError(f'{control["address"]}: {diff} differing instructions ({reason})')
        results.append(dict(address=control['address'], unit=unit['name'], source=unit['source'],
                            symbol=function['symbol'], differing_instructions=0))
    addresses = {r['address'] for r in results}
    for layer in config['layers']:
        if not Path(ROOT / layer['header']).is_file():
            raise ValueError('missing shared header: ' + layer['header'])
        if not layer['controls'] or not set(layer['controls']) <= addresses:
            raise ValueError('layer lacks verified controls: ' + layer['header'])
        for address in layer['controls']:
            control = next(c for c in config['controls'] if c['address'] == address)
            if layer['header'] not in control['headers']:
                raise ValueError('layer/control header coverage is inconsistent')
    return dict(source_addresses_preserved=len(original_source_addresses()),
                current_source_functions=len(owners), full_image_sha256=hashlib.sha256(built.read_bytes()).hexdigest(),
                layers=len(config['layers']), controls=results)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('command', choices=['verify', 'list'])
    args = parser.parse_args()
    config = json.loads(CONFIG.read_text())
    if config.get('version') != 1:
        raise SystemExit('unsupported shared context version')
    if args.command == 'list':
        for layer in config['layers']:
            print(layer['header'] + ': ' + '; '.join(layer['verified_scope']))
        return
    try:
        result = verify(config)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        raise SystemExit(str(error))
    output = ROOT / 'build/shared-context/verification.json'
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2) + '\n')
    print(f'OK shared context: {result["layers"]} headers, {len(result["controls"])} exact consumers; '
          f'{result["source_addresses_preserved"]} HEAD source addresses preserved')


if __name__ == '__main__':
    main()
