#!/usr/bin/env python3
"""Read-only short-loop diagnostics. This tool never changes assembly or objects."""
import argparse
import bisect
import collections
import hashlib
import json
from pathlib import Path
import struct
import subprocess


ROOT = Path(__file__).resolve().parents[1]


def branch_offset(word):
    op = word >> 26
    if (op == 1 and word >> 16 & 31 in (0, 1, 2, 3, 16, 17, 18, 19)) or op in (4, 5, 6, 7, 20, 21, 22, 23) or (
            op in (16, 17, 18) and word >> 21 & 31 == 8):
        value = word & 65535
        return value - 65536 if value & 32768 else value
    return None


def loops(tokens):
    words = [t[0] for t in tokens]
    result = []
    for i, word in enumerate(words):
        offset = branch_offset(word)
        if offset is None or offset >= 0:
            continue
        target = i + 1 + offset
        if not 0 <= target <= i:
            continue
        before = 0
        for j in range(i - 1, target - 1, -1):
            if words[j] != 0:
                break
            before += 1
        result.append(dict(branch=i, target=target, displacement=offset,
                           words_including_delay=i + 2 - target,
                           nops_before_branch=before,
                           nops_in_body=sum(w == 0 for w in words[target:i]),
                           delay_nop=i + 1 < len(words) and words[i + 1] == 0))
    return result


def without_padding(tokens):
    """Diagnostic equivalence: preserve CFG targets and every control delay slot.

    NOP deletion here is comparison only. In particular moving a useful delay
    instruction outside a branch cannot be mistaken for harmless padding.
    """
    words = [t[0] for t in tokens]
    ordinals = []
    count = 0
    for word in words:
        ordinals.append(count)
        count += word != 0
    ordinals.append(count)
    result = []
    for i, (word, reloc) in enumerate(tokens):
        if not word:
            continue
        offset = branch_offset(word)
        if offset is not None:
            target = i + 1 + offset
            if not 0 <= target <= len(words):
                return None
            instruction = (word & 0xffff0000, ('branch', ordinals[target]))
        else:
            instruction = word, reloc
        control = offset is not None or word >> 26 in (2, 3) or (
            word >> 26 == 0 and word & 63 in (8, 9))
        delay = tokens[i + 1] if control and i + 1 < len(tokens) else None
        result.append((instruction, delay))
    return result


def padding_equivalent(original, compiled, constant_word):
    a = without_padding(original)
    b = without_padding(compiled)

    def same(x, y):
        if x == y:
            return True
        if x is None or y is None or x[0] != y[0]:
            return False
        for first, second in ((x[1], y[1]), (y[1], x[1])):
            if (first and second and first[0] == second[0] and isinstance(first[1], int)
                    and isinstance(second[1], tuple) and second[1][0] == 'const'):
                return first[0] == 'hi' or constant_word(first[1]) == second[1][2]
        return False
    return (a is not None and b is not None and len(a) == len(b)
            and all(same(x[0], y[0]) and same(x[1], y[1]) for x, y in zip(a, b)))


def is_control(word):
    return (branch_offset(word) is not None or word >> 26 in (2, 3)
            or word >> 26 == 0 and word & 63 in (8, 9))


def instruction_features(words):
    """EE instruction classes, including instructions executed in delay slots."""
    import rabbitizer
    instructions = [rabbitizer.Instruction(w, 0, rabbitizer.InstrCategory.R5900) for w in words]
    names = [i.getOpcodeName() for i in instructions]
    return dict(load=any(i.doesLoad() for i in instructions),
                store=any(i.doesStore() for i in instructions),
                multdiv=any(n.startswith(('mult', 'div', 'madd', 'msub', 'pmult', 'pdiv', 'pmadd', 'pmsub'))
                            for n in names),
                cop1=any(w >> 26 in (17, 49, 53, 57, 61) for w in words),
                cop2=any(w >> 26 in (18, 50, 54, 58, 62) for w in words),
                call=any(i.isFunctionCall() for i in instructions),
                other_branch=any(is_control(w) for w in words))


