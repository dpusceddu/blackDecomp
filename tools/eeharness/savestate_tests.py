#!/usr/bin/env python3
"""Synthetic file-format checks; these are not real savestate validation."""
from pathlib import Path
import struct
import tempfile
import unittest
import zipfile

import savestate


def fixture():
    # Independent literal offsets from the documented 64-bit PCSX2 format.
    cpu = bytearray(1160)
    struct.pack_into('<4I',cpu,31*16,1,2,3,4)
    struct.pack_into('<I',cpu,544+12*4,0x70000000)
    struct.pack_into('<I',cpu,680,0x100000)
    struct.pack_into('<Q',cpu,1088,12345)
    fpu = bytearray(264)
    struct.pack_into('<I',fpu,4*7,0x3f800000)
    struct.pack_into('<II',fpu,256,0x7fffffff,0x8000)
    tlb = bytearray(768)
    struct.pack_into('<4I',tlb,0,0x6000,0x10000,0x17,0x117)
    vu = bytearray(1570)
    struct.pack_into('<I',vu,28,0x3f800000)  # VF0.w
    struct.pack_into('<I',vu,128,0x41200000)  # VF7.x
    struct.pack_into('<I',vu,528+29*16,1)  # VPU-STAT busy
    struct.pack_into('<I',vu,528+22*16,0x40000000)  # old architected Q
    struct.pack_into('<I',vu,1040,0x40400000)  # separate saved Q latch
    struct.pack_into('<Q',vu,1056,12340)
    struct.pack_into('<I',vu,1093,1)  # pending-Q marker, after a one-byte bool
    struct.pack_into('<I',vu,1101,0x88)  # first JIT MAC flag instance
    struct.pack_into('<IIiII',vu,1178,7,8,1,8,4)
    struct.pack_into('<QIIII',vu,1202,12340,4,8,0x41,0x123456)
    struct.pack_into('<I',vu,1378,1)  # FMAC queue count
    struct.pack_into('<iI',vu,1382,1,0x40800000)  # active FDIV and its pending value
    struct.pack_into('<QII',vu,1406,12340,7,0x20)
    struct.pack_into('<i',vu,1462,5)
    struct.pack_into('<QI',vu,1470,12340,4)
    struct.pack_into('<I',vu,1566,1)
    def tag(text):
        return text.encode().ljust(32,b'\0')
    name = b'cdrom0:SYNTHETIC;1'
    return (tag('BIOS')+bytes(260)+struct.pack('<II',0x12345678,len(name))+name+b'\1'+tag('cpuRegs')+
            cpu+bytes(952)+fpu+tlb+bytes(976)+bytes(8)+tag('Cycles')+bytes(36)+tag('EE-Subsystems')+
            bytes(64)+tag('vuMicroRegs')+vu+bytes(1618)+tag('IOP-Subsystems'))


class SavestateFormat(unittest.TestCase):
    def test_replay_rejects_backend_work_and_preserves_idle_registers(self):
        registers = savestate.internal_registers(fixture())
        snapshot = savestate.Snapshot('synthetic',savestate.VERSION,'fixture',
                                     {n:bytes(size) for n,(_,size) in savestate.REGIONS.items()},registers,b'')
        with self.assertRaisesRegex(ValueError,'active saved VU0'):
            snapshot.replay_image()
        vu = registers['vu0'];vu['vi'][29][0]=0
        vu['fmac_queue'][2]=vu['ialu_queue'][2]=0
        vu['fdiv']['enabled']=vu['efu']['enabled']=0
        registers['fpu']['acc_overflow_raw']=0
        bridge = snapshot.replay_image()
        self.assertEqual(bridge[:8],b'EESNAP01')
        self.assertEqual(struct.unpack_from('<4I',bridge,8+31*16),(1,2,3,4))
        self.assertEqual(struct.unpack_from('<3I',bridge,8+396*4),(0x7fffffff,0x100000,0))
        registers['cpu']['delay_slot']=1
        with self.assertRaisesRegex(ValueError,'saved EE branch'):
            snapshot.replay_image()

    def test_register_offsets_and_pending_state(self):
        state = savestate.internal_registers(fixture())
        self.assertEqual(state['cpu']['gpr'][31],[1,2,3,4])
        self.assertEqual(state['cpu']['pc'],0x100000)
        self.assertEqual(state['cpu']['cycle'],12345)
        self.assertEqual(state['cpu']['cop0'][12],0x70000000)
        self.assertEqual(state['fpu']['fpr'][7],0x3f800000)
        self.assertEqual(state['fpu']['acc_overflow_raw'],0x8000)
        self.assertEqual(state['tlb'][0],dict(page_mask=0x6000,entry_hi=0x10000,entry_lo0=0x17,entry_lo1=0x117))
        vu = state['vu0']
        self.assertEqual(vu['vf'][7][0],0x41200000)
        self.assertEqual(vu['cycle'],12340)
        self.assertEqual(vu['vi'][22][0],0x40000000)
        self.assertEqual(vu['q'][0],0x40400000)
        self.assertEqual(vu['pending_q'],1)
        self.assertEqual(vu['micro_mac_flags'][0],0x88)
        self.assertEqual(vu['fmac_queue'][2],1)
        self.assertEqual(vu['fmac'][0]['start_cycle'],12340)
        self.assertEqual(vu['fmac'][0]['clip_flag'],0x123456)
        self.assertEqual(vu['fdiv']['register'][0],0x40800000)
        self.assertEqual(vu['fdiv']['status_flag'],0x20)
        self.assertEqual(vu['ialu'][0],dict(register=5,start_cycle=12340,latency=4))
        self.assertEqual(vu['ialu_queue'][2],1)

    def test_archive_reads_members_in_memory(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)/'synthetic.p2s'
            internal = fixture()
            with zipfile.ZipFile(path,'w',compression=zipfile.ZIP_DEFLATED) as archive:
                archive.writestr('PCSX2 Savestate Version.id',struct.pack('<I',0x9a590000)+b'format-test'.ljust(32,b'\0'))
                archive.writestr('PCSX2 Internal Structures.dat',internal)
                for name,(_,size) in savestate.REGIONS.items():
                    archive.writestr(name,bytes(size))
            loaded = savestate.load(path)
            self.assertEqual(loaded.internals,internal)
            self.assertEqual(len(loaded.regions['eeMemory.bin']),32*1024*1024)
            self.assertTrue(loaded.summary()['vu0_busy'])
            self.assertFalse(loaded.summary()['replay_validated'])
            self.assertEqual([p.name for p in Path(directory).iterdir()],['synthetic.p2s'])

    def test_unknown_version_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)/'unknown.p2s'
            with zipfile.ZipFile(path,'w') as archive:
                archive.writestr('PCSX2 Savestate Version.id',struct.pack('<I',0x9a580000))
            with self.assertRaisesRegex(ValueError,'unsupported PCSX2 savestate format'):
                savestate.load(path)

    def test_truncated_pipeline_is_rejected(self):
        data = fixture()
        pos = data.index(b'vuMicroRegs')+32
        with self.assertRaises(ValueError):
            savestate.internal_registers(data[:pos+100]+data[-32:])


if __name__ == '__main__':
    unittest.main()
