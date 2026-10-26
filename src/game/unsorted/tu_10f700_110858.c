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

/* Partial sampled-track layout; member meanings remain UNVERIFIED. */
typedef struct Recovered_SamplePoint {
    f32 unk_00;
    u8 unk_04[0x3C];
} Recovered_SamplePoint;

typedef char RecoveredSamplePointerIs32[(sizeof(void*) == 4) ? 1 : -1];
typedef char RecoveredSamplePointSize[(sizeof(Recovered_SamplePoint) == 0x40) ? 1 : -1];

typedef struct Recovered_SampleTrack {
    s32 unk_00;
    u8 unk_04[4];
    s16 unk_08;
    u8 unk_0A[0xE];
    Recovered_SamplePoint* unk_18;
} Recovered_SampleTrack;

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
s32 func_001109C8(Recovered_SampleTrack* track, f32 value) {
    s16 index = track->unk_08;
    Recovered_SamplePoint* point;
    int finished;

    if (index < 0) { index = 0; }
    if (index > track->unk_00 - 2) { index = track->unk_00 - 2; }
    point = (Recovered_SamplePoint*)(index * 0x40 + (u32)track->unk_18);
    do {
        finished = 1;
        if (value < point->unk_00 && index > 0) {
            point--;
            finished = 0;
            index--;
        }
        if (point[1].unk_00 <= value && index < track->unk_00 - 2) {
            point++;
            finished = 0;
            index++;
        }
    } while (!finished);
    return index;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_10f700_110858", func_00110A78);
