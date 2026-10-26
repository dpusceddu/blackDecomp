#include "include_asm.h"
#include "ps2/prelude.h"

/* Partial dispatch layout; member meanings remain UNVERIFIED. */
typedef struct Recovered_SlotDispatch {
    u8 unk_00[0x18];
    s16 unk_18;
    u16 unk_1A;
    void (*unk_1C)(void*, void*);
    s16 unk_20;
    u16 unk_22;
    void (*unk_24)(void*, int);
} Recovered_SlotDispatch;

typedef struct Recovered_SlotObject {
    Recovered_SlotDispatch* unk_00;
} Recovered_SlotObject;

typedef struct Recovered_SlotOwner {
    u8 unk_000[0x1C0];
    Recovered_SlotObject* unk_1C0[14];
    u8 unk_1F8[0x4F8];
    u64 unk_6F0;
    u8 unk_6F8[8];
    u8 unk_700[0xE0];
    u8 unk_7E0;
    u8 unk_7E1;
    u8 unk_7E2;
} Recovered_SlotOwner;

s32 func_00110858(s32 arg0) {
    return arg0 + 0x7F0;
}

void func_00110860(Recovered_SlotOwner* owner, int index) {
    if (owner->unk_7E2) {
        Recovered_SlotObject* slot = owner->unk_1C0[index];
        Recovered_SlotDispatch* dispatch = slot->unk_00;
        dispatch->unk_1C((u8*)slot + dispatch->unk_18, owner->unk_700);
    }
    owner->unk_6F0 |= 1L << index;
}
void func_001108D0(Recovered_SlotOwner* owner, int index) {
    if (owner->unk_7E2) {
        Recovered_SlotObject* slot = owner->unk_1C0[index];
        Recovered_SlotDispatch* dispatch = slot->unk_00;
        dispatch->unk_24((u8*)slot + dispatch->unk_20, 0);
    }
    owner->unk_6F0 &= ~(1L << index);
}
void func_00110940(Recovered_SlotOwner* owner, int index) {
    u64 bit;
    int i;
    for (i = 0; i < 14; i++) {
        bit = 1UL;
        if ((owner->unk_6F0 >> i) & bit) { func_001108D0(owner, i); }
    }
    func_00110860(owner, index);
    owner->unk_7E0 = 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110858", func_001109C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110858", func_001109C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110858", func_00110A78);
