#!/usr/bin/env python3
"""Read private PCSX2 savestates in memory; never extract game material to disk.

Prepared from the serialization/layout facts in PCSX2 revision
5b6e6e23eba403b589495c1abf8266eb1309a5b1. No emulator implementation is
embedded. This is an archive/register reader, not yet a validated replay importer.
"""
import argparse
from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import struct
import zipfile

ROOT = Path(__file__).resolve().parents[2]
VERSION = 0x9a590000
REGIONS = {
    'eeMemory.bin':(0,32*1024*1024),
    'Scratchpad.bin':(0x70000000,16*1024),
    'vu0Memory.bin':(0x11004000,4096),
    'vu0MicroMem.bin':(0x11000000,4096),
    'eeHwRegs.bin':(0x10000000,64*1024),
}


def require(condition,message):
    if not condition:
        raise ValueError(message)


def tag_bytes(name):
    return name.encode('ascii').ljust(32,b'\0')


class Reader:
    def __init__(self,data):
        self.data = memoryview(data)
        self.pos = 0

    def take(self,size):
        require(0 <= size <= len(self.data)-self.pos,'truncated savestate register block')
        value = self.data[self.pos:self.pos+size]
        self.pos += size
        return value

    def values(self,fmt):
        return struct.unpack('<'+fmt,self.take(struct.calcsize('<'+fmt)))

    def scalar(self,fmt='I'):
        return self.values(fmt)[0]

    def tag(self,name):
        require(self.take(32) == tag_bytes(name),'unexpected savestate tag; wanted '+name)


def tag_position(data,name,start=0,end=None):
    marker = tag_bytes(name)
    pos = data.find(marker,start,len(data) if end is None else end)
    require(pos >= start,'missing savestate tag '+name)
    require(data.find(marker,pos+1,len(data) if end is None else end) < 0,'ambiguous savestate tag '+name)
    return pos


def cpu_registers(raw):
    # LP64 x86-64/ARM64 layout: the 128-bit storage unions have eight-byte
    # alignment. These are file-format offsets, independent of the host ABI.
    require(len(raw) == 1160,'unexpected EE register structure size')
    r = Reader(raw)
    result = dict(gpr=[list(r.values('4I')) for _ in range(32)],
                  hi=list(r.values('4I')),lo=list(r.values('4I')),cop0=list(r.values('32I')))
    result.update(sa=r.scalar(),delay_slot=r.scalar(),pc=r.scalar(),instruction=r.scalar())
    result['performance'] = list(r.values('4I'))
    r.take(32*4+32*8)
    result['cycle'] = r.scalar('Q')
    result.update(interrupt=r.scalar(),branch=r.scalar('i'),opmode=r.scalar('i'),temporary_cycles=r.scalar(),
                  dma_stall=r.scalar(),pc_writeback=r.scalar())
    result['event_clocks'] = list(r.values('5Q'))
    require(r.pos == len(raw),'EE register layout did not consume its block')
    require(result['gpr'][0] == [0,0,0,0],'EE zero register is inconsistent with the selected format')
    require(result['pc']&3 == 0 and result['delay_slot'] in (0,1),'invalid EE PC/delay state')
    return result


