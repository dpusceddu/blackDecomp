import sys
from pathlib import Path
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[2]/'tools'))
from stack_context import detect_frame_size


def addiu(reg, source, immediate):
    return 9<<26 | source<<21 | reg<<16 | (immediate&0xffff)


class Frames(unittest.TestCase):
    def test_scheduled_allocation_after_register_setup(self):
        self.assertEqual(detect_frame_size([0x00c0102d,addiu(29,29,-32),0x03e00008,addiu(29,29,32)]),32)

    def test_scheduled_allocation_after_lui_and_argument_move(self):
        self.assertEqual(detect_frame_size([0x3c030045,0x00a0302d,addiu(29,29,-32),0x03e00008,addiu(29,29,32)]),32)

    def test_first_instruction_can_be_an_argument_addiu(self):
        self.assertEqual(detect_frame_size([addiu(4,4,1),addiu(29,29,-64),0x03e00008,addiu(29,29,64)]),64)

    def test_dynamic_or_multiple_frames_are_rejected(self):
        self.assertIsNone(detect_frame_size([addiu(29,29,-32),addiu(29,29,-16)]))
        self.assertIsNone(detect_frame_size([addiu(29,29,-32),0x001de823]))

    def test_control_or_stack_access_before_frame_is_ambiguous(self):
        self.assertIsNone(detect_frame_size([0x10800002,0,addiu(29,29,-32)]))
        self.assertIsNone(detect_frame_size([0xafbf0000,addiu(29,29,-32)]))

    def test_wrong_restore_and_unaligned_frame_are_rejected(self):
        self.assertIsNone(detect_frame_size([addiu(29,29,-32),addiu(29,29,16)]))
        self.assertIsNone(detect_frame_size([addiu(29,29,-12)]))


if __name__=='__main__': unittest.main()
