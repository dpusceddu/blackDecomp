#!/usr/bin/env python3
"""Batch source experiments with the owning recipe, changed-instruction diffs and a local hypothesis history.

Usage: trysrc.py ADDR SOURCE.c|cpp ... [--hypothesis TEXT] [--quiet]
       trysrc.py ADDR --history

Each input is a complete candidate, including needed declarations and helpers.
Uses the owner's compiler, flags, assembler and named-symbol bindings. --flags
replaces its flags; --variants explicitly explores the pipeline's flag sets.
Use --non-matching for complete TUs containing NON_MATCHING drafts. C++ is
inferred from each input or its owner unless -x selects a language explicitly.
The compiled function defaults to the image symbol; --symbol overrides it.

Sources, scores, context hashes and the best source/object/diff of each run stay
under build/experiments/ADDR/. History is diagnostic and never reused as proof.
Compilation uses the existing dependency-aware worker cache. No sources are
adopted and no progress is recorded. An object match still needs source review
and the full-image check. Exit 0: an object match; 1: near misses; 2: no score.
"""
import argparse
from datetime import datetime, timezone
import difflib
import hashlib
import json
import os
from pathlib import Path
import shlex
import sys
import tempfile

sys.path[:0] = [str(Path(__file__).resolve().parent / d) for d in ('', 'build', 'pipeline', 'maint')]
import preflight
from splits import group_splits, load_splits, load_symbols

ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / 'build/experiments'


def digest(value):
    return hashlib.sha256(value).hexdigest()


def json_hash(value):
    return digest(json.dumps(value, sort_keys=True).encode())


def address(value):
    try:
        return int(value.removeprefix('func_'), 16)
    except ValueError:
        raise argparse.ArgumentTypeError('expected a hexadecimal function address')


def source_recipe(owner, source, flags=None, variants=False):
    """Resolve a candidate's recipe from a single metadata snapshot per batch."""
    language = 'c++' if Path(source).suffix in ('.cpp', '.cc', '.cxx', '.C') or Path(owner.src).suffix == '.cpp' else 'c'
    if variants:
        return None, language
    selected = list(flags) if flags is not None else owner.compile_flags()
    if not any(f.startswith('--cc=') for f in selected):
        selected.insert(0, '--cc=' + owner.compiler)
    return selected, language


def symbol_bindings(symbols, owner):
    """Use real names and per-owner overrides; ambiguous names and aliases cannot prove a relocation."""
    overrides = owner.extra.get('externs', {})
    return {name: addr for name in symbols.by_name.keys() | overrides.keys()
            if (addr := symbols.address(name, overrides)) is not None}


def changed_instructions(want, got, start):
    """Show changed spans only, including unresolved relocation operands."""
    import rabbitizer
    def text(token, pc):
        word, relocation = token
        instruction = rabbitizer.Instruction(word, pc, rabbitizer.InstrCategory.R5900).disassemble()
        return instruction + (' ' + repr(relocation) if relocation else '')
    lines = []
    matcher = difflib.SequenceMatcher(None, list(map(repr, want)), list(map(repr, got)), autojunk=False)
    for tag, i, end, j, last in matcher.get_opcodes():
        if tag == 'equal':
            continue
        lines.append('@@ original word %d / candidate word %d @@' % (i, j))
        lines.extend('- %08X  %s' % (start + k * 4, text(want[k], start + k * 4)) for k in range(i, end))
        lines.extend('+ word %-4d %s' % (k, text(got[k], 0)) for k in range(j, last))
    return '\n'.join(lines) + ('\n' if lines else '')