def candidate_padding(words, target, branch):
    """Count trailing NOPs, excluding any NOP owned by a prior control's delay slot.

    The executable alone cannot distinguish authored NOPs from assembler NOPs.
    This reports a padding candidate, never proof of its production history.
    """
    count = 0
    for i in range(branch - 1, target - 1, -1):
        if words[i] != 0 or i > 0 and is_control(words[i - 1]):
            break
        count += 1
    return count


def sn_compiler(compiler):
    return compiler.startswith(('ee-gcc2.95', 'ee-gcc2.9-991111b'))


def classify_short_loops(words, base, tus, functions=(), source_units=()):
    """Classify every d=-1..-6 branch in a complete .text word stream.

    TU assignments are evidence, not recovered assembler version metadata. A
    matching source recipe takes precedence for the effective compiler, while
    the TU compiler and confidence remain available to audit that choice.
    """
    import rabbitizer
    number = lambda n: int(n, 0) if isinstance(n, str) else n
    tus = sorted(tus, key=lambda t: number(t['text'][0]))
    starts = [number(t['text'][0]) for t in tus]
    functions = sorted(functions, key=lambda f: f['addr'])
    function_starts = [f['addr'] for f in functions]
    matched = {f['addr']: u for u in source_units for f in u['functions'] if f.get('status') == 'source'}
    result = []
    for i, word in enumerate(words):
        displacement = branch_offset(word)
        if displacement is None or not -6 <= displacement < 0:
            continue
        target, address = i + 1 + displacement, base + 4 * i
        if target < 0 or i + 1 >= len(words):
            continue
        k = bisect.bisect_right(starts, address) - 1
        tu = tus[k] if k >= 0 and address < number(tus[k]['text'][1]) else {}
        k = bisect.bisect_right(function_starts, address) - 1
        function = functions[k] if k >= 0 else {}
        if function and address >= function['addr'] + function.get('span', function.get('size', 0)):
            function = {}
        unit = matched.get(function.get('addr'))
        compiler = unit.get('compiler', 'ee-gcc2.95.3-136') if unit else tu.get('compiler', '')
        body, delay = list(words[target:i]), words[i + 1]
        branch = rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900)
        delay_instruction = rabbitizer.Instruction(delay, address + 4, rabbitizer.InstrCategory.R5900)
        padding = candidate_padding(words, target, i)
        row = dict(addr=hex(address), target=hex(base + 4 * target),
                   function=hex(function['addr']) if function else None,
                   region=function.get('region'), tu=tu.get('name'), library=tu.get('library'),
                   tu_compiler=tu.get('compiler'), tu_confidence=tu.get('confidence'),
                   tu_flags_basis=tu.get('flags_basis'), compiler=compiler,
                   compiler_basis='matching-source-recipe' if unit else 'tu-map',
                   source_unit=unit['name'] if unit else None,
                   flags=unit['flags'] if unit else tu.get('flags', []),
                   # Sony-library TU assignments remain excluded even where a
                   # trivial source body happens to match with an SN compiler.
                   sn=sn_compiler(tu.get('compiler', '')) and sn_compiler(compiler),
                   displacement=displacement, length=1 - displacement,
                   padding_nops=padding, padded=padding > 0,
                   padding_basis='candidate trailing NOPs; authored padding is indistinguishable',
                   body_non_nop=sum(w != 0 for w in body),
                   branch=branch.getOpcodeName(), likely=branch.isBranchLikely(),
                   delay=delay_instruction.disassemble(), delay_word=delay,
                   delay_op=delay_instruction.getOpcodeName(),
                   words=[hex(w) for w in words[target:i + 2]],
                   body_features=instruction_features(body))
        row.update(instruction_features(body + [delay]))
        # An inner control is distinct from the backward branch being studied.
        row['other_branch'] = row['body_features']['other_branch']
        result.append(row)
    return result