def vu0_registers(reader):
    # Unlike cpuRegs, vuMicroFreeze serializes members separately. There is no
    # padding between the bool/u8 members and the following scalar fields.
    result = dict(acc=list(reader.values('4I')),vf=[list(reader.values('4I')) for _ in range(32)],
                  vi=[list(reader.values('4I')) for _ in range(32)],q=list(reader.values('4I')))
    result['cycle'] = reader.scalar('Q')
    for name in ['flags','instruction','start_pc','branch','branch_pc','delay_branch_pc']:
        result[name] = reader.scalar()
    result['take_delay_branch'] = reader.scalar('B')
    for name in ['ebit','pending_q','pending_p']:
        result[name] = reader.scalar()
    for name in ['micro_mac_flags','micro_clip_flags','micro_status_flags']:
        result[name] = list(reader.values('4I'))
    for name in ['mac_flag','status_flag','clip_flag']:
        result[name] = reader.scalar()
    result['next_block_cycles'] = reader.scalar('q')
    result['vi_backup_cycles'] = reader.scalar('B')
    result['vi_old_value'] = reader.scalar(); result['vi_register_number'] = reader.scalar()
    result['fmac'] = []
    for _ in range(4):
        fields = reader.values('IIiII4xQIIII')
        result['fmac'].append(dict(zip(['upper_register','lower_register','flag_register','upper_mask','lower_mask',
                                       'start_cycle','latency','mac_flag','status_flag','clip_flag'],fields)))
    result['fmac_queue'] = list(reader.values('3I'))
    result['fdiv'] = divider_pipeline(reader,True)
    result['efu'] = divider_pipeline(reader,False)
    result['ialu'] = [dict(zip(['register','start_cycle','latency'],reader.values('i4xQI4x'))) for _ in range(4)]
    result['ialu_queue'] = list(reader.values('3I'))
    require(result['vf'][0] == [0,0,0,0x3f800000] and result['vi'][0][0] == 0,
            'VU0 zero registers are inconsistent with the selected format')
    require(result['take_delay_branch'] in (0,1),'invalid VU0 branch marker')
    require(result['fmac_queue'][2] <= 4 and result['ialu_queue'][2] <= 4,'invalid VU0 pipeline queue length')
    return result


def divider_pipeline(reader,with_status):
    r = Reader(reader.take(40))
    result = dict(enabled=r.scalar('i'),register=list(r.values('4I')))
    r.take(4)  # eight-byte alignment inside the saved structure
    result['start_cycle'] = r.scalar('Q'); result['latency'] = r.scalar()
    if with_status:
        result['status_flag'] = r.scalar()
    return result


def internal_registers(data):
    r = Reader(data)
    r.tag('BIOS'); r.take(4+256)
    crc = r.scalar(); length = r.scalar()
    require(length <= 4096,'invalid saved ELF name length')
    elf_name = bytes(r.take(length)).decode('utf-8',errors='replace')
    executed = r.scalar('B')
    require(executed in (0,1),'invalid saved ELF execution marker')
    r.tag('cpuRegs')
    cpu = cpu_registers(r.take(1160))
    r.take(952)  # IOP registers are retained in the opaque input, never executed.
    fpu = dict(fpr=list(r.values('32I')),fcr=list(r.values('32I')),acc=r.scalar(),acc_overflow_raw=r.scalar())
    tlb = [dict(zip(['page_mask','entry_hi','entry_lo0','entry_lo1'],r.values('4I'))) for _ in range(48)]
    r.take(976)  # PCSX2's derived TLB cache; replay uses the hardware TLB entries.
    cycles = tag_position(data,'Cycles',r.pos,min(len(data),r.pos+1024))
    r.pos = cycles; r.tag('Cycles'); r.take(36); r.tag('EE-Subsystems')
    end = tag_position(data,'IOP-Subsystems',r.pos)
    vu_offset = tag_position(data,'vuMicroRegs',r.pos,end)
    r.pos = vu_offset; r.tag('vuMicroRegs')
    vu_start = r.pos; vu = vu0_registers(r)
    require(r.pos-vu_start == 1570,'VU0 serialized layout size changed')
    require(r.pos+1618 <= end,'missing VU1 register block after VU0')
    # Preserve all internal bytes, including VU1, JIT, VIF and device state.
    # Conversion of backend-specific active pipeline state requires real-state
    # validation; it must never silently become an idle interpreter pipeline.
    return dict(game_crc=crc,elf_name=elf_name,elf_executed=bool(executed),cpu=cpu,fpu=fpu,tlb=tlb,vu0=vu,
                vu0_internal_offset=vu_offset)


