#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001E5AF8();
extern s32 func_001E5DD0(void *);
extern s32 func_00138320();
extern s32 func_00135570();
extern s32 func_0012D158();
extern void * D_0040F4D0;
extern s32 func_001E4B70(s32);
extern M2C_UNK D_003BD478;

/* Partial grid view: slot status is observed; the remaining fields are UNVERIFIED. */
typedef struct Recovered_GridEntry {
    s32 unk_00;
    u8 unk_04[0x28];
} Recovered_GridEntry;
typedef struct Recovered_GridRow {
    Recovered_GridEntry entries[6];
    u8 unk_108[0x68];
    u8 unk_170;
    u8 unk_171[0x1F];
} Recovered_GridRow;
typedef struct Recovered_GridOwner {
    u8 unk_000[0xE0];
    Recovered_GridRow rows[3];
    u8 unk_590[0x204];
    s32 unk_794;
    u8 unk_798[0xBC];
    s32 unk_854;
    u8 unk_858[0x50];
    s32 unk_8A8;
} Recovered_GridOwner;
typedef char RecoveredGridEntrySize[(sizeof(Recovered_GridEntry) == 0x2C) ? 1 : -1];
typedef char RecoveredGridRowSize[(sizeof(Recovered_GridRow) == 0x190) ? 1 : -1];
extern s32 func_001E7448(Recovered_GridEntry*);
extern void func_001E63B8(void*, u64, s32);
extern u64 D_003F9208[7];
extern u64 D_003F92C0[];
extern s32 func_001E6118(void*, u64);
extern s32 func_001E6C38(void*, void*, u64);
extern void func_001E4F40(void*);
extern void func_001E6A98(void*, u32);
extern s32 func_00382348(void*, s32);

/* Partial keyed table; the entry and group meanings are UNVERIFIED. */
typedef struct Recovered_KeyEntry {
    u64 unk_00;
    u32 unk_08;
    u16 unk_0C;
    u8 unk_0E[0xA];
} Recovered_KeyEntry;
typedef struct Recovered_KeyGroup {
    u8 unk_00[8];
    u64 unk_08;
    u16 unk_10;
    u8 unk_12[2];
    Recovered_KeyEntry* unk_14;
} Recovered_KeyGroup;
typedef struct Recovered_KeyTable {
    u8 unk_00[0x50];
    u32 unk_50;
    u8 unk_54[4];
    Recovered_KeyGroup** unk_58;
} Recovered_KeyTable;
typedef struct Recovered_KeyOwner {
    u8 unk_00[0x44];
    Recovered_KeyTable* unk_44;
} Recovered_KeyOwner;
typedef char RecoveredKeyEntrySize[(sizeof(Recovered_KeyEntry) == 0x18) ? 1 : -1];
typedef char RecoveredKeyPointerIs32[(sizeof(void*) == 4) ? 1 : -1];

s32 func_001E51C8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x44), s32 *, 0x5C)), s32 *, 0);
}

