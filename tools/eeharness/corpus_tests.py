#!/usr/bin/env python3
"""Checks for capture decoding and conservative scalar fuzz generation."""
from pathlib import Path
import struct
import tempfile
import unittest
from types import SimpleNamespace

import corpus
import phase2


class CorpusTests(unittest.TestCase):
    def test_live_state_virtual_call_contract(self):
        ram = bytearray(2*1024*1024)
        struct.pack_into('<I',ram,0x100000+0x21070,0x180000)
        struct.pack_into('<I',ram,0x180008,0x1800)
        struct.pack_into('<hI',ram,0x1810,-16,0x1046b0)
        # The function is at +20, following a four-byte adjustment word.
        struct.pack_into('<I',ram,0x1814,0x1046b0)
        self.assertEqual(phase2.state_update_root(ram,0x100000,{0x1046b0}),(0x1046b0,0x17fff0))
        self.assertIsNone(phase2.state_update_root(ram,0x100000,{0x105518}))
        self.assertIsNone(phase2.state_update_root(ram,0,{}))

    def test_boot_thread_context_and_stack_bounds(self):
        ram = bytearray(2*1024*1024);registers = [[0]*4 for _ in range(32)]
        registers[28][0]=0x4157f0;registers[29][0]=0x81e00
        # The documented TCB is 76 bytes. The boot thread has a saved context
        # below its suspended user SP, outside the active kernel stack.
        struct.pack_into('<20I',ram,0x1000,0,0,1,0x367888,0x18f000,0x4157f0,0,0,0,0,0,0,
                         0x100008,0,0,0x180000,0x10000,0,0,0)
        struct.pack_into('<I',ram,0x18f1c0,0x4157f0)
        struct.pack_into('<I',ram,0x18f1d0,0x18f280)
        snapshot = SimpleNamespace(regions={'eeMemory.bin':ram},registers={'cpu':{'gpr':registers}})
        stack = phase2.main_thread_stack(snapshot)
        self.assertEqual(stack['stack'],0x18f000)
        registers[29][0]=0x18fd00
        self.assertIsNone(phase2.main_thread_stack(snapshot))
        registers[29][0]=0x81e00
        struct.pack_into('<I',ram,0x18f1d0,0x18ffff)
        with self.assertRaisesRegex(ValueError,'uniquely recover'):
            phase2.main_thread_stack(snapshot)

    def test_gate_requires_strict_majority_and_completed_collection(self):
        fs = [dict(address=a,size=8,region='game') for a in range(4)]
        self.assertEqual(phase2.summarize(fs,[],{0:20,1:20,2:0,3:0},0)['status'],'not_passed')
        self.assertEqual(phase2.summarize(fs,[],{0:20,1:20,2:20,3:0},0)['status'],'passed')
        self.assertEqual(phase2.summarize(fs,[],{0:20,1:20,2:20,3:0},1)['status'],'not_passed')

    def test_pending_state_and_delta_boundaries(self):
        # Independent literal codec counts; a vector and an external interrupt
        # make a wrong skip offset fail at the following memory delta.
        fixed = [0]*593
        fixed[16]=0x500000;fixed[397]=0x129360;fixed[592]=1
        pending = [0,123,7,8,1,2,3,4,0x80,0x40,0]
        tail = [0]*249;tail[245]=123456;tail[248]=1
        values = [0x129360,7]+fixed+pending+tail+[99999,0x2b2638,1]+[1,0x500000,42,0]
        data = b'EECAP001'+struct.pack('<'+'Q'*len(values),*values)
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)/'entries.eec';path.write_bytes(data)
            memory = bytearray(0x500001)
            rows = list(corpus.entries(path,memory))
            self.assertEqual(len(rows),1)
            self.assertEqual((rows[0]['function'],rows[0]['ordinal'],rows[0]['instructions']),(0x129360,7,123456))
            self.assertEqual(rows[0]['pc'],0x129360)
            self.assertEqual(memory[0x500000],42)
            path.write_bytes(data[:-1])
            with self.assertRaisesRegex(ValueError,'truncated'):
                list(corpus.entries(path))

    def test_fuzz_scalar_contract(self):
        self.assertEqual(corpus.field_variants(0,'bool',1),[1])
        self.assertEqual(corpus.field_variants(17,'bool',1),[])
        self.assertEqual(corpus.field_variants(0x1234,'void *',4),[])
        self.assertEqual(corpus.field_variants(0,'unknown',4),[])
        self.assertEqual(corpus.field_variants(255,'unsigned char',1),[254])
        self.assertEqual(corpus.field_variants(0x3f800000,'float',4),[0x3f800001])


if __name__ == '__main__':
    unittest.main()