@dataclass
class Snapshot:
    sha256: str
    version: int
    emulator_version: str
    regions: dict
    registers: dict
    internals: bytes

    def replay_image(self):
        """Portable bridge to the host interpreter; active pipelines fail closed.

        PCSX2's backend pipeline representation is not interchangeable with the
        harness. Idle VU0 and an EE instruction boundary need no such conversion.
        """
        c, f, v = (self.registers[k] for k in ('cpu','fpu','vu0'))
        require(not c['delay_slot'] and not c['branch'],'saved EE branch needs an explicit continuation')
        require(not (v['vi'][29][0]&1) and not v['ebit'] and not v['branch'] and
                not v['fmac_queue'][2] and not v['ialu_queue'][2] and
                not v['fdiv']['enabled'] and not v['efu']['enabled'],
                'active saved VU0 pipeline is not yet convertible')
        require(f['acc_overflow_raw'] == 0,'saved FPU accumulator overflow needs backend conversion')
        out = bytearray(b'EESNAP01')
        def words(values): out.extend(struct.pack('<'+'I'*len(values),*values))
        words([w for q in c['gpr'] for w in q]+c['hi']+c['lo']+c['cop0']+f['fpr']+f['fcr'])
        words([w for q in v['vf'] for w in q]+[q[0] for q in v['vi']]+v['acc'])
        words([f['acc'],c['pc'],c['sa']]); out.extend(struct.pack('<Q',c['cycle']))
        for entry in self.registers['tlb']:
            words([entry[k] for k in ('page_mask','entry_hi','entry_lo0','entry_lo1')])
        for name in REGIONS: out.extend(self.regions[name])
        return out

    def summary(self):
        vu = self.registers['vu0']
        return dict(sha256=self.sha256,format_version=hex(self.version),emulator_version=self.emulator_version,
                    regions={name:len(data) for name,data in self.regions.items()},
                    ee_pc=hex(self.registers['cpu']['pc']),vu0_busy=bool(vu['vi'][29][0]&1),
                    vu0_fmac_pending=vu['fmac_queue'][2],vu0_ialu_pending=vu['ialu_queue'][2],
                    replay_validated=False,scope='Archive/register extraction only; no execution coverage.')


def load(path):
    path = Path(path)
    with path.open('rb') as stream:
        digest = hashlib.file_digest(stream,'sha256').hexdigest()
    with zipfile.ZipFile(path) as archive:
        names = archive.namelist()
        require(len(names) == len(set(names)),'duplicate savestate archive entries')
        def entry(name,size=None,maximum=64*1024*1024):
            info = archive.getinfo(name)
            require(info.file_size == size if size is not None else info.file_size <= maximum,
                    'unexpected savestate entry size: '+name)
            return archive.read(info)
        version_data = entry('PCSX2 Savestate Version.id',maximum=4096)
        require(len(version_data) >= 4,'missing savestate format version')
        version = struct.unpack_from('<I',version_data)[0]
        require(version == VERSION,f'unsupported PCSX2 savestate format {version:#010x}; documented profile is {VERSION:#010x}')
        emulator = version_data[4:36].split(b'\0',1)[0].decode('utf-8',errors='replace')
        regions = {name:entry(name,size=size) for name,(_,size) in REGIONS.items()}
        internals = entry('PCSX2 Internal Structures.dat')
        registers = internal_registers(internals)
    return Snapshot(digest,version,emulator,regions,registers,internals)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('paths',nargs='*',type=Path)
    parser.add_argument('--output',type=Path)
    args = parser.parse_args()
    paths = args.paths or sorted((ROOT/'orig/savestates').glob('*.p2s'))
    if not paths:
        print('No .p2s files in orig/savestates/. Phase 2 needs real Black savestates.')
        return 2
    rows = []
    for path in paths:
        try:
            row = dict(input=path.name,**load(path).summary())
        except (ValueError,OSError,KeyError,zipfile.BadZipFile,NotImplementedError) as error:
            row = dict(input=path.name,error=str(error),replay_validated=False)
        rows.append(row)
    if args.output:
        require(args.output.resolve().is_relative_to((ROOT/'build').resolve()),'reports must stay under ignored build/')
        args.output.parent.mkdir(parents=True,exist_ok=True)
        args.output.write_text(json.dumps(rows,indent=2)+'\n')
    print(json.dumps(rows,indent=2))
    return int(any('error' in row for row in rows))


if __name__ == '__main__':
    raise SystemExit(main())
