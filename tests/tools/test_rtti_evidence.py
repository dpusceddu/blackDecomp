"""Synthetic legacy RTTI flow tests; no retail/SDK input or target execution."""
from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'tools'))
from rtti_evidence import constant_flow, deleting_destructor_pattern, inline_type_record, literal_offsets


def lui(rt, value):
    return (15 << 26) | (rt << 16) | value


def addiu(rt, rs, value):
    return (9 << 26) | (rs << 21) | (rt << 16) | (value & 65535)


def move(rd, rs):
    return (rs << 21) | (rd << 11) | 0x2d


def jal(target):
    return (3 << 26) | ((target >> 2) & 0x3ffffff)


def store(rt, rs, offset):
    return (43 << 26) | (rs << 21) | (rt << 16) | (offset & 65535)


RETURN = 0x03e00008
HELPER, GETTER = 0x2000, 0x3000


class ConstantFlow(unittest.TestCase):
    def test_delay_slot_contributes_final_call_argument(self):
        words = [lui(4, 0x40), addiu(4, 4, 0x1000), lui(5, 0x40),
                 jal(HELPER), addiu(5, 5, 0x2000), RETURN, 0]
        calls, _ = constant_flow(words, 0x1000, 0x408000, {})
        self.assertEqual(calls[(3, HELPER)][:2], (0x401000, 0x402000))

    def test_getter_return_propagates_to_single_base_argument(self):
        _, value = constant_flow([lui(2, 0x40), addiu(2, 2, 0x1234), RETURN, 0],
                                 GETTER, 0, {})
        words = [jal(GETTER), 0, move(6, 2), addiu(4, 0, 0x1000),
                 addiu(5, 0, 0x2000), jal(HELPER), 0, RETURN, 0]
        calls, _ = constant_flow(words, 0x1000, 0, {GETTER: value})
        self.assertEqual(calls[(5, HELPER)], (0x1000, 0x2000, 0x401234, None))
        unknown, _ = constant_flow(words, 0x1000, 0, {})
        self.assertIsNone(unknown[(5, HELPER)][2])

    def test_branch_join_rejects_disagreeing_name_addresses(self):
        words = [addiu(4, 0, 0x1000), (4 << 26) | (6 << 21) | 4, 0,
                 addiu(5, 0, 11), (4 << 26) | 2, 0,
                 addiu(5, 0, 22), jal(HELPER), 0, RETURN, 0]
        calls, _ = constant_flow(words, 0x1000, 0, {})
        self.assertEqual(calls[(7, HELPER)][:2], (0x1000, None))

    def test_likely_branch_annuls_delay_slot_on_fallthrough(self):
        words = [addiu(5, 0, 1), (0x15 << 26) | (6 << 21) | 2,
                 addiu(5, 0, 2), 0, jal(HELPER), 0, RETURN, 0]
        calls, _ = constant_flow(words, 0x1000, 0, {})
        self.assertIsNone(calls[(4, HELPER)][1])

    def test_call_clobbers_arguments_but_keeps_saved_registers(self):
        words = [addiu(4, 0, 1), addiu(5, 0, 2), addiu(16, 0, 3),
                 jal(HELPER), 0, jal(HELPER), 0, move(2, 16), RETURN, 0]
        calls, value = constant_flow(words, 0x1000, 0, {})
        self.assertEqual(calls[(5, HELPER)][:2], (None, None))
        self.assertEqual(value, 3)


class InlineTypes(unittest.TestCase):
    def fixture(self):
        return [lui(4, 0x4a), addiu(4, 4, 0x1000), lui(2, 0x41),
                addiu(2, 2, -0x3f40), store(2, 4, 4), lui(3, 0x40),
                addiu(3, 3, 0x2000), store(3, 4, 0), move(2, 4), RETURN, 0]

    def test_builtin_record_comes_from_name_and_vtable_stores(self):
        row = inline_type_record(self.fixture(), 0x1000, 0, {0x40c0c0: 'builtin'},
                                 {0x402000: 'i'}.get)
        self.assertEqual(row['kind'], 'builtin')
        self.assertEqual(row['encoded_name'], 'i')
        self.assertEqual(row['storage'], [0x4a1000])
        self.assertEqual(row['getters'], [0x1000])

    def test_unknown_runtime_vtable_does_not_create_type(self):
        self.assertIsNone(inline_type_record(self.fixture(), 0x1000, 0, {},
                                             {0x402000: 'i'}.get))

    def test_name_store_to_other_storage_does_not_create_type(self):
        words = self.fixture()
        words[7] = store(3, 4, 8)
        self.assertIsNone(inline_type_record(words, 0x1000, 0, {0x40c0c0: 'builtin'},
                                             {0x402000: 'i'}.get))

    def test_string_can_follow_nonzero_binary_byte_but_not_template_prefix(self):
        name = b'Q24Test5Thing\0'
        data = b'\x7f' + name + b'Q24Testt5Array1Z' + name + b'\0' + name
        self.assertEqual(list(literal_offsets(data, name)), [1, len(data) - len(name)])


class SpecialMembers(unittest.TestCase):
    def fixture(self):
        words = [move(16, 4), (12 << 26) | (5 << 21) | (2 << 16) | 1,
                 (4 << 26) | (2 << 21) | 5, lui(25, 0x40),
                 (35 << 26) | (25 << 21) | (25 << 16),
                 (25 << 21) | (31 << 11) | 9, move(4, 16), 0, RETURN, 0]
        return dict(addr=0x1000, words=words, rel={'4': ['lo', 0x3c87e0, 0, 'release']})

    def test_incharge_bit_guard_skips_release_of_this(self):
        proof = deleting_destructor_pattern(self.fixture())
        self.assertEqual((proof['mask'], proof['branch'], proof['release']),
                         (0x1004, 0x1008, 0x1014))

    def test_mask_of_another_argument_is_not_incharge_proof(self):
        function = self.fixture()
        function['words'][1] = (12 << 26) | (6 << 21) | (2 << 16) | 1
        self.assertIsNone(deleting_destructor_pattern(function))

    def test_release_of_another_pointer_is_not_destructor_proof(self):
        function = self.fixture()
        function['words'][6] = move(4, 6)
        self.assertIsNone(deleting_destructor_pattern(function))

    def test_mask_without_conditional_skip_is_not_destructor_proof(self):
        function = self.fixture()
        function['words'][2] = 0
        self.assertIsNone(deleting_destructor_pattern(function))


if __name__ == '__main__':
    unittest.main()
