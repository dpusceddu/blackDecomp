#!/usr/bin/env python3
"""Run durable, restartable decomp-permuter searches inside the build backend.

The queue contains every saved nonexact draft with 1-29 differing instructions,
including the old pipeline's status=mismatch records. Largest functions run
first. Fetch writes private checkpoints and best sources below build/permuter/.
An exact candidate still needs unit settlement and an identical full-image link.
"""
import argparse
import base64
import contextlib
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import re
import sys
import tarfile
import time
import uuid

sys.path.insert(0, str(Path(__file__).resolve().parent))
import sandbox

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / 'build/permuter'


def parse_bindings(values):
    """Read explicit image symbol addresses without changing compiler names."""
    bindings = {}
    for value in values:
        name, separator, address_text = value.partition('=')
        if not separator or not re.fullmatch(r'[A-Za-z_.$][A-Za-z0-9_.$]*', name):
            raise ValueError('binding must be SYMBOL=ADDRESS')
        try:
            address = int(address_text, 0)
        except ValueError:
            raise ValueError('binding address must be an integer: ' + name) from None
        if not 0 <= address <= 0xffffffff:
            raise ValueError('binding address is outside the EE address space: ' + name)
        if name in bindings and bindings[name] != address:
            raise ValueError('conflicting binding addresses: ' + name)
        bindings[name] = address
    return bindings


def selected_records(results, source_addresses):
    """Select by real instruction count, independently of legacy status names."""
    return sorted(((key, value) for key, value in results.items()
                   if isinstance(value.get('score'), int) and 0 < value['score'] < 30
                   and value.get('source') and int(key, 16) not in source_addresses
                   and value.get('status') not in ('matched', 'fragment', 'orphan')),
                  key=lambda pair: (-pair[1]['size'], pair[1]['score'], int(pair[0], 16)))


def preserve_native_typedefs(source):
    """Keep TI attributes in compiler text while giving the C parser plain types."""
    pattern = r'(?m)^(typedef\s+(?:unsigned\s+)?int\s+(?:s128|u128))\s+__attribute__\(\(mode\(TI\)\)\)\s*;'
    return re.sub(pattern, lambda m: 'PERM_IGNORE(' + m[0] + ')\nPERM_PRETEND(' + m[1] + ';)', source)


def prepare_record(key, record, function, original):
    """Package a candidate and exact target metadata; record parser limits openly."""
    import autodecomp as auto
    constants = {}
    for _, relocation in auto.Target(function, original).tokens:
        if relocation and len(relocation) > 1 and isinstance(relocation[1], int):
            address = relocation[1]
            constants[str(address)] = original.word(address)
    out = dict(key=key, function=function, flags=record['flags'], constants=constants,
               original_source=record['source'], saved_differing_instructions=record['score'],
               scoring_recipe=hashlib.sha256(b''.join((ROOT / 'tools' / name).read_bytes()
                   for name in ('autodecomp.py', 'constant_relocs.py', 'elfinfo.py', 'assembler.py'))).hexdigest())
    if record.get('bindings'):
        out['bindings'] = record['bindings']
    try:
        out['expanded_source'] = auto.expand_macros(record['source'])
        if re.search(r'\b[su]128\b', record['source']):
            out['expanded_source'] = preserve_native_typedefs(out['expanded_source'])
    except (ValueError, OSError, IndexError) as error:
        out.update(expanded_source='', unsupported='source expansion: ' + str(error))
    out['input_hash'] = hashlib.sha256(json.dumps(out, sort_keys=True).encode()).hexdigest()
    return out


def parser_preflight(record):
    """Diagnose unsupported submitted text immediately, without any host SDK use."""
    if record.get('unsupported'):
        return
    import autodecomp as auto
    sys.path.insert(0, str(auto.PERMUTER))
    from src.candidate import Candidate
    from src.helpers import get_default_randomization_weights
    from src.perm.eval import perm_evaluate_one
    from src.perm.parse import perm_parse
    from src.perm.perm import EvalState
    try:
        with contextlib.redirect_stdout(io.StringIO()):
            source = perm_evaluate_one(perm_parse(record['expanded_source']))[0]
            Candidate.from_source(source, EvalState(), record['function']['name'],
                                  get_default_randomization_weights('gcc'), rng_seed=1)
    except Exception as error:
        record['unsupported'] = 'permuter parser: ' + str(error)[:800]
        record['input_hash'] = hashlib.sha256(json.dumps({k: v for k, v in record.items()
            if k != 'input_hash'}, sort_keys=True).encode()).hexdigest()


