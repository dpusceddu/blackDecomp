#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002AC628();
extern s32 func_0035C6EC();
extern s32 func_0027BA68();
extern s32 func_0027B688();
extern s32 func_0027BB98();

void func_0027ACC8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027ACD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B260);

s32 func_0027B2C8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x6C) = -1.0f;
    return 1;
}

void func_0027B2E0(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x68) = arg1;
    M2C_FIELD(arg1, void **, 0x30) = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B2F0);

void func_0027B388(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x74) = fparg0;
}

s32 func_0027B390(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;
    s32 temp_5;

    func_002AC628(M2C_FIELD(arg0, s32 *, 0x60), M2C_FIELD(arg1, s32 *, 0x60), arg2);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x64);
    if (temp_5 != 0) {
        func_002AC628(M2C_FIELD(arg0, s32 *, 0x64), temp_5, arg2);
    }
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x7C) = (s32) M2C_FIELD(arg2, s32 *, 0xC);
    temp_2 = M2C_FIELD(arg1, s32 *, 0x80);
    M2C_FIELD(arg0, s32 *, 0x80) = temp_2;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B408);

void func_0027B648(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 8) = arg1;
  M2C_FIELD(arg0, s32 *, 0xC) = arg2;
  M2C_FIELD(arg0, s32 *, 0) = (M2C_FIELD(arg0, s32 *, 4) = 0);
  func_0035C6EC(arg1, 0, arg2 << 5);
}

// UNVERIFIED: original record and ring identities, and unused fields.
typedef struct { u8 unknown[0x1E]; u8 occupied, unknown1F; } Recovered_RingRecord;
typedef struct { s32 cursor, used; Recovered_RingRecord* records; s32 capacity; } Recovered_RecordRing;
s32 func_0027B688(Recovered_RecordRing* ring) {
    s32 index = ring->cursor;
    Recovered_RingRecord* records = ring->records;
    if (records[index].occupied) {
        do {
            index++;
            if (index >= ring->capacity) index = 0;
        } while (records[index].occupied);
    }
    ring->cursor = index;
    return index;
}

s32 func_0027B6D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_18;
    void *temp_4;

    temp_18 = func_0027BA68(arg2, arg3, arg4);
    temp_4 = M2C_FIELD(arg0, s32 *, 8) + (func_0027B688(arg0) << 5);
    M2C_FIELD(temp_4, s32 *, 0xC) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x10) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x14) = arg4;
    M2C_FIELD(temp_4, s32 *, 0x18) = temp_18;
    M2C_FIELD(temp_4, s8 *, 0x1D) = (s8) arg5;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
    return (s32) temp_4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027B950);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BA60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BA68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BB50);
#ifdef NON_MATCHING
// Unmatched: section is eight bytes shorter despite matching instructions.
s32 func_0027BB98(Recovered_RecordRing* ring, Recovered_RingRecord* record) {
    record->occupied = 0;
    return --ring->used;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BB98);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BBB8);

void func_0027BC38(void) {

}

void func_0027BC40(void) {

}

void func_0027BC48(void) {

}

void func_0027BC50(void) {

}

void func_0027BC58(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2792c0_27acc8", func_0027BC60);

void func_0027BD00(void) {
    func_0027BB98();
}
