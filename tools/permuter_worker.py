#!/usr/bin/env python3
"""Worker-only durable decomp-permuter search with relocation-aware PS2 scores.

Run through tools/permuter_service.py and tools/sandbox.py, never directly on the
host. A manifest and packaged pure-Python dependencies live in /work/job; every
best candidate, RNG state and elapsed budget is checkpointed under output/.
"""
import argparse
import base64
import hashlib
import json
import os
from pathlib import Path
import random
import signal
import shutil
import subprocess
import sys
import time


def atomic_json(path, value):
    """Replace one checkpoint atomically so concurrent snapshots stay readable."""
    temp = path.with_suffix(path.suffix + '.tmp')
    temp.write_text(json.dumps(value, indent=1, sort_keys=True))
    temp.replace(path)


def tuple_state(value):
    """Restore Random's tuple tree from JSON lists."""
    return tuple(tuple_state(x) for x in value) if isinstance(value, list) else value


def candidate_tokens(auto, obj, record):
    """Use the same explicit symbol bindings for baselines and every mutation."""
    return auto.compiled_tokens(obj, record['function']['name'], bindings=record.get('bindings'))


def target_declarator(candidate):
    """Freeze the target return/parameter types while allowing local mutations.

    Upstream's internal-type visitor also reaches parameter declarations despite
    its documented exclusion. Zero function-type weight alone does not freeze
    the interface. Parameter spelling and source coordinates are immaterial.
    """
    function = next(node for node in candidate.ast.ext
                    if type(node).__name__ == 'FuncDef' and node.decl.name == candidate.fn_name)

    def freeze(value):
        if isinstance(value, (list, tuple)):
            return tuple(freeze(item) for item in value)
        return value

    def shape(node):
        attributes = tuple((name, freeze(getattr(node, name))) for name in node.attr_names
                           if name != 'declname' and not (type(node).__name__ == 'Decl'
                                                         and name in ('name', 'storage')))
        return (type(node).__name__, attributes,
                tuple((name, shape(child)) for name, child in node.children()))

    return shape(function.decl.type)


def inert_declaration(node):
    """Allow uninitialized declarations without VLA/type-side evaluations."""
    if type(node).__name__ != 'Decl' or node.init is not None:
        return False

    def constant_bound(expression):
        kind = type(expression).__name__
        if kind == 'Constant':
            return True
        if kind == 'UnaryOp' and expression.op in ('+', '-', '~', '!'):
            return constant_bound(expression.expr)
        if kind == 'BinaryOp':
            return constant_bound(expression.left) and constant_bound(expression.right)
        return False

    def safe_type(part):
        kind = type(part).__name__
        if kind in ('FuncCall', 'Assignment') or (kind == 'UnaryOp' and part.op in ('p++', 'p--', '++', '--')):
            return False
        if kind == 'ArrayDecl' and part.dim is not None and not constant_bound(part.dim):
            return False
        return all(safe_type(child) for _, child in part.children())

    return safe_type(node.type)


def protected_prefix(candidate):
    """Identify an opaque initial body whose real definitions must run first."""
    function = next(node for node in candidate.ast.ext
                    if type(node).__name__ == 'FuncDef' and node.decl.name == candidate.fn_name)
    for node in function.body.block_items or ():
        if type(node).__name__ == 'Pragma':
            if node.string.startswith('_permuter b64literal '):
                return node.string
        elif not inert_declaration(node):
            return None
    return None


def prefix_preserved(candidate, expected):
    """Reject executable mutations moved before an initial opaque source block."""
    return expected is None or protected_prefix(candidate) == expected


def rebase_abi_best(state, directory):
    """Archive an interface-drifted best, preserving its search clock and RNG."""
    archive = directory / 'rejected-abi' / str(time.time_ns())
    archive.mkdir(parents=True)
    for name in ('best.c', 'best.o', 'best.permuter.c', 'best.repository.c'):
        source = directory / name
        if source.exists():
            shutil.copyfile(source, archive / name)
    (directory / 'best.repository.c').unlink(missing_ok=True)
    atomic_json(archive / 'state.json', state)
    for field in ('best_source', 'best_parser_source', 'best_rank', 'object_sha256',
                  'differing_instructions', 'note'):
        state.pop(field, None)
    state['abi_rebases'] = state.get('abi_rebases', 0) + 1
    state['last_abi_rejection'] = 'saved target declarator differs from submitted baseline'
    return archive


