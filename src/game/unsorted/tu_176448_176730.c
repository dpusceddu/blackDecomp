#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00176460(void *);

/* Partial eight-slot owner; meanings of fields and queue entries are UNVERIFIED. */
typedef struct Recovered_ScoredSlot {
    void* unk_00;
    s32 unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    u8 unk_18;
    u8 unk_19[3];
} Recovered_ScoredSlot;
typedef struct Recovered_ScoredQueueEntry {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    f32 unk_0C;
} Recovered_ScoredQueueEntry;
typedef struct Recovered_ScoredOwner {
    u8 unk_00[0xD0];
    Recovered_ScoredSlot slots[8];
    Recovered_ScoredQueueEntry queue[8];
    u8 unk_230[0x10];
    s8 queueCount;
} Recovered_ScoredOwner;
typedef char RecoveredScoredSlotSize[(sizeof(Recovered_ScoredSlot) == 0x1C) ? 1 : -1];
extern void* D_0040F4D0;
extern s32 func_00176C70(Recovered_ScoredOwner*, s8);
extern s32 func_00176770(Recovered_ScoredOwner*, s32);

s32 func_00176730(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = (s8) arg1 * 0x1C;
    M2C_FIELD((arg0 + temp_5), s8 *, 0xE8) = 0;
    return func_00176460(arg0 + (temp_5 + 0xD0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_001768D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176978);
s32 func_00176A78(Recovered_ScoredOwner* owner, u32 first, u32 second, u32 third, f32 score) {
    s32 result = 0;
    if (owner->queueCount < 8) {
        result = 1;
        owner->queue[owner->queueCount].unk_08 = third;
        owner->queue[owner->queueCount].unk_00 = first;
        owner->queue[owner->queueCount].unk_04 = second;
        owner->queue[owner->queueCount].unk_0C = score;
        owner->queueCount++;
    }
    return result;
}

f32 func_00176AE0(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176AF0);
s32 func_00176B50(Recovered_ScoredOwner* owner, f32 score) {
    f32* slotScore = &owner->slots[0].unk_14;
    s32 selected = -1;
    s8 index = 0;
    while (index < 8) {
        if (!M2C_FIELD(slotScore, u8*, 4)) { return index; }
        if (*slotScore < score) {
            score = *slotScore;
            selected = index;
        }
        slotScore = (f32*)((u32)slotScore + sizeof(Recovered_ScoredSlot));
        index++;
    }
    return selected;
}
s32 func_00176BB0(Recovered_ScoredOwner* owner, s32 unused) {
    f32* slotScore = &owner->slots[0].unk_14;
    s8 index = 0;
    s32 selected = -1;
    s32 result;
    f32 best = 0.0f;
    do {
        if (best <= *slotScore && func_00176C70(owner, index)) {
            best = *slotScore;
            selected = index;
        }
        slotScore = (f32*)((u32)slotScore + sizeof(Recovered_ScoredSlot));
        index++;
        result = index < 8;
    } while (result);
    if (selected >= 0) { result = func_00176770(owner, selected); }
    return result;
}
#ifdef NON_MATCHING
// Unmatched: slot-address registers and return branches differ.
s32 func_00176C70(Recovered_ScoredOwner* owner, s8 index) {
    s32 offset = index * 0x1C;
    void* slotBase = (u8*)owner + offset;
    void* subject;
    s32 kind;
    if (!M2C_FIELD(slotBase, u8*, 0xE8)) { return 0; }
    subject = M2C_FIELD(M2C_FIELD(slotBase, void**, 0xD0), void**, 0x7C);
    if (M2C_FIELD(D_0040F4D0, f32*, 0x20) - M2C_FIELD(subject, f32*, 0x2F4) < 3.0f) { return 0; }
    if (M2C_FIELD(subject, s32*, 0x38C) == 0 || (kind = owner->slots[index].unk_08, kind == 0x20 || kind == 0x21)) {
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176C70);
#endif

void func_00176D00(void) {

}

void func_00176D08(void) {

}

void func_00176D10(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176D18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176E40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176EA0);