def summarize_classification(rows):
    """Aggregate evidence and strict identical-non-NOP-body counterexamples."""
    summaries = {}
    for label, selected in (('all', rows), ('sn', [r for r in rows if r['sn']]),
                            ('excluded', [r for r in rows if not r['sn']])):
        lengths = collections.Counter((r['length'], r['padded']) for r in selected)
        summaries[label] = dict(branches=len(selected), candidate_padded=sum(r['padded'] for r in selected),
                                unpadded=sum(not r['padded'] for r in selected),
                                lengths=[dict(length=n, padded=p, count=count)
                                         for (n, p), count in sorted(lengths.items())])
    sn = [r for r in rows if r['sn']]
    features = {}
    for feature in ('library', 'compiler_basis', 'tu_confidence', 'branch', 'likely', 'load', 'store',
                    'multdiv', 'cop1', 'cop2', 'call', 'other_branch', 'delay_op', 'body_non_nop'):
        counts = collections.Counter((str(r.get(feature)), r['padded']) for r in sn)
        features[feature] = [dict(value=value, padded=padded, count=count)
                             for (value, padded), count in sorted(counts.items())]
    groups = collections.defaultdict(list)
    for row in sn:
        words = [int(w, 16) for w in row['words']]
        # Preserve every register, immediate, call address and delay instruction;
        # only the studied branch displacement and NOP words are disregarded.
        key = tuple(w for w in words[:-2] if w) + (words[-2] & 0xffff0000, words[-1])
        groups[key].append(row)
    examples = []
    for key, members in groups.items():
        if len({r['padding_nops'] for r in members}) <= 1:
            continue
        examples.append(dict(id=hashlib.sha256(repr(key).encode()).hexdigest()[:16],
                             different_lengths=len({r['length'] for r in members}) > 1,
                             branches=[dict(addr=r['addr'], tu=r['tu'], library=r['library'],
                                            length=r['length'], padding_nops=r['padding_nops']) for r in members]))
    return dict(note='NOPs are padding candidates; bytes cannot establish whether they were authored. '
                     'Matching-source compiler recipes do not prove the historical compiler.',
                summary=summaries, sn_features=features, content_counterexamples=examples, loops=rows)


def classification():
    """Read retail inputs only. No compiler, assembler or output mutation."""
    import autodecomp as auto
    from units import load_units
    import yaml
    original = auto.OrigImage().e
    text = original.section('.text')
    words = list(struct.unpack('<%dI' % (text['size'] // 4), original.content(text)))
    tus = yaml.safe_load((ROOT / 'config/tus.yaml').read_text())['tus']
    return summarize_classification(classify_short_loops(words, text['addr'], tus,
                                                       auto.load_inventory(), load_units()))


def main():
    import autodecomp as auto
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output')
    parser.add_argument('--classify', action='store_true', help='classify retail short loops by SN-region evidence')
    args = parser.parse_args()
    if args.classify:
        if args.output:
            ignored = subprocess.run(['git', '-C', str(ROOT), 'check-ignore', '--quiet', args.output],
                                     capture_output=True)
            if ignored.returncode:
                parser.error('--classify --output must name a Git-ignored path')
        result = classification()
        if args.output:
            output = Path(args.output)
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_text(json.dumps(result, indent=2) + '\n')
        print(json.dumps(dict(summary=result['summary'],
                              content_counterexample_groups=len(result['content_counterexamples']),
                              length_counterexample_groups=sum(g['different_lengths']
                                                               for g in result['content_counterexamples'])), indent=2))
        return
    counts = collections.Counter()
    nop_counts = collections.Counter()
    affected = set()
    for function in auto.load_inventory():
        for loop in loops(auto.Target(function, None).tokens):
            counts[-loop['displacement']] += 1
            if -loop['displacement'] <= 6:
                nop_counts[(str(-loop['displacement']), str(loop['nops_before_branch']))] += 1
                if -loop['displacement'] <= 5:
                    affected.add(function['addr'])
    result = dict(backward_branches=sum(counts.values()),
                  short_branches=sum(v for k, v in counts.items() if k <= 5),
                  short_functions=len(affected), displacement_counts=dict(sorted(counts.items())),
                  short_nops={','.join(k): v for k, v in sorted(nop_counts.items())})
    if args.output:
        with open(args.output, 'w') as stream:
            json.dump(result, stream, indent=2)
    print(json.dumps({k: v for k, v in result.items() if k != 'displacement_counts'}, indent=2))


if __name__ == '__main__':
    main()