def run_batch(function, candidates, context, bindings, hypothesis, output, symbol=None):
    """Compile and score all variants together, then preserve the complete experiment under a content hash."""
    import autodecomp as A
    original = A.OrigImage()
    target = A.Target(function, original)
    jobs, attempts = [], []
    for index, (path, source, flags) in enumerate(candidates):
        dependencies = A.compile_dependencies(source)
        attempts.append(dict(source=str(path), source_sha256=digest(source.encode()),
                             dependencies={name: digest(data) for name, data in dependencies.items()}, flags=flags))
        jobs.append((index, source, flags))
    context = dict(context, bindings_sha256=json_hash(bindings),
                   target_sha256=json_hash(dict(words=function['words'], rel=function['rel'])),
                   image_sha256=digest(original.e.data))
    identity = dict(context=context, hypothesis=hypothesis, attempts=attempts, symbol=symbol or function['name'])
    compiled = A.worker_compile(jobs, tag='trysrc')
    results, best, best_tokens = [], None, None
    for index, (path, source, flags) in enumerate(candidates):
        rc, message, obj = compiled[index]
        entry = dict(attempts[index], candidate=index, status='compile-failed', message=message)
        if rc == 0:
            entry['object_sha256'] = digest(obj)
            tokens, reason = A.compiled_tokens(obj, symbol or function['name'], bindings=bindings)
            if tokens is None:
                entry.update(status='unscored', message=reason)
            else:
                matches, differences, kind = A.score(target, tokens, original.word)
                entry.update(status='object-match' if matches else 'near', differences=differences, kind=kind,
                             words=len(tokens), code_sha256=json_hash(dict(tokens=tokens, resolved=tokens.resolved_words)))
                if best is None or differences < results[best]['differences']:
                    best, best_tokens = index, tokens
        results.append(entry)
    # A changed outcome (including a transient failure) preserves the earlier best too.
    fingerprint = json_hash(dict(inputs=identity, results=results))
    directory = output / ('%08X' % function['addr']) / fingerprint[:20]
    previous = (directory / 'results.json').exists()
    record = dict(version=1, fingerprint=fingerprint, inputs_sha256=json_hash(identity),
                  created=datetime.now(timezone.utc).isoformat(),
                  **identity, results=results, best=best,
                  distinct_code=len({r['code_sha256'] for r in results if 'code_sha256' in r}))
    # Each run keeps its own best: a worse later hypothesis cannot overwrite it.
    directory.mkdir(parents=True, exist_ok=True)
    for index, (path, source, flags) in enumerate(candidates):
        (directory / ('candidate-%03d%s' % (index, Path(path).suffix))).write_text(source)
    if best is not None:
        flags = candidates[best][2]
        suffix = '.cpp' if '-x' in flags and flags[flags.index('-x') + 1] == 'c++' else '.c'
        (directory / ('best' + suffix)).write_text(candidates[best][1])
        (directory / 'best.o').write_bytes(compiled[best][2])
        diff = changed_instructions(target.tokens, best_tokens, function['addr']) if results[best]['differences'] else ''
        (directory / 'diff.txt').write_text(diff)
    # History readers must never see a partly written record.
    with tempfile.NamedTemporaryFile(mode='w', dir=directory, delete=False) as temporary:
        try:
            json.dump(record, temporary, indent=2)
            temporary.write('\n')
            temporary.close()
            os.replace(temporary.name, directory / 'results.json')
        finally:
            Path(temporary.name).unlink(missing_ok=True)
    return record, directory, previous


