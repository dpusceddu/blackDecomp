#!/usr/bin/env python3
"""Reproduce a fixed private calibration set against the isolated compiler catalog.

A manifest is a JSON list of {addr, symbol, source, flags, bindings, control, area}.
Sources, manifests, objects and detailed results belong under ignored build/.
The grid is factorial for optimization, scheduling, aliasing, GP and bool width;
inline limits, frame pointers and EE switches are additional controlled contrasts.
No candidate is registered or linked by this tool.
"""
import sys as _sys
from pathlib import Path as _Path
_sys.path[:0] = [str(_Path(__file__).resolve().parents[1] / _d) for _d in ('', 'build', 'pipeline', 'maint')]  # the core tools
import argparse
import hashlib
import itertools
import json
from pathlib import Path
import time

import autodecomp as auto


def flag_grid(compiler):
    if compiler.startswith('mwcps2-'):
        # Catalog coverage beyond the GCC family: use its actual option syntax.
        return [['-O' + opt, '-sdatathreshold', gp, '-inline', inline]
                for opt, gp, inline in itertools.product(('2', '3', 's'), ('0', '8'), ('on', 'off'))]
    rows = []
    scheduling = ([], ['-fno-schedule-insns'], ['-fno-schedule-insns2'],
                  ['-fno-schedule-insns', '-fno-schedule-insns2'])
    for opt, sched, alias, gp, boolean in itertools.product(
            ('-O2', '-O3', '-Os'), scheduling, ([], ['-fno-strict-aliasing']),
            ('-G0', '-G8'), ([], ['-fbyte-bool'])):
        rows.append([opt, gp] + sched + alias + boolean)
    switches = ['-finline-limit-100', '-finline-limit-600', '-finline-limit-2000', '-fno-inline',
                '-fno-omit-frame-pointer', '-mno-gpopt', '-mno-split-addresses', '-mno-mad',
                '-mno-check-zero-division', '-mno-check-range-division', '-mno-memcpy',
                '-mno-fix4300', '-mno-abicalls']
    for opt, switch in itertools.product(('-O2', '-O3', '-Os'), switches):
        rows.append([opt, '-G0', switch])
    # SN's assembler changes hazard/short-loop padding; test both assemblers.
    if compiler.startswith(('ee-gcc2.95.2-', 'ee-gcc2.95.3-')):
        rows = [row + assembler for row in rows for assembler in ([], ['-snas'])]
    return list(dict.fromkeys(tuple(row) for row in rows))


def invariant_flags(flags, compiler=''):
    out = []
    i = 0
    while i < len(flags):
        flag = flags[i]
        if flag == '-x':
            out += (['-lang', flags[i + 1]] if compiler.startswith('mwcps2-') else flags[i:i + 2])
            i += 2
            continue
        if flag.startswith(('-D', '-U')) or (not compiler.startswith('mwcps2-')
                and (flag.startswith('-mvu0-') or flag == '-ffunction-sections')):
            out.append(flag)
        i += 1
    return out


def evaluate(row, obj, original, inventory, compiler=''):
    symbol = row['symbol']
    bindings = dict(row.get('bindings', {}))
    for prefix, alias in row.get('compiler_symbols', {}).items():
        if compiler.startswith(prefix):
            symbol = alias
    for prefix, aliases in row.get('compiler_bindings', {}).items():
        if compiler.startswith(prefix):
            bindings.update(aliases)
    bindings[symbol] = int(row['addr'], 0)
    tokens, reason = auto.compiled_tokens(obj, symbol, bindings=bindings)
    if tokens is None:
        return dict(error=reason)
    exact, differences, kind = auto.score(auto.Target(inventory[int(row['addr'], 0)], original), tokens, original.word)
    return dict(exact=exact, differences=differences, kind=kind, compiled_bytes=4 * len(tokens))


def run(manifest, output, batch=80, baseline_only=False, compilers=()):
    rows = json.loads(manifest.read_text())
    catalog = json.loads((auto.ROOT / 'config/toolchain-compilers.json').read_text())['compilers']
    if compilers:
        known = {row['id'] for row in catalog}
        if set(compilers) - known:
            raise ValueError('unknown compiler selection')
        catalog = [row for row in catalog if row['id'] in compilers]
    inventory = {fn['addr']: fn for fn in auto.load_inventory()}
    original = auto.OrigImage()
    output.mkdir(parents=True, exist_ok=True)
    results_path = output / ('baseline.jsonl' if baseline_only else 'grid.jsonl')
    previous = {}
    if results_path.exists():
        previous = {r['key']: r for line in results_path.read_text().splitlines() if (r := json.loads(line))}
    jobs, metadata = [], {}
    for row in rows:
        source = Path(row['source']).read_text()
        source_hash = hashlib.sha256(source.encode()).hexdigest()
        context = hashlib.sha256(auto.PRELUDE_HASH.encode())
        for name, data in sorted(auto.compile_dependencies(source).items()):
            context.update(name.encode() + b'\0' + data)
        context_hash = context.hexdigest()
        configs = [(auto.split_cc(row['flags'])[0], row['flags'])] if baseline_only else [
            (cc['id'], ['--cc=' + cc['id']] + invariant_flags(row['flags'], cc['id']) + list(flags))
            for cc in catalog for flags in flag_grid(cc['id'])]
        for cc, flags in configs:
            digest = hashlib.sha256(json.dumps([row['addr'], row['symbol'], source_hash, context_hash, flags,
                                                row.get('bindings', {}), row.get('compiler_symbols', {}),
                                                row.get('compiler_bindings', {})], sort_keys=True).encode()).hexdigest()[:24]
            if digest in previous:
                continue
            jobs.append((digest, source, flags))
            metadata[digest] = dict(key=digest, addr=row['addr'], symbol=row['symbol'], source_hash=source_hash,
                                    context_hash=context_hash, compiler=cc, flags=flags,
                                    control=row.get('control', False), area=row['area'])
    print('pending candidates:', len(jobs), flush=True)
    started = time.time()
    by_addr = {row['addr']: row for row in rows}
    with results_path.open('a') as destination:
        for offset in range(0, len(jobs), batch):
            chunk = jobs[offset:offset + batch]
            compiled = auto.worker_compile(chunk, 'large-study-baseline' if baseline_only else 'large-study-grid')
            for key, _, _ in chunk:
                rc, message, obj = compiled[key]
                record = metadata[key]
                record.update(rc=rc)
                if rc:
                    record['error'] = message
                else:
                    record.update(evaluate(by_addr[record['addr']], obj, original, inventory, record['compiler']))
                destination.write(json.dumps(record, sort_keys=True) + '\n')
            destination.flush()
            print('scored %d/%d, %.1fs' % (min(offset + batch, len(jobs)), len(jobs), time.time() - started), flush=True)
    (output / ('baseline-telemetry.json' if baseline_only else 'grid-telemetry.json')).write_text(
        json.dumps(dict(auto.STATS), indent=1))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('manifest', type=Path)
    parser.add_argument('--output', type=Path, default=Path('build/large-study/results'))
    parser.add_argument('--batch', type=int, default=80)
    parser.add_argument('--baseline-only', action='store_true')
    parser.add_argument('--compiler', action='append', default=[], help='restrict to a catalog compiler (repeatable)')
    args = parser.parse_args()
    run(args.manifest, args.output, args.batch, args.baseline_only, args.compiler)


if __name__ == '__main__':
    main()