def source_addresses():
    import yaml
    data = yaml.safe_load((ROOT / 'config/units.yaml').read_text())
    return {int(f['addr'], 0) if isinstance(f['addr'], str) else f['addr']
            for unit in data['units'] for f in unit.get('functions', []) if f.get('status') == 'source'}


def create_queue(args):
    import autodecomp as auto
    inventory = {f['addr']: f for f in auto.load_inventory()}
    original = auto.OrigImage()
    selected = selected_records(auto.load_results(), source_addresses())
    if args.limit:
        selected = selected[:args.limit]
    queue = [prepare_record(k, r, inventory[int(k, 16)], original) for k, r in selected]
    previous_path = OUTPUT / args.name / 'queue.json'
    previous = json.loads(previous_path.read_text()) if previous_path.exists() else {}
    deadline = previous.get('deadline_unix')
    if getattr(args, 'end_at', None):
        from datetime import datetime
        value = datetime.fromisoformat(args.end_at.replace('Z', '+00:00'))
        if value.tzinfo is None:
            raise ValueError('--end-at requires an explicit UTC offset or Z')
        deadline = value.timestamp()
    return dict(queue=queue, integrated_addresses=sorted(hex(addr) for addr in source_addresses()),
                permuter_commit=auto.PERMUTER_COMMIT, seed=args.seed,
                hours_per_function=args.hours_per_function, total_hours=args.total_hours,
                lanes=getattr(args, 'lanes', None) or previous.get('lanes', 1), deadline_unix=deadline)


def package(manifest):
    """Snapshot only text/Python dependencies; no compiler or executable inputs."""
    import autodecomp as auto
    if not auto.PERMUTER.is_dir():
        raise SystemExit('Run tools/autodecomp.py setup first.')
    import subprocess
    commit = subprocess.check_output(['git', '-C', str(auto.PERMUTER), 'rev-parse', 'HEAD'], text=True).strip()
    if commit != auto.PERMUTER_COMMIT:
        raise SystemExit('Permuter checkout differs from the pinned commit; run tools/autodecomp.py setup.')
    files = {}
    for name in ('autodecomp.py', 'elfinfo.py', 'elfobj.py', 'constant_relocs.py', 'build_telemetry.py', 'assembler.py'):
        files['tools/' + name] = (ROOT / 'tools' / name).read_bytes()
    for name in ('ps2/prelude.h', 'types_ghidra.h'):
        path = ROOT / 'include' / name
        if path.exists():
            files['include/' + name] = path.read_bytes()
    for record in manifest['queue']:
        files.update(auto.compile_dependencies(record['original_source']))
    for subtree in ('src', 'perm_pycparser'):
        for path in (auto.PERMUTER / subtree).rglob('*.py'):
            files['vendor/permuter/' + path.relative_to(auto.PERMUTER).as_posix()] = path.read_bytes()
    files['vendor/permuter/default_weights.toml'] = (auto.PERMUTER / 'default_weights.toml').read_bytes()
    spec = importlib.util.find_spec('toml')
    if not spec or not spec.origin:
        raise SystemExit('toml is missing; use the repository virtual environment.')
    module = Path(spec.origin).parent
    for path in module.rglob('*.py'):
        files['vendor/toml/' + path.relative_to(module).as_posix()] = path.read_bytes()
    files['queue.json'] = json.dumps(manifest).encode()
    files['tools/permuter_worker.py'] = (ROOT / 'tools/permuter_worker.py').read_bytes()
    files['tools/permuter_lanes.py'] = (ROOT / 'tools/permuter_lanes.py').read_bytes()
    buffer = io.BytesIO()
    with tarfile.open(fileobj=buffer, mode='w:gz') as archive:
        for name, data in sorted(files.items()):
            item = tarfile.TarInfo(name)
            item.size = len(data)
            archive.addfile(item, io.BytesIO(data))
    return buffer.getvalue()


