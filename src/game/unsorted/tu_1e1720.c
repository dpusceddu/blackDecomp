#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035C6EC(s32, M2C_UNK, M2C_UNK);
extern f32 D_003BD3A8;

/* Partial selection records and owner; field meanings are UNVERIFIED. */
typedef struct Recovered_ChoiceEntry {
    u8 unk_00[0x88];
    s32 kind;
    u8 unk_8C[0x24];
} Recovered_ChoiceEntry;
typedef struct Recovered_ChoiceGroup {
    u8 unk_00[0x10];
    u64 key;
    Recovered_ChoiceEntry* entries;
    Recovered_ChoiceEntry* special;
    s32 count;
    s32 specialCount;
} Recovered_ChoiceGroup;
typedef struct Recovered_ChoiceRegistry {
    u8 unk_00[4];
    Recovered_ChoiceGroup* groups;
    s32 count;
} Recovered_ChoiceRegistry;
typedef struct Recovered_ChoiceOwner {
    u8 unk_00[0x58];
    void* selected;
    u8 unk_5C[0x10];
    f32 elapsed;
    f32 priority;
    u8 unk_74[0x0C];
} Recovered_ChoiceOwner;
typedef char RecoveredChoiceEntrySize[(sizeof(Recovered_ChoiceEntry) == 0xB0) ? 1 : -1];
typedef char RecoveredChoiceGroupSize[(sizeof(Recovered_ChoiceGroup) == 0x28) ? 1 : -1];
typedef char RecoveredChoiceOwnerSize[(sizeof(Recovered_ChoiceOwner) == 0x80) ? 1 : -1];
extern void* D_0040F4D0;
extern f32 func_001E1F18(void*);
extern void func_001E1EA8(void*);
extern Recovered_ChoiceEntry* func_001E1788(void*, Recovered_ChoiceGroup*, s32, s32);
/* Partial selection manager; the meaning of its state fields is UNVERIFIED. */
typedef struct Recovered_ChoiceManager {
    u8 unk_00[0x244];
    s32 unk_244;
    s32 unk_248;
    s32 unk_24C;
    u8 unk_250[0x10];
    u8 unk_260;
    u8 unk_261[3];
    s32 unk_264;
    Recovered_ChoiceOwner* objects;
    Recovered_ChoiceOwner** ordered;
    s32 count;
    s32 unk_274;
    s32 unk_278;
    s32 unk_27C;
    s32 unk_280;
    s32 unk_284;
    s32 unk_288;
    u8 unk_28C;
} Recovered_ChoiceManager;
extern void* func_00107D20(s32);
extern void func_001E1720(Recovered_ChoiceOwner*);
extern void func_00280A08(void*);
extern void func_001E2C68(void*, s32, s32);
extern f32 func_001E2540(Recovered_ChoiceManager*, Recovered_ChoiceOwner*, s128, s128);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E1720);
#ifdef NON_MATCHING
// Unmatched: modulo fallback uses different registers and a division check.
Recovered_ChoiceEntry* func_001E1788(void* owner, Recovered_ChoiceGroup* group, s32 kind, s32 selection) {
    if (kind >= 0x1D && kind < 0x20 && group->specialCount > 0) {
        s32 index = 0;
        Recovered_ChoiceEntry* entry = group->special;
        do {
            if ((entry->kind == 8 && kind == 0x1D) || (entry->kind == 0x10 && kind == 0x1E) ||
                (entry->kind == 0x20 && kind == 0x1F)) {
                return entry;
            }
            index++;
            entry++;
        } while (index < group->specialCount);
    }
    if (group->count != 0) { return &group->entries[selection % group->count]; }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E1788);