Recovered_KeyEntry* func_001E51E0(Recovered_KeyOwner* owner, const u64* group_key, const u64* entry_key) {
    u32 group_index;
    for (group_index = 0; group_index < owner->unk_44->unk_50; group_index++) {
        Recovered_KeyGroup* group = owner->unk_44->unk_58[group_index];
        if (group->unk_08 == *group_key) {
            u32 entry_index;
            for (entry_index = 0; entry_index < group->unk_10; entry_index++) {
                Recovered_KeyEntry* entry = &group->unk_14[entry_index];
                if (entry->unk_00 == *entry_key) { return entry->unk_0C ? entry : 0; }
            }
        }
    }
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: random conversion and floating-point scheduling differ.
extern u32 D_0040EB30[2];
static inline u32 NextTimingRandom(void) {
    u32 first = D_0040EB30[0];
    u32 second = D_0040EB30[1];
    u32 next = (first << 16) + ((s32)first >> 16) + second;
    D_0040EB30[1] = second + next;
    D_0040EB30[0] = next;
    return next;
}

void func_001E5270(void* unused, s32* indices, s32 count, s32 limit) {
    u32 next = NextTimingRandom();
    f32 scale = ((f32)((s32)((u32)limit - 1U)) + 1.0f) - 0.0000152587890625f;
    s32* cursor;
    s32 remaining;

    indices[0] = (s32)(0.0f + (scale - 0.0f) * ((f32)next * 2.3283064365386963e-10f));
    cursor = indices + 1;
    if (count > 1) {
        remaining = count - 1;
        do {
            *cursor = (s32)((u32)cursor[-1] + 1U) % count;
            cursor++;
            remaining--;
        } while (remaining != 0);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5270);
#endif
#ifdef NON_MATCHING
// Unmatched: loop padding and final argument scheduling differ.
void func_001E5360(void* owner) {
    s32 remaining = 1;
    u8* state;
    s32* counters;
    void* target;
    s32 parameter;
    func_001E4F40((u8*)owner + 0x79C);
    state = (u8*)owner + 0x68;
    func_001E4F40((u8*)owner + 0x7F0);
    do {
        func_001E6A98(state, (u32)owner + 0x79C);
        remaining--;
        state += 0x38;
    } while (remaining >= 0);
    target = (u8*)owner + 0x8D0;
    remaining = 2;
    counters = (s32*)((u8*)owner + 0x84C);
    do {
        *counters-- = 0;
        remaining--;
    } while (remaining >= 0);
    M2C_FIELD(owner, s32*, 0x798) = 0;
    parameter = 0x02B9D6F8;
    M2C_FIELD(owner, s32*, 0x850) = 0;
    M2C_FIELD(owner, s32*, 0x8A8) = 0;
    M2C_FIELD(owner, s32*, 0x854) = 5;
    func_00382348(target, parameter);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5360);
#endif

s32 func_001E5408(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 4) + ((s32) &D_003BD478)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5420);
void func_001E5830(Recovered_GridOwner* owner) {
    s32 key_index;
    s32 row;
    s32 remaining = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), s8*, 0x19);
    for (key_index = 0; key_index < 7; key_index++) {
        for (row = 0; row < 3; row++) {
            if (owner->rows[row].unk_170) {
                func_001E63B8(&owner->rows[row], D_003F9208[key_index], 0);
                remaining--;
                if (remaining == 0) { return; }
            }
        }
    }
}

void func_001E5900(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x798) == 8) {
        func_001E5AF8();
        func_001E5DD0(arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5AF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5AF8);
/* UNVERIFIED: the four queued values and their meaning are unknown. */
typedef struct Recovered_GridQueue {
    u8 unk_000[0x784];
    s32 entries[4];
    u32 count;
} Recovered_GridQueue;

void func_001E5CB0(Recovered_GridQueue* self, s32 item) {
    if (self->count < 4) self->entries[self->count++] = item;
}

s32 func_001E5CD8(void) {
    return 1;
}

s32 func_001E5CE0(void *arg0, s32 arg1) {
    s32 temp_2;
    s32 var_16;
    s32 var_18;

    var_16 = -1;
    var_18 = 0;
    temp_2 = func_00138320(func_00135570(arg1));
    if (temp_2 >= 0x24) {
        if (temp_2 < 0x26) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x594);
            var_16 = 2;
        } else if (temp_2 < 0x2B) {
            var_18 = M2C_FIELD(arg0, s32 *, 0x590);
            var_16 = 1;
        }
    }
    return (func_0012D158(D_0040F4D0, 0, var_16 - 1) * 0x190) + var_18;
}

