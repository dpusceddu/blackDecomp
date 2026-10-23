#!/usr/bin/env python3
"""Cross-check every original .text word; report decoding and execution separately."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
from elfinfo import Elf
import rabbitizer
from vu0_micro import UPLOADS, lower as reference_vu_lower


def canonical(instruction):
    name = instruction.getOpcodeName()
    if name == 'c1':
        name = instruction.uniqueId.name.split('__', 1)[-1].replace('_', '.')
    if name.startswith(('qmfc2.', 'qmtc2.', 'cfc2.', 'ctc2.')):
        name = name.split('.')[0]
    if name in ('sync.p', 'sync.l'):
        name = 'sync'
    if name == 'nop':
        name = 'sll'
    return name


def audit(executable, elf_path):
    rabbitizer.config.pseudos_enablePseudos = False
    elf = Elf(elf_path.read_bytes())
    text = elf.section('.text')
    if not text or text['size'] % 4:
        raise ValueError('missing or non-word-aligned .text')
    data = elf.content(text)
    decoded = subprocess.run([str(executable), 'decode'], input=data, capture_output=True, check=True).stdout.decode().splitlines()
    if len(decoded) != len(data) // 4:
        raise ValueError('decoder output does not cover every .text word')
    names = collections.Counter()
    unsupported = collections.Counter()
    mismatches, invalid = [], []
    for index, ((word,), row) in enumerate(zip(struct.iter_unpack('<I', data), decoded)):
        address = text['addr'] + 4*index
        name, supported = row.split('\t')
        instruction = rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900)
        other = canonical(instruction)
        names[name] += 1
        if supported != '1':
            unsupported[name] += 1
        detail = dict(address=hex(address), word=hex(word), harness=name, rabbitizer=other)
        if not instruction.isValid():
            invalid.append(detail)
        elif name != other:
            mismatches.append(detail)
    return dict(words=len(decoded), distinct_opcodes=len(names),
                harness_sha256=hashlib.sha256(executable.read_bytes()).hexdigest(),
                reference_sha256=hashlib.sha256(elf.data).hexdigest(),
                decoded_words=sum(count for name, count in names.items() if name != 'reserved'),
                execution_supported_words=len(decoded)-sum(unsupported.values()),
                unsupported_opcodes=dict(unsupported.most_common()),
                decoder_mismatch_count=len(mismatches), decoder_mismatches=mismatches,
                rabbitizer_invalid_count=len(invalid), rabbitizer_invalid=invalid,
                rabbitizer_version=rabbitizer.__version__,
                vu_uploads=audit_vu(executable,elf),
                gate_1='not evaluated by this individual check',
                limitations=['Decoder agreement is not execution validation.',
                             'EE/VU integration uses a deterministic issue-clock profile; full EE timing and broader COP1/VU flag validation remain unfinished. TLB-backed execution is implemented.',
                             'No function is promoted to equivalent by this audit.'])


def audit_vu(executable,elf):
    section = elf.section('.vutext')
    if not section:
        return []
    contents = elf.content(section)
    reports = []
    for upload in UPLOADS:
        data,addresses = bytearray(),[]
        for address,dest,size in upload['payloads']:
            offset = address-section['addr']
            if offset < 0 or offset+size > len(contents):
                raise ValueError('VU upload outside .vutext')
            data += contents[offset:offset+size]
            addresses += [dest+i for i in range(0,size,8)]
        rows = subprocess.run([str(executable),'decode-vu'],input=data,capture_output=True,check=True).stdout.decode().splitlines()
        if len(rows) != len(addresses):
            raise ValueError('incomplete VU decoding stream')
        mismatches,unsupported,invalid_upper = [],[],0
        for (lo,hi),address,row in zip(struct.iter_unpack('<II',data),addresses,rows):
            up,down,supported = row.split('\t')
            instruction = rabbitizer.Instruction(0x4a000000 | (hi&0x1ffffff),0,rabbitizer.InstrCategory.R5900)
            if instruction.isValid():
                if instruction.getOpcodeName() != up:
                    mismatches.append(dict(pc=hex(address),half='upper',harness=up,reference=instruction.getOpcodeName()))
            else:
                invalid_upper += 1
            other = reference_vu_lower(lo,bool(hi&0x80000000))[0].lower()
            normalized = down[1:] if down.startswith('v') else down
            if other != normalized:
                mismatches.append(dict(pc=hex(address),half='lower',harness=down,reference=other))
            if supported != '1' or up == 'reserved':
                unsupported.append(hex(address))
        reports.append(dict(name=upload['name'],pairs=len(rows),sha256=hashlib.sha256(data).hexdigest(),
                            decoder_mismatches=mismatches,unsupported=unsupported,rabbitizer_invalid_upper=invalid_upper,
                            scope='Known VU0 upload instruction decoding; execution agreement is checked separately.'))
    return reports


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--harness', type=Path, default=ROOT / 'build/eeharness/host/eeharness')
    parser.add_argument('--elf', type=Path, default=ROOT / 'orig/usa-retail/files/SLUS_213.76')
    parser.add_argument('--output', type=Path, default=ROOT / 'build/eeharness/decode-audit.json')
    args = parser.parse_args()
    if not args.output.resolve().is_relative_to((ROOT / 'build').resolve()):
        parser.error('reports must stay under ignored build/')
    report = audit(args.harness, args.elf)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print('Audited {words:,} words; {decoder_mismatch_count:,} mnemonic disagreements; '
          '{rabbitizer_invalid_count:,} words invalid to rabbitizer; '
          '{execution_supported_words:,} words have execution handlers.'.format(**report))
    print('Individual check only; run gate1.py for the combined functional gate.')
    for upload in report['vu_uploads']:
        print('VU0 %s: %d pairs, %d decoder disagreements, %d unsupported.' % (
            upload['name'],upload['pairs'],len(upload['decoder_mismatches']),len(upload['unsupported'])))
    return bool(report['decoder_mismatch_count'] or any(u['decoder_mismatches'] or u['unsupported'] for u in report['vu_uploads']))


if __name__ == '__main__':
    raise SystemExit(main())
