#!/usr/bin/env python3
"""Read-only short-loop diagnostics. This tool never changes assembly or objects."""
import argparse
import collections
import json


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


def main():
    import autodecomp as auto
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output')
    args = parser.parse_args()
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