def history(addr, output):
    records = [json.loads(p.read_text()) for p in (output / ('%08X' % addr)).glob('*/results.json')]
    for record in sorted(records, key=lambda r: r['created']):
        best = record['best']
        result = record['results'][best] if best is not None else None
        summary = '%d differences' % result['differences'] if result else 'no score'
        print('%s  %s: %s; %d variants, %d distinct code outputs [%s]' % (
            record['created'], record['hypothesis'], summary, len(record['results']),
            record['distinct_code'], record['fingerprint'][:20]))
    if not records:
        print('No experiments recorded for %08X.' % addr)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('addr', type=address)
    ap.add_argument('source', nargs='*', type=Path)
    ap.add_argument('--flags', help="replace the owner's flags")
    ap.add_argument('--variants', action='store_true', help="explicitly try the pipeline's flag variants")
    ap.add_argument('--non-matching', action='store_true', help='compile NON_MATCHING bodies in complete TUs')
    ap.add_argument('--symbol', help='compiled function symbol, if different from the image symbol')
    ap.add_argument('--hypothesis', default='source variants', help='what this batch is testing')
    ap.add_argument('--history', action='store_true', help='show prior hypotheses without compiling or requiring game files')
    ap.add_argument('--output', type=Path, default=OUTPUT, help='artifact/history directory (default: build/experiments)')
    ap.add_argument('--quiet', action='store_true', help='suppress the best candidate diff')
    args = ap.parse_args(argv)
    if args.history:
        if args.source:
            ap.error('--history does not take source files')
        history(args.addr, args.output)
        return 0
    if not args.source:
        ap.error('provide at least one candidate source, or use --history')
    if args.flags is not None and args.variants:
        ap.error('--flags and --variants are mutually exclusive')
    preflight.require()
    import autodecomp as A
    function = next((f for f in A.load_inventory() if f['addr'] == args.addr), None)
    if function is None:
        ap.error('address is not in the function inventory')
    groups = group_splits(load_splits())
    owner = next((g[0] for g in groups if any(s.start <= args.addr < s.end for s in g)), None)
    if owner is None:
        ap.error('address has no source owner')
    bindings = symbol_bindings(load_symbols(), owner)
    candidates = []
    override_flags = shlex.split(args.flags) if args.flags is not None else None
    variant_sets = None
    if args.variants:
        variant_sets = A.variants_for(function)
        variant_sets += [flags for flags in A.extra_sets(function) if flags not in variant_sets]
    for path in args.source:
        try:
            source = path.read_text()
        except OSError as error:
            ap.error(str(error))
        flags, language = source_recipe(owner, path, override_flags, args.variants)
        sets = [flags] if flags is not None else variant_sets
        for flags in sets:
            flags = list(flags)
            if '-x' not in flags:
                flags += ['-x', language]
            if args.non_matching and '-DNON_MATCHING' not in flags:
                flags.append('-DNON_MATCHING')
            candidates.append((path, source, flags))
    context = dict(owner=owner.src, owner_sha256=digest((ROOT / owner.src).read_bytes()),
                   tools={p: digest((ROOT / p).read_bytes()) for p in (
                       'tools/trysrc.py', 'tools/autodecomp.py', 'tools/compile.py', 'tools/build/assembler.py',
                       'tools/build/object_compile.py', 'tools/build/elfinfo.py', 'tools/build/constant_relocs.py')})
    record, directory, previous = run_batch(function, candidates, context, bindings, args.hypothesis, args.output, args.symbol)
    print('%s: %s (%d variants)' % (function['name'], args.hypothesis, len(record['results'])))
    if previous:
        print('This batch was already recorded with the same sources and context; scores have been refreshed.')
    for index, result in enumerate(record['results']):
        outcome = ('%d differences (%s)' % (result['differences'], result['kind'] or 'object match')
                   if 'differences' in result else result['status'] + ': ' + result['message'])
        print('  %d %s: %s' % (index, result['source'], outcome))
    print('%d distinct code outputs; results: %s' % (record['distinct_code'], directory))
    if record['best'] is None:
        return 2
    best = record['results'][record['best']]
    print('Best: variant %d, %d differences; source and object saved.' % (record['best'], best['differences']))
    print('Recipe: %s' % shlex.join(best['flags']))
    if not args.quiet:
        print((directory / 'diff.txt').read_text(), end='')
    if best['differences'] == 0:
        print('Object match is a candidate; review the source and verify the full image before counting progress.')
    return 0 if best['differences'] == 0 else 1


if __name__ == '__main__':
    preflight.guard(lambda: sys.exit(main()))