def refresh_record_state(record, state, directory=None):
    """Start a changed seed, optionally retaining reviewed search accounting.

    A reviewed refresh replaces the search root, never its accumulated budget.
    Archive the prior source/object/state before discarding its candidate rank.
    """
    refreshed = dict(state='queued', tried=0, elapsed_seconds=0,
                     input_hash=record['input_hash'], size=record['function']['size'],
                     saved_differing_instructions=record['saved_differing_instructions'],
                     parser_override=bool(record.get('parser_override')))
    if record.get('preserve_search_accounting') and state.get('input_hash'):
        for field in ('tried', 'elapsed_seconds', 'rng_state'):
            if field in state:
                refreshed[field] = state[field]
        refreshed['seed_refreshes'] = state.get('seed_refreshes', 0) + 1
        if directory is not None:
            archive = directory / 'reviewed-seeds' / str(time.time_ns())
            archive.mkdir(parents=True)
            for name in ('baseline.c', 'best.c', 'best.o', 'best.permuter.c', 'best.repository.c'):
                source = directory / name
                if source.exists():
                    shutil.copyfile(source, archive / name)
            atomic_json(archive / 'state.json', state)
            # A historical exact repository form must not describe the new seed.
            (directory / 'best.repository.c').unlink(missing_ok=True)
            refreshed['previous_seed_archive'] = str(archive.relative_to(directory))
    return refreshed


def ingest_submissions(records, inbox):
    """Replay accepted and pending submissions after restart, newest per address.

    Accepted receipts are durable inputs, not disposable acknowledgments. Replaying
    the same ordered receipts is idempotent and preserves a submitted seed even
    when queue.json still contains its older automatic draft.
    """
    incoming = [(path, json.loads(path.read_text())) for suffix in ('*.accepted', '*.json')
                for path in inbox.glob(suffix)]
    for path, record in sorted(incoming, key=lambda item: (item[1].get('submitted_unix_ns', 0), item[0].stem)):
        records[record['key']] = record
        if path.suffix == '.json':
            path.rename(path.with_suffix('.accepted'))


def larger_queued(records, states, active):
    """New larger functions preempt at a checkpoint; unsupported work never does."""
    size = records[active]['function']['size']
    return any(state['state'] == 'queued' and records[key]['function']['size'] > size
               for key, state in states.items() if key != active)


def reconcile_integrated(state, key, integrated_addresses):
    """Retain winning evidence but retire submissions since integrated by hand."""
    if key not in integrated_addresses or state.get('state') in ('exact', 'integrated'):
        return False
    state.update(state='integrated', reason='source is already exact in the current unit manifest')
    return True


def retained_wins(output):
    """Recover genuine improvements to exact, including retired queue entries."""
    path = output / 'wins.json'
    wins = json.loads(path.read_text()) if path.exists() else {}
    for path in output.glob('*/state.json'):
        state = json.loads(path.read_text())
        baseline = state.get('baseline_rank', [0])
        digest = state.get('object_sha256')
        legacy_object = path.parent / 'best.o'
        if not digest and state.get('state') == 'exact' and legacy_object.exists():
            digest = hashlib.sha256(legacy_object.read_bytes()).hexdigest()
        if state.get('state') == 'exact' and baseline[0] > 0 and digest:
            wins[path.parent.name] = {key: state.get(key) for key in
                ('size', 'baseline_rank', 'best_rank', 'object_sha256', 'tried', 'elapsed_seconds')}
            wins[path.parent.name]['object_sha256'] = digest
    return wins


def restore_dependencies(record):
    """Restore a submitted seed's quoted-header snapshot inside its worker job."""
    for name, data in record.get('dependencies', {}).items():
        path = Path(name)
        if path.is_absolute() or '..' in path.parts or not path.parts or path.parts[0] != 'include':
            raise ValueError('submitted dependency must be below include/')
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(base64.b64decode(data))


