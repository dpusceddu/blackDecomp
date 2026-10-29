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
    u8 unk_00[0x74];
    u16 counts[46];
    Recovered_ScoredSlot slots[8];
    Recovered_ScoredQueueEntry queue[8];
    s32 recent[4];
    s8 queueCount;
} Recovered_ScoredOwner;
typedef char RecoveredScoredSlotSize[(sizeof(Recovered_ScoredSlot) == 0x1C) ? 1 : -1];
extern void* D_0040F4D0;
extern s32 func_00176C70(Recovered_ScoredOwner*, s8);
extern s32 func_00176770(Recovered_ScoredOwner*, s32);
extern f32 func_00176D18(Recovered_ScoredOwner*, Recovered_ScoredSlot*);
extern f32 func_00176DD0(Recovered_ScoredOwner*, Recovered_ScoredSlot*);
extern f32 func_00176D90(Recovered_ScoredOwner*, Recovered_ScoredSlot*);
extern void func_00176AF0(Recovered_ScoredOwner*, Recovered_ScoredSlot*);
extern s32 func_00176B50(Recovered_ScoredOwner*, f32);
extern s32 func_00176E40(Recovered_ScoredOwner*, s32);

s32 func_00176730(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = (s8) arg1 * 0x1C;
    M2C_FIELD((arg0 + temp_5), s8 *, 0xE8) = 0;
    return func_00176460(arg0 + (temp_5 + 0xD0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_001768D0);
#ifdef NON_MATCHING
// Unmatched: temporary record setup and saved-register allocation differ.
s32 func_00176978(Recovered_ScoredOwner* owner, void* object, s32 value, s32 kind, f32 delay, f32 duration) {
    Recovered_ScoredSlot candidate __attribute__((aligned(16)));
    f32 start;
    s32 index;
    s32 result = 0;
    s32 active = 1;

    candidate.unk_00 = object;
    start = M2C_FIELD(D_0040F4D0, f32*, 0x20) + delay;
    candidate.unk_04 = value;
    candidate.unk_14 = -1.0f;
    candidate.unk_08 = kind;
    candidate.unk_0C = start;
    candidate.unk_18 = active;
    candidate.unk_10 = start + duration;
    func_00176AF0(owner, &candidate);
    index = func_00176B50(owner, candidate.unk_14);
    if (index >= 0) {
        Recovered_ScoredSlot* slot = &owner->slots[index];
        result = 1;
        slot->unk_08 = candidate.unk_08;
        slot->unk_00 = candidate.unk_00;
        slot->unk_04 = candidate.unk_04;
        slot->unk_0C = candidate.unk_0C;
        slot->unk_10 = candidate.unk_10;
        slot->unk_14 = candidate.unk_14;
        slot->unk_18 = active;
        owner->counts[kind]++;
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176978);
#endif
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

void func_00176AF0(Recovered_ScoredOwner* owner, Recovered_ScoredSlot* slot) {
    f32 value = func_00176D18(owner, slot);
    func_00176DD0(owner, slot);
    slot->unk_14 = value * func_00176D90(owner, slot);
}
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
extern const f32 D_003F6260[42];
/* Native category weights; original category names are unknown. */
f32 func_00176D90(Recovered_ScoredOwner* owner, Recovered_ScoredSlot* slot) {
    s32 kind = M2C_FIELD(slot, s32*, 8);
    f32 factor = 0.0f;
    if (kind != M2C_FIELD(owner, s32*, 0xC) && kind != M2C_FIELD(M2C_FIELD(slot, void**, 0), s32*, 0xC84)) {
        factor = D_003F6260[kind];
    }
    return factor;
}

const f32 D_003F6260[42] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f, 0.7f, 0.6f, 0.6f, 0.0f, 0.5f, 0.9f, 0.5f, 0.5f,
                            0.5f, 0.3f, 0.5f, 0.9f, 0.9f, 0.2f, 0.8f, 0.8f, 0.7f, 0.4f, 0.3f, 0.4f, 0.4f, 0.4f,
                            0.6f, 0.6f, 0.9f, 0.9f, 1.0f, 1.0f, 0.4f, 0.8f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f, 0.4f};

f32 func_00176DD0(Recovered_ScoredOwner* owner, Recovered_ScoredSlot* slot) {
    f32 factor = 1.0f;
    s32 value = slot->unk_04;
    if (value != 0) {
        s32 index = func_00176E40(owner, value);
        if (index != -1) { factor = 1.0f - ((f32)index + 1.0f) * 0.25f; }
    }
    return factor;
}
#ifdef NON_MATCHING
// Unmatched: the native loop starts one instruction later.
s32 func_00176E40(Recovered_ScoredOwner* owner, s32 value) {
    s8 found = -1;
    s8 index;
    if (value == 0) { return -1; }
    index = 0;
    if (owner->recent[index] == value) {
        found = index;
    } else {
    next:
        index++;
        if (index < 4) {
            if (owner->recent[index] != value) { goto next; }
            found = index;
        }
    }
    return found;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176E40);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176448_176730", func_00176EA0);