#endif
Recovered_ChoiceEntry* func_001E1840(void* owner, u64 key, s32 kind, s32 selection) {
    Recovered_ChoiceRegistry* registry = M2C_FIELD(D_0040F4D0, Recovered_ChoiceRegistry**, 0x5AF0);
    s32 index = 0;
    while (index < registry->count) {
        Recovered_ChoiceGroup* group = &registry->groups[index];
        if (group->key == key) { return func_001E1788(owner, group, kind, selection); }
        index++;
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E18B0);
void func_001E1A70(void* self, f32 dt) {
    s32 state;

    state = M2C_FIELD(self, s32*, 0x5C);
    switch (state) {
        case 5:
            if (M2C_FIELD(self, f32*, 0x68) <= 0.0f) {
                func_001E1EA8(self);
                M2C_FIELD(self, s8*, 0x79) = 1;
            }
            M2C_FIELD(self, f32*, 0x68) = (f32)(M2C_FIELD(self, f32*, 0x68) - dt);
            return;
        case 3:
        case 4:
            if ((M2C_FIELD(self, f32*, 0x64) <= 0.0f) && (M2C_FIELD(self, u8*, 0x7C) == 0)) {
                if (M2C_FIELD(self, f32*, 0x68) <= 0.0f) {
                    func_001E1EA8(self);
                } else {
                    M2C_FIELD(self, s32*, 0x5C) = 5;
                }
            }
            M2C_FIELD(self, u8*, 0x7C) = 0U;
            if (M2C_FIELD(self, f32*, 0x68) <= 0.0f) {
                M2C_FIELD(self, s8*, 0x79) = 1;
                M2C_FIELD(self, f32*, 0x68) = (f32)M2C_FIELD(M2C_FIELD(self, void**, 0x58), f32*, 0x94);
            }
            M2C_FIELD(self, f32*, 0x68) = (f32)(M2C_FIELD(self, f32*, 0x68) - dt);
            M2C_FIELD(self, f32*, 0x64) = (f32)(M2C_FIELD(self, f32*, 0x64) - dt);
            /* fallthrough */
        default:
        case 2:
        case 6: return;
    }
}

s32 func_001E1BA0(void *arg0) {
    func_0035C6EC(arg0 + 0x20, 0, 0x28);
    M2C_FIELD(arg0, s32 *, 0x5C) = 7;
    return 1;
}

void func_001E1BE0(void *arg0, s128 arg1, f32 fparg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x58);
    if (temp_2 != NULL) {
        M2C_FIELD(arg0, s128 *, 0x10) = arg1;
        if (M2C_FIELD(temp_2, u8 *, 0xAC) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x5C) == 2) {
                func_001E1EB8();
            }
            M2C_FIELD(arg0, s8 *, 0x7C) = 1;
        } else {
            M2C_FIELD(arg0, s8 *, 0x79) = 1;
        }
        M2C_FIELD(arg0, f32 *, 0x64) = fparg0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E1C50);

void func_001E1EA8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 6;
}

void func_001E1EB8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 3;
}

s32 func_001E1EC8(Recovered_ChoiceOwner* owner) {
    if (owner->selected != 0 && owner->elapsed < func_001E1F18(owner)) { return 1; }
    return 0;
}

f32 func_001E1F18(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x58), f32 *, 0xA0);
}

f32 func_001E1F28(void) {
    return D_003BD3A8;
}

s32 func_001E1F38(Recovered_ChoiceManager* manager, s32 count) {
    s32 index = 0;
    manager->count = count;
    manager->objects = func_00107D20((u32)count << 7);
    manager->ordered = func_00107D20((u32)count * 4U);
    if (manager->count > 0) {
        do {
            func_001E1720(&manager->objects[index]);
            manager->ordered[index] = &manager->objects[index];
            index++;
        } while (index < manager->count);
    }
    func_00280A08(manager);
    manager->unk_248 = 0;
    manager->unk_24C = 0;
    manager->unk_274 = 0;
    manager->unk_278 = 0;
    manager->unk_280 = 0;
    manager->unk_264 = 0;
    manager->unk_288 = 0;
    manager->unk_27C = 0;
    manager->unk_260 = 0;
    func_001E2C68(manager, 0, 0);
    manager->unk_28C = 0;
    manager->unk_244 = 1;
    manager->unk_284 = 0;
    return 1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E2020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E2540);
#ifdef NON_MATCHING
// Unmatched: sorting-loop registers and pointer scheduling differ.
s32 func_001E26D0(Recovered_ChoiceManager* manager, s128 first, s128 second) {
    s32 index = 0;
    s32 result;
    s32 swapped;
    for (index = 0; index < manager->count; index++) {
        Recovered_ChoiceOwner* object = manager->ordered[index];
        object->priority = func_001E2540(manager, object, first, second);
    }
    index = 0;
    do {
        result = (s32)((u32)manager->count - 1U);
        swapped = 0;
        if (result > 0) {
            do {
                Recovered_ChoiceOwner** pair = &manager->ordered[index];
                Recovered_ChoiceOwner* left = pair[0];
                Recovered_ChoiceOwner* right = pair[1];
                index++;
                if (left->priority < right->priority) {
                    pair[0] = right;
                    swapped = 1;
                    manager->ordered[index] = left;
                }
                result = manager->count;
            } while (index < (s32)((u32)result - 1U));
        }
        index = 0;
    } while (swapped);
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E26D0);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e1720", func_001E27D8);