def compile_one(source, flags, compiler):
    """Use the same catalog driver/assembler recipe as build_job.py."""
    from assembler import compile_with_assembler
    from elfobj import normalize_object
    root = Path('/toolchains/compilers') / compiler
    src, obj = Path('candidate.c'), Path('candidate.o')
    src.write_text(source)
    obj.unlink(missing_ok=True)
    env = dict(os.environ, TMPDIR='/tmp', WINEDEBUG='-all')
    if (root / 'bin/ee-gcc.exe').is_file():
        versions = root / 'lib/gcc-lib/ee'
        backend = next(x for x in sorted(versions.iterdir()) if x.is_dir() and not x.name.startswith('.'))
        env['WIBO_PATH'] = str(backend)
        prefix = ['wibo', str(root / 'bin/ee-gcc.exe'), '-B' + str(backend) + '/']
    elif compiler.startswith('mwcps2-'):
        prefix = ['wibo', str(root / 'mwccps2.exe')]
    else:
        prefix = [str(root / 'bin/ee-gcc'), '-B' + str(root / 'bin/ee-')]
    try:
        p = compile_with_assembler(prefix, flags + ['-I', 'include'], str(src), str(obj), env, 30)
    except subprocess.TimeoutExpired:
        return None, 'compiler timeout'
    if p.returncode or not obj.exists():
        return None, (p.stdout + p.stderr)[-1200:]
    data = normalize_object(obj.read_bytes())
    obj.unlink(missing_ok=True)
    Path('candidate.o.s').unlink(missing_ok=True)
    return data, ''


def gcc_weights():
    """Use upstream GCC weights; emphasize declarations/lifetimes for SN search.

    Speculative external type mutations are disabled: changing a callee ABI to
    improve a score is unsuitable for this queue. Artificial identical arms,
    empty statements and constant-condition wrappers are also excluded. A full-image match is
    still required before any candidate can replace assembly.
    """
    from src.helpers import get_default_randomization_weights
    weights = dict(get_default_randomization_weights('gcc'))
    weights.update(perm_temp_for_expr=120, perm_expand_expr=35,
                   perm_reorder_stmts=25, perm_reorder_decls=35,
                   perm_inline=20, perm_remove_var=15, perm_split_assignment=20,
                   perm_randomize_external_type=0, perm_randomize_function_type=0,
                   perm_var_cond_block=0, perm_empty_stmt=0, perm_ins_block=0)
    return weights


def candidate_weights(weights, disabled=(), typed_temporaries=False):
    """Apply explicit per-seed search exclusions without changing other lanes."""
    result = dict(weights)
    if typed_temporaries:
        # This mode keeps inferred expression widths. Explicit casts and local
        # type randomization would defeat that scoped guarantee.
        for name in ('perm_randomize_internal_type', 'perm_cast_simple'):
            if name in result:
                result[name] = 0
    for name in disabled:
        if name not in result:
            raise ValueError('unknown randomizer: ' + name)
        result[name] = 0
    if not any(value > 0 for value in result.values()):
        raise ValueError('at least one randomizer must remain enabled')
    return result


def randomize_candidate(candidate, rounds, typed_temporaries=False):
    """Keep temporary creation useful while optionally freezing inferred types.

    Each lane is a separate process. Restore upstream globals even on failure,
    so a later unqualified seed retains the upstream search distribution. This
    excludes speculative narrowing/reuse; it is not a semantic proof.
    """
    if not typed_temporaries:
        for _ in range(rounds):
            candidate.randomize_ast()
        return
    import src.randomizer as randomizer
    previous = randomizer.PROB_RANDOMIZE_TYPE, randomizer.PROB_REUSE_VAR
    try:
        randomizer.PROB_RANDOMIZE_TYPE = 0
        randomizer.PROB_REUSE_VAR = 0
        for _ in range(rounds):
            candidate.randomize_ast()
    finally:
        randomizer.PROB_RANDOMIZE_TYPE, randomizer.PROB_REUSE_VAR = previous