void func_001E5D80(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x170) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5DC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5DD0);
#ifdef NON_MATCHING
// Unmatched: flag tests and return branches are laid out differently.
s32 func_001E5F30(Recovered_GridOwner* owner) {
    u32 row;
    u32 column;
    if (owner->unk_794 != 0 || owner->unk_854 != 0 || owner->unk_8A8 != 0) { return 1; }
    for (row = 0; row < 3; row++) {
        for (column = 0; column < 6; column++) {
            if (owner->rows[row].entries[column].unk_00 != 1) { return 1; }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E5F30);
#endif

s32 func_001E5FA8(s32 arg0) {
    return func_001E4B70(arg0 + 0x858) != 0;
}

s32 func_001E5FC8(Recovered_GridOwner* owner) {
    u32 row;
    u32 column;
    for (row = 0; row < 3; row++) {
        for (column = 0; column < 6; column++) {
            if (func_001E7448(&owner->rows[row].entries[column]) == 0) { return 0; }
        }
    }
    return 1;
}

void func_001E6050(void) {

}

#ifdef NON_MATCHING
/* UNVERIFIED: partial view of the current and previous coordinates. */
typedef struct Recovered_GridPosition {
    u8 unk_000[0x8AC];
    f32 current[3];
    u8 unk_8B8[4];
    u8 changed;
    u8 unk_8BD[3];
    f32 previous[3];
} Recovered_GridPosition;

// Unmatched: the first coordinate store is scheduled later than the reference.
void func_001E6058(Recovered_GridPosition* self, f32 x, f32 y, f32 z) {
    f32 oldX = self->current[0], oldY = self->current[1], oldZ = self->current[2];
    self->previous[0] = oldX;
    self->previous[1] = oldY;
    self->previous[2] = oldZ;
    self->current[2] = z;
    self->current[0] = x;
    self->current[1] = y;
    self->changed = 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6058);
#endif

void func_001E6088(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x8AC) = (f32) M2C_FIELD(arg0, f32 *, 0x8C0);
    M2C_FIELD(arg0, f32 *, 0x8B0) = (f32) M2C_FIELD(arg0, f32 *, 0x8C4);
    M2C_FIELD(arg0, f32 *, 0x8B4) = (f32) M2C_FIELD(arg0, f32 *, 0x8C8);
    M2C_FIELD(arg0, s8 *, 0x8BC) = 0;
}

s32 func_001E60A8(void* unused, u64 key) {
    s32 i;
    for (i = 0; i < 7; i++) {
        if (key == D_003F9208[i]) return 1;
    }
    return 0;
}
const u64 D_003F9240[6] = {
    0x87C4F55F40000000ULL, 0x81F2D7A540000000ULL, 0x87EA361D80000000ULL,
    0x8218186380000000ULL, 0x5F2B660780000000ULL, 0x6C1EE82BC0000000ULL,
};
const u64 D_003F9270[4] = {
    0x81F2D7A540000000ULL, 0x8218186380000000ULL,
    0x87C4F55F40000000ULL, 0x87EA361D80000000ULL,
};

s32 func_001E60E0(void* unused, u64 key) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (key == D_003F9270[i]) return 1;
    }
    return 0;
}
s32 func_001E6118(void* unused, u64 key) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (key == D_003F9240[i]) return 1;
    }
    return 0;
}
#ifdef NON_MATCHING
// Unmatched: register allocation differs and the key table is assembly-owned.
s32 func_001E6150(void* owner, void* argument, s32 key_index) {
    u64* key = &D_003F92C0[key_index];
    if (func_001E6118(owner, *key) != 0) {
        s32 index;
        u8* state = (u8*)owner + 0x68;
        for (index = 0; index < 2; index++) {
            if (func_001E6C38(state, argument, *key) != 0) { return 1; }
            state += 0x38;
        }
        return 0;
    }
    {
        s32 result = 1;
        if (func_001E6C38((u8*)owner + 0x68, argument, *key) == 0) { result = 0; }
        return result;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6150);
#endif
/* UNVERIFIED: only the channel byte and pointer array are described. */
typedef struct Recovered_GridChannel {
    u8 unk_00[0x35];
    u8 value;
} Recovered_GridChannel;
typedef struct Recovered_GridChannels {
    u8 unk_000[0x844];
    Recovered_GridChannel* channels[2];
} Recovered_GridChannels;

void func_001E6208(Recovered_GridChannels* self, u32 kind, s32 value) {
    Recovered_GridChannel** channel = self->channels;
    u32 i = 0;
    do {
        if (*channel) (*channel)->value = value;
        channel++;
        i++;
    } while (i < 2);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e51c8", func_001E6240);
