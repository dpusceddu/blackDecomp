#!/usr/bin/env python3
"""Compare a retail scalar divide under catalog SN and Sony compiler defaults.

This is an isolated compiler capability control, not a TU compiler-identity claim.
Both compilers run through the build backend. Objects and the measured
ledger remain under ignored build/. Recipe variants are isolated; production
source is never modified.
"""
import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import autodecomp as A


SCALAR_CONTROL = """struct AnimationScaleFields {
    unsigned char reserved[0x60];
    float rootScale, inverseRootScale;
};
typedef char ScaleRoot60[(unsigned)&((AnimationScaleFields*)0)->rootScale == 0x60 ? 1 : -1];
typedef char ScaleInverse64[(unsigned)&((AnimationScaleFields*)0)->inverseRootScale == 0x64 ? 1 : -1];
typedef char ScaleFloat32[sizeof(float) == 4 ? 1 : -1];
extern "C" void func_003484D0(AnimationScaleFields* instance, float value) {
    instance->rootScale = value;
    instance->inverseRootScale = 1.0f / value;
}
"""


def verify(source, output):
    """Check the unchanged leaf and a causal Sony workaround on/off control."""
    inventory = next(f for f in A.load_inventory() if f['addr'] == 0x3484D0)
    image = A.OrigImage()
    text = (source.read_text() if source else SCALAR_CONTROL) + '\n/* divide compiler default control v1 */\n'
    jobs = []
    for compiler in ('ee-gcc2.95.3-136', 'ee-gcc2.9-991111-01'):
        flags = ['--cc=' + compiler, '-O2', '-G0', '-x', 'c++', '-ffunction-sections']
        if compiler == 'ee-gcc2.95.3-136':
            flags.append('-snas')
        jobs.append((compiler, text, flags))
    for enabled in (True, False):
        flag = '-mhandle-ee-div-pipeline-bug' if enabled else '-mno-handle-ee-div-pipeline-bug'
        flags = ['--cc=ee-gcc2.96', '-O2', '-G0', '-x', 'c++', '-ffunction-sections', flag]
        jobs.append(('ee-gcc2.96/' + ('enabled' if enabled else 'disabled'), text, flags))
    guarded = text.replace('    instance->rootScale = value;',
                           '    float one = 1.0f;\n    instance->rootScale = value;').replace(
                               '1.0f / value', 'BkEeDividePipelineGuarded(one, value)')
    header = (ROOT / 'include/ps2/ee_fpu.h').read_text()
    flags = ['--cc=ee-gcc2.95.3-136', '-O2', '-G0', '-x', 'c++', '-ffunction-sections', '-snas']
    jobs.append(('SN-guarded-recipe', header + '\n' + guarded, flags))
    no_guard = header.replace('nop\\n\\tnop\\n\\tdiv.s', 'div.s')
    if no_guard == header:
        raise ValueError('shared divide guard source changed')
    jobs.append(('SN-guard-removed', no_guard + '\n' + guarded, flags))
    compiled = A.worker_compile(jobs, tag='divide-compiler-default-control')
    output.mkdir(parents=True, exist_ok=True)
    rows = []
    for index, (compiler, _, flags) in enumerate(jobs):
        rc, message, obj = compiled[compiler]
        if rc:
            raise ValueError(compiler + ': ' + message)
        tokens, error = A.compiled_tokens(obj, 'func_003484D0')
        if tokens is None:
            raise ValueError(compiler + ': ' + str(error))
        exact, difference, reason = A.score(A.Target(inventory, image), tokens, image.word)
        variant = 'unchanged-scalar' if index < 4 else ('guarded-recipe' if index == 4 else 'guard-removed')
        rows.append(dict(key=compiler, compiler=flags[0].removeprefix('--cc='), flags=flags,
                         source_variant=variant, unchanged_scalar_source=index < 4, exact=exact,
                         differing_instructions=difference, mismatch_class=reason,
                         instruction_count=len(tokens)))
        (output / (compiler.replace('/', '-') + '.o')).write_bytes(obj)
    ledger = dict(address='0x3484d0', source=str(source.relative_to(ROOT)) if source else 'embedded-scalar-control',
                  unchanged_scalar_compiler_controls=4, production_source_modified=False, controls=rows)
    (output / 'results.json').write_text(json.dumps(ledger, indent=2) + '\n')
    measured = [(row['exact'], row['differing_instructions'], row['instruction_count']) for row in rows]
    if measured != [(False, 2, 6), (True, 0, 8), (True, 0, 8), (False, 2, 6), (True, 0, 8), (False, 2, 6)]:
        raise ValueError('compiler-default control changed: ' + str(measured))
    print('All six controls passed: unchanged SN leaf=2, Sony defaults/guarded SN=exact; removing either guard=2.')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, help='optional unchanged scalar leaf source; default is the embedded PS2 access view')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/final-campaign/divide-compiler-control',
                        help='ignored directory for compiler objects and measured ledger')
    args = parser.parse_args()
    verify(args.source.resolve() if args.source else None, args.output.resolve())


if __name__ == '__main__':
    main()