def rank(exact, differing, tokens, target):
    """Keep instruction count separate from a bit-distance tie breaker."""
    bits = sum(bin(a[0] ^ b[0]).count('1') for a, b in zip(tokens, target.tokens))
    return (0, 0) if exact else (differing, bits)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--work', type=Path, default=Path('/work/job'))
    ap.add_argument('--output', type=Path, default=Path('output'))
    ap.add_argument('--status-file', type=Path)
    ap.add_argument('--no-wins-index', action='store_true', help='supervisor owns the shared win index')
    a = ap.parse_args()
    if not Path('/toolchains/compilers').is_dir():
        raise SystemExit('Worker-only tool: launch it through tools/permuter_service.py.')
    os.chdir(a.work)
    sys.path[:0] = [str(a.work / 'tools'), str(a.work / 'vendor'), str(a.work / 'vendor/permuter')]
    import autodecomp as auto
    from src.candidate import Candidate
    from src.perm.eval import perm_evaluate_one
    from src.perm.parse import perm_parse
    from src.perm.perm import EvalState
    from src.ast_util import to_c_raw
    output = a.output
    output.mkdir(exist_ok=True)
    status_path = a.status_file or output / 'status.json'
    status_path.parent.mkdir(parents=True, exist_ok=True)
    wins = retained_wins(output)
    manifest = json.loads(Path('queue.json').read_text())
    if manifest.get('lanes', 1) > 1:
        from permuter_lanes import supervise
        supervise(a.work, manifest)
        return
    records = {r['key']: r for r in manifest['queue']}
    integrated_addresses = set(manifest.get('integrated_addresses', []))
    weights = gcc_weights()
    stop = [False]
    for sig in (signal.SIGTERM, signal.SIGINT):
        signal.signal(sig, lambda *_: stop.__setitem__(0, True))
    started = time.monotonic()
    old_status = json.loads(status_path.read_text()) if status_path.exists() else {}
    past_seconds = old_status.get('elapsed_seconds', 0)
    total_budget = manifest['total_hours'] * 3600
    states = {}

    def status(state='running', active=None):
        counts = {}
        for value in states.values():
            key = value.get('state', 'queued')
            counts[key] = counts.get(key, 0) + 1
        atomic_json(status_path, dict(
            state=state, active=active, queue=len(records), counts=counts,
            elapsed_seconds=past_seconds + time.monotonic() - started,
            container_wall_seconds=past_seconds + time.monotonic() - started,
            total_budget_seconds=total_budget,
            candidates=sum(x.get('tried', 0) for x in states.values()),
            exact_candidates=sorted(set(wins) | {k for k, v in states.items() if v.get('state') == 'exact'}),
            permuter_wins=sorted(wins),
            improved=[k for k, v in states.items() if v.get('best_rank', [10**9]) < v.get('baseline_rank', [10**9])],
            updated_unix=time.time(), permuter_commit=manifest['permuter_commit'],
            weights=weights))

    def save(key, state, source=None, parser_source=None):
        directory = output / key
        directory.mkdir(exist_ok=True)
        if source is not None:
            state['best_source'] = source
            temp = directory / 'best.c.tmp'
            temp.write_text(source)
            temp.replace(directory / 'best.c')
        if parser_source is not None:
            state['best_parser_source'] = parser_source
            temp = directory / 'best.permuter.c.tmp'
            temp.write_text(parser_source)
            temp.replace(directory / 'best.permuter.c')
        atomic_json(directory / 'state.json', state)
        states[key] = state
        if state.get('state') == 'exact' and state.get('baseline_rank', [0])[0] > 0:
            wins[key] = {field: state.get(field) for field in
                ('size', 'baseline_rank', 'best_rank', 'object_sha256', 'tried', 'elapsed_seconds')}
            if not a.no_wins_index:
                atomic_json(output / 'wins.json', wins)

    def save_object(directory, state, obj):
        temp = directory / 'best.o.tmp'
        temp.write_bytes(obj)
        temp.replace(directory / 'best.o')
        state['object_sha256'] = hashlib.sha256(obj).hexdigest()

    def ingest():
        ingest_submissions(records, Path('inbox'))
        for key, record in records.items():
            path = output / key / 'state.json'
            state = states.get(key)
            if state is None:
                state = json.loads(path.read_text()) if path.exists() else {}
                if state.get('state') == 'running':
                    state['state'] = 'queued'
            elif state.get('input_hash') == record['input_hash']:
                if reconcile_integrated(state, key, integrated_addresses):
                    save(key, state)
                continue
            if state.get('input_hash') != record['input_hash']:
                state = refresh_record_state(record, state, output / key)
            if record.get('unsupported'):
                state.update(state='unsupported', reason=record['unsupported'])
            elif state['state'] == 'budget-exhausted' and state['elapsed_seconds'] < manifest['hours_per_function'] * 3600:
                state['state'] = 'queued'
            reconcile_integrated(state, key, integrated_addresses)
            save(key, state)

    def budget_finished():
        return past_seconds + time.monotonic() - started >= total_budget or (
            manifest.get('deadline_unix') is not None and time.time() >= manifest['deadline_unix'])

    while not stop[0] and not budget_finished():
        ingest()
        pending = sorted((k for k, s in states.items() if s['state'] in ('queued', 'running')),
                         key=lambda k: (-records[k]['function']['size'], records[k]['saved_differing_instructions'], k))
        if not pending:
            status('complete')
            return
        key = pending[0]
        record, state = records[key], states[key]
        typed_temporaries = record.get('typed_temporaries', False)
        search_weights = candidate_weights(weights, record.get('disabled_randomizers', ()),
                                           typed_temporaries)
        state['disabled_randomizers'] = record.get('disabled_randomizers', [])
        state['typed_temporaries'] = typed_temporaries
        directory = output / key
        target = auto.Target(record['function'], None)
        constants = record['constants']
        const_word = lambda addr: constants.get(str(addr))
        compiler, flags = auto.split_cc(record['flags'])
        rng = random.Random(manifest['seed'] ^ record['function']['addr'])
        if state.get('rng_state'):
            rng.setstate(tuple_state(state['rng_state']))
        try:
            restore_dependencies(record)
            original_expanded = perm_evaluate_one(perm_parse(record['expanded_source']))[0]
            original_candidate = Candidate.from_source(original_expanded, EvalState(),
                record['function']['name'], search_weights, rng_seed=1)
            original_declarator = target_declarator(original_candidate)
            original_prefix = protected_prefix(original_candidate)
            source = state.get('best_parser_source') or state.get('best_source') or ((directory / 'best.c').read_text()
                     if state.get('best_rank') and (directory / 'best.c').exists() else original_expanded)
            base_candidate = Candidate.from_source(source, EvalState(), record['function']['name'], search_weights, rng_seed=1)
            if target_declarator(base_candidate) != original_declarator:
                rebase_abi_best(state, directory)
                source, base_candidate = original_expanded, original_candidate
            compiled_source = base_candidate.get_source()
        except Exception as error:
            state.update(state='unsupported', reason='permuter parser: ' + str(error)[:800])
            save(key, state)
            status(active=key)
            continue
        block_started = time.monotonic()
        elapsed_before = state.get('elapsed_seconds', 0)
        state['state'] = 'running'
        if state.get('best_rank') and (not state.get('object_sha256') or not (directory / 'best.o').exists()):
            obj, error = compile_one(compiled_source, flags, compiler)
            tokens, reason = candidate_tokens(auto, obj, record) if obj else (None, error)
            if tokens is None:
                state.update(state='compile-failed', reason='saved best source: ' + str(reason))
                save(key, state)
                continue
            exact, differing, note = auto.score(target, tokens, const_word)
            state.update(best_rank=list(rank(exact, differing, tokens, target)),
                         differing_instructions=differing, note=note)
            save_object(directory, state, obj)
            save(key, state, compiled_source, parser_source=source)
        if not state.get('best_rank'):
            obj, error = compile_one(compiled_source, flags, compiler)
            tokens, reason = candidate_tokens(auto, obj, record) if obj else (None, error)
            if tokens is None:
                state.update(state='compile-failed', reason=reason)
                save(key, state)
                continue
            exact, differing, note = auto.score(target, tokens, const_word)
            baseline = list(rank(exact, differing, tokens, target))
            state.update(baseline_rank=baseline, best_rank=baseline, differing_instructions=differing,
                         note=note, revalidated=True)
            save_object(directory, state, obj)
            (directory / 'baseline.c').write_text(record['original_source'])
            if exact:
                state['state'] = 'exact'
                (directory / 'best.repository.c').write_text(compiled_source if record.get('parser_override')
                                                           else auto.committed_form(compiled_source))
            elif differing >= 30:
                state.update(state='outside-threshold', reason='fresh baseline has at least 30 differing instructions')
            save(key, state, compiled_source, parser_source=source)
        checkpoint = time.monotonic()
        while state['state'] == 'running' and not stop[0]:
            elapsed = elapsed_before + time.monotonic() - block_started
            if elapsed >= manifest['hours_per_function'] * 3600:
                state['state'] = 'budget-exhausted'
                break
            if budget_finished():
                break
            # Alternate shallow changes with longer jumps, restarting from the
            # original source periodically rather than accumulating only quirks.
            base = original_expanded if state['tried'] and state['tried'] % 97 == 0 else source
            try:
                candidate = Candidate.from_source(base, EvalState(), record['function']['name'],
                                                  search_weights, rng_seed=rng.randrange(1, 2**63))
                randomize_candidate(candidate, rng.choice((1, 1, 2, 3, 5, 8)),
                                    typed_temporaries)
                if target_declarator(candidate) != original_declarator:
                    state['abi_rejections'] = state.get('abi_rejections', 0) + 1
                    raise ValueError('target return/parameter declarator mutation rejected')
                if not prefix_preserved(candidate, original_prefix):
                    state['prefix_rejections'] = state.get('prefix_rejections', 0) + 1
                    raise ValueError('executable mutation moved before protected source prefix')
                text = candidate.get_source()
            except Exception as error:
                state['randomization_errors'] = state.get('randomization_errors', 0) + 1
                state['last_error'] = str(error)[:300]
                # Still charge failed randomizations to the deterministic stream.
                state['tried'] += 1
                if time.monotonic() - checkpoint >= 5:
                    state.update(rng_state=rng.getstate(), elapsed_seconds=elapsed)
                    save(key, state); status(active=key); checkpoint = time.monotonic()
                continue
            state['tried'] += 1
            obj, error = compile_one(auto.Climb.plain(text), flags, compiler)
            tokens, _ = candidate_tokens(auto, obj, record) if obj else (None, error)
            if tokens is not None:
                exact, differing, note = auto.score(target, tokens, const_word)
                candidate_rank = list(rank(exact, differing, tokens, target))
                if candidate_rank < state['best_rank']:
                    source = to_c_raw(candidate.ast)
                    compiled_source = text
                    state.update(best_rank=candidate_rank, differing_instructions=differing, note=note,
                                 improvements=state.get('improvements', 0) + 1,
                                 rng_state=rng.getstate(),
                                 elapsed_seconds=elapsed_before + time.monotonic() - block_started)
                    save_object(directory, state, obj)
                    if exact:
                        state['state'] = 'exact'
                        (directory / 'best.repository.c').write_text(text if record.get('parser_override')
                                                                   else auto.committed_form(text))
                    save(key, state, compiled_source, parser_source=source)
            else:
                state['compile_errors'] = state.get('compile_errors', 0) + 1
                state['last_error'] = error[:300]
            if time.monotonic() - checkpoint >= 5 or state['state'] == 'exact':
                state.update(rng_state=rng.getstate(), elapsed_seconds=elapsed_before + time.monotonic() - block_started)
                save(key, state)
                ingest()
                status(active=key); checkpoint = time.monotonic()
                if records[key]['input_hash'] != record['input_hash']:
                    break
                if larger_queued(records, states, key):
                    state['state'] = 'queued'
                    break
        if records[key]['input_hash'] != record['input_hash']:
            continue
        state.update(rng_state=rng.getstate(), elapsed_seconds=elapsed_before + time.monotonic() - block_started)
        save(key, state, compiled_source, parser_source=source)
        status(active=key)
    status('stopped' if stop[0] else 'budget-exhausted')


if __name__ == '__main__':
    main()
