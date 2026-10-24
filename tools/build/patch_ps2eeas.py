#!/usr/bin/env python3
"""Reproduce retail's six-word short loops with SN Ps2EeAs 1.9.25.758.

This derivative changes one general rule: the minimum short backward loop is
six words including its branch and delay slot, instead of seven. Two immediate
operands implement that rule: the eligibility threshold and the padding count.
All other assembler behavior, including divbug and FPU hazards, is unchanged.
Never apply this patch to compiler output or game bytes. The original assembler
is retained; both complete binaries and both instruction preimages are checked.

Usage: patch_ps2eeas.py ORIGINAL.exe DERIVATIVE.exe

The guarded derivative approach follows, but does not apply, Lombyte's separate
divbug patch: https://github.com/lombyte-project/lombyte/blob/
65ba28828557887c82cb97716dd1c9aad7da2cf2/scripts/patch-ps2eeas.py
Related SN behavior: https://github.com/ethteck/splat/issues/525 and
https://github.com/OpenRAC/rac3-uya-decomp/blob/
ac0eb2a87cc1706e1d15025f8a17838d17f9175c/tools/asm_filter.py
"""
import argparse
import hashlib
import os
from pathlib import Path
import tempfile


DERIVATIVE_ID = 'ps2eeas-1.9.25.758-min6'
ORIGINAL_SHA256 = 'cb5adda955e64626564212ef7e0c1434708c4e1ef423344a92ec8033306ed3aa'
PATCHED_SHA256 = '4a4bf6f8ae63ee10e4eda6db837a9df4b331b08a71c8f360bb9f0283e84a7813'
PATCHES = (
    (0x4db6, bytes.fromhex('6683fefa'), bytes.fromhex('6683fefb')),
    (0x4de9, bytes.fromhex('8d7006'), bytes.fromhex('8d7005')),
)


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def patch(data):
    """Return the pinned derivative; reject other inputs before changing bytes."""
    if sha256(data) != ORIGINAL_SHA256:
        raise ValueError('input is not the pinned Ps2EeAs 1.9.25.758')
    for offset, before, _ in PATCHES:
        if data[offset:offset + len(before)] != before:
            raise ValueError('unexpected instruction at patch offset %#x' % offset)
    out = bytearray(data)
    for offset, before, after in PATCHES:
        if len(before) != len(after):
            raise ValueError('patch must preserve the assembler file size')
        out[offset:offset + len(before)] = after
    result = bytes(out)
    if sha256(result) != PATCHED_SHA256:
        raise ValueError('patched assembler has an unexpected SHA-256')
    return result


def atomic_write(path, data, mode=0o644):
    """Replace a file atomically within its directory; never leave a partial file."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, name = tempfile.mkstemp(prefix='.' + path.name + '.', dir=path.parent)
    try:
        with os.fdopen(fd, 'wb') as stream:
            stream.write(data)
            stream.flush()
            os.fsync(stream.fileno())
        os.chmod(name, mode)
        os.replace(name, path)
    finally:
        if os.path.exists(name):
            os.unlink(name)


def write_derivative(source, target):
    source, target = Path(source), Path(target)
    if source.resolve() == target.resolve():
        raise ValueError('keep the original assembler; choose a separate output')
    result = patch(source.read_bytes())
    if target.is_symlink():
        raise ValueError('refusing to replace a derivative symlink')
    if target.exists():
        if target.read_bytes() != result:
            raise ValueError('refusing to replace an unexpected derivative file')
        return False
    atomic_write(target, result, 0o755)
    return True


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('source', type=Path)
    parser.add_argument('target', type=Path)
    args = parser.parse_args()
    try:
        changed = write_derivative(args.source, args.target)
    except (ValueError, OSError) as error:
        raise SystemExit(str(error))
    print(DERIVATIVE_ID + (': written' if changed else ': already verified'))


if __name__ == '__main__':
    main()