BOOTSTRAP = '''import json,os,runpy,tarfile,traceback
os.chdir('/work/job')
try:
    with tarfile.open('inputs.tgz') as archive:
        archive.extractall('.')
    runpy.run_path('tools/permuter_worker.py',run_name='__main__')
except BaseException:
    os.makedirs('output',exist_ok=True)
    with open('output/status.json.tmp','w') as stream:
        json.dump({'state':'error','error':traceback.format_exc()},stream)
    os.replace('output/status.json.tmp','output/status.json')
    raise
'''


def unpack_snapshot(blob, destination):
    """Extract regular checkpoint files only, rejecting unsafe archive entries."""
    count = 0
    with tarfile.open(fileobj=io.BytesIO(blob), mode='r:gz') as archive:
        for item in archive.getmembers():
            parts = Path(item.name).parts
            if not parts or parts[0] != 'output' or '..' in parts or Path(item.name).is_absolute():
                raise ValueError('unsafe checkpoint archive path')
            if not item.isfile():
                if not item.isdir():
                    raise ValueError('checkpoint archive contains a link or special file')
                continue
            path = destination.joinpath(*parts[1:])
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(archive.extractfile(item).read())
            count += 1
    return count


def cmd_start(args):
    manifest = create_queue(args)
    destination = OUTPUT / args.name
    destination.mkdir(parents=True, exist_ok=True)
    (destination / 'queue.json').write_text(json.dumps(manifest, indent=1))
    payload = package(manifest)
    reply = sandbox.service_request('start', args.name, files={'inputs.tgz': payload}, script=BOOTSTRAP)
    print(json.dumps(dict(service=args.name, queued=len(manifest['queue']),
                         bytes=sum(r['function']['size'] for r in manifest['queue']),
                         running=reply.get('state', {}).get('Running', False),
                         hours_per_function=args.hours_per_function, total_hours=args.total_hours,
                         lanes=manifest['lanes'], deadline_unix=manifest['deadline_unix'])))


def cmd_snapshot(args):
    reply = sandbox.service_request(args.command, args.name)
    if args.command == 'fetch':
        reply['files'] = unpack_snapshot(reply.pop('archive'), OUTPUT / args.name)
    state = reply.get('state') or {}
    status = reply.get('status')
    if status:
        status = {key: value for key, value in status.items() if key != 'weights'}
        from permuter_worker import retained_wins
        status['permuter_wins'] = sorted(set(status.get('permuter_wins', [])) |
                                        set(retained_wins(OUTPUT / args.name)))
    print(json.dumps(dict(running=state.get('Running', False), exit_code=state.get('ExitCode'),
                         status=status, files=reply.get('files')), indent=1))


