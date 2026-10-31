#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001E9EE8();
extern M2C_UNK D_0042A630;
/* The meanings of these 17 keys are UNVERIFIED. */
extern u64 D_003F9410[];
/* Partial mode state and table entry; their meanings are UNVERIFIED. */
typedef struct Recovered_ModeOwner {
    u8 unk_00[0x90];
    u32 active;
    u32 previous;
    s32 current;
    u8 delay;
} Recovered_ModeOwner;
typedef struct Recovered_ModeEntry {
    f32 pairs[18][2];
    f32 weights[18];
    u8 flags[18];
    u8 unk_EA;
    u8 unk_EB[0x45];
    u64 key;
    f32 expiry;
    u8 unk_13C;
    u8 unk_13D;
    u8 unk_13E[2];
} Recovered_ModeEntry;
typedef char RecoveredModeEntrySize[(sizeof(Recovered_ModeEntry) == 0x140) ? 1 : -1];
extern void* D_0040F4D0;
extern s32 func_001EA728(void*, u64, s32*);
extern void func_001EA2D0(Recovered_ModeOwner*);

#ifdef NON_MATCHING
// Unmatched: mode-entry address calculations and store scheduling differ.
s32 func_001E9D30(Recovered_ModeOwner* owner) {
    Recovered_ModeEntry* entries = (Recovered_ModeEntry*)&D_0042A630;
    s32 index = 0;
    s32 result;
    owner->active = 1;
    owner->current = 0;
    owner->delay = 0;
    owner->previous = 0;
    do {
        Recovered_ModeEntry* entry = &entries[index];
        s32 item;
        entry->key = D_003F9410[index];
        entry->unk_EA = 0;
        entry->unk_13C = 0;
        entry->unk_13D = 0;
        entry->expiry = -1.0f;
        for (item = 0; item < 18; item++) {
            entry->pairs[item][0] = 1.0f;
            entry->pairs[item][1] = 1.0f;
            entry->weights[item] = 0.25f;
            entry->flags[item] = 0;
        }
        index++;
        result = index < 17;
    } while (result);
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001E9D30);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001E9E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001E9EE8);
#ifdef NON_MATCHING
// Unmatched: countdown branch and delay-slot scheduling differ.
s32 func_001EA200(Recovered_ModeOwner* owner) {
    Recovered_ModeEntry* entries = (Recovered_ModeEntry*)&D_0042A630;
    f32 now = M2C_FIELD(D_0040F4D0, f32*, 0x20);
    s32 index;
    s32 remaining;
    for (index = 0; index < 17; index++) {
        u32 bit = 1U << index;
        if ((owner->active & bit) && entries[index].expiry > 0.0f && entries[index].expiry < now) {
            owner->active &= ~bit;
        }
    }
    if (owner->active != owner->previous || owner->delay == 0) {
        func_001EA2D0(owner);
        owner->previous = owner->active;
    }
    remaining = (s32)owner->delay - 1;
    owner->delay = remaining;
    return remaining;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001EA200);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001EA2D0);

s32 func_001EA4F0(s32 arg0) {
    func_001E9EE8(arg0, 0);
    return 1;
}

void func_001EA510(void) {

}

void func_001EA518(void *arg0, s32 arg1, s32 arg2) {
    void *temp_4;

    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) | (1 << arg1));
        temp_4 = (arg1 * 0x140) + ((s32) &D_0042A630);
        M2C_FIELD(temp_4, f32 *, 0x138) = -1.0f;
        M2C_FIELD(temp_4, s8 *, 0x13D) = 0;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) & ~(1 << arg1));
}

void func_001EA580(Recovered_ModeOwner* owner, u64 key, s32 enabled) {
    s32 index;
    s32 result = func_001EA728(owner, key, &index);
    if (result != 0) {
        if (enabled != 0) {
            u32 bit = 1U << index;
            Recovered_ModeEntry* entry = &((Recovered_ModeEntry*)&D_0042A630)[index];
            owner->active |= bit;
            entry->expiry = -1.0f;
            entry->unk_13D = 0;
            return;
        }
        owner->active &= ~(1U << index);
        return;
    }
    return;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001EA620);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e9d30", func_001EA628);
s32 func_001EA728(void* owner, u64 key, s32* index) {
    s32 found = 0;
    *index = 0;
    do {
        if (D_003F9410[*index] == key) {
            found = 1;
        } else {
            (*index)++;
        }
    } while (!found && *index < 17);
    return found;
}