def cmd_enqueue(args):
    import autodecomp as auto
    address = int(args.address, 0)
    inventory = {f['addr']: f for f in auto.load_inventory()}
    function = inventory[address]
    source = args.source.read_text()
    saved = auto.load_results().get(hex(address), {})
    flags = args.flags if args.flags else saved.get('flags', auto.BASE_FLAGS)
    disabled = sorted(set(args.disable_randomizer))
    if disabled:
        sys.path.insert(0, str(auto.PERMUTER))
        from permuter_worker import candidate_weights, gcc_weights
        try:
            candidate_weights(gcc_weights(), disabled)
        except ValueError as error:
            raise SystemExit(str(error)) from None
    try:
        bindings = parse_bindings(args.binding)
    except ValueError as error:
        raise SystemExit(str(error)) from None
    obj = auto.worker_compile([('enqueue', source, flags)], tag='permuter-enqueue')['enqueue']
    tokens, reason = auto.compiled_tokens(obj[2], function['name'], bindings=bindings) if obj[0] == 0 and obj[2] else (None, obj[1])
    if tokens is None:
        hint = ('; expose the scratch symbol %s with its exact ABI label; named C++ symbol bindings '
                'are not supported by this enqueue path' % function['name']) if reason == 'function symbol missing' else ''
        raise SystemExit('Candidate did not compile or expose the target: ' + str(reason) + hint)
    original = auto.OrigImage()
    exact, differing, note = auto.score(auto.Target(function, original), tokens, original.word)
    if exact or differing >= 30:
        raise SystemExit('Queue requires 1-29 differing instructions; fresh count is %d.' % differing)
    record = prepare_record(hex(address), dict(source=source, flags=flags, score=differing,
                                              bindings=bindings), function, original)
    if disabled:
        record['disabled_randomizers'] = disabled
    if args.typed_temporaries:
        record['typed_temporaries'] = True
    if args.preserve_search_accounting:
        record['preserve_search_accounting'] = True
    if args.parser_source:
        record['expanded_source'] = args.parser_source.read_text()
        record['parser_override'] = True
        record.pop('unsupported', None)
    record['dependencies'] = {name: base64.b64encode(data).decode()
                              for name, data in auto.compile_dependencies(source).items()}
    record['input_hash'] = hashlib.sha256(json.dumps({k: v for k, v in record.items()
        if k != 'input_hash'}, sort_keys=True).encode()).hexdigest()
    parser_preflight(record)
    record['submitted_unix_ns'] = time.time_ns()
    submission = uuid.uuid4().hex
    destination = OUTPUT / args.name / 'submissions'
    destination.mkdir(parents=True, exist_ok=True)
    (destination / (record['key'] + '-' + submission + '.json')).write_text(json.dumps(record, indent=1))
    reply = sandbox.service_request('submit', args.name, files={submission + '.json': json.dumps(record).encode()})
    print(json.dumps(dict(queued=hex(address), differing_instructions=differing, note=note,
                         unsupported=record.get('unsupported'), running=(reply.get('state') or {}).get('Running', False))))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest='command', required=True)
    for command in ('start', 'status', 'fetch', 'stop', 'enqueue'):
        child = sub.add_parser(command)
        child.add_argument('--name', default='matching')
        if command == 'start':
            child.add_argument('--hours-per-function', type=float, default=2)
            child.add_argument('--total-hours', type=float, default=10)
            child.add_argument('--seed', type=int, default=1)
            child.add_argument('--limit', type=int, help='control runs only; omit for the entire queue')
            child.add_argument('--lanes', type=int, choices=(1, 2, 3), help='disjoint worker lanes within the fixed container resource cap; resumes the prior value, initially 1')
            child.add_argument('--end-at', help='absolute ISO timestamp with timezone; preserved on restart')
            child.set_defaults(function=cmd_start)
        elif command == 'enqueue':
            child.add_argument('address')
            child.add_argument('source', type=Path)
            child.add_argument('--parser-source', type=Path,
                               help='optional PERM_IGNORE/PERM_PRETEND parser seed; original source is compiled first')
            child.add_argument('--binding', action='append', default=[], metavar='SYMBOL=ADDRESS',
                               help='verified image symbol address; repeat before --flags, preserving compiler builtin names')
            child.add_argument('--disable-randomizer', action='append', default=[], metavar='NAME',
                               help='disable an upstream AST transform for this seed only; repeat before --flags')
            child.add_argument('--typed-temporaries', action='store_true',
                               help='retain inferred temporary widths; exclude speculative reuse, local type changes and casts')
            child.add_argument('--preserve-search-accounting', action='store_true',
                               help='reviewed replacement: archive prior best and retain attempts, RNG and function elapsed budget')
            child.add_argument('--flags', nargs=argparse.REMAINDER,
                               help='compiler flags after this option; defaults to saved flags')
            child.set_defaults(function=cmd_enqueue)
        else:
            child.set_defaults(function=cmd_snapshot)
    args = ap.parse_args()
    if args.command == 'start' and (args.hours_per_function <= 0 or args.total_hours <= 0):
        ap.error('hour budgets must be positive')
    args.function(args)


if __name__ == '__main__':
    main()
