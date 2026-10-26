#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/sequence.h"

extern s32 func_00165AE0();
extern void * func_00135550();
extern s32 func_0018D3A0();
extern void* func_00107D20();
extern s32 func_001749E8();
extern void func_00174C08();
extern s32 func_00183238(s32);
extern s32 func_00173F18();
extern s32 func_00183688();
extern s32 func_001736B8();
extern s32 func_00173EE0();

extern s32 func_00107BC0(void*, void*);
extern u8 D_0040F0F0[];
extern void* D_0040F4D4;
extern s32 func_0016DEF0(void*, s32, s32);
extern void func_00173E30(void*, s32, f32);
extern s32 func_0018DDD8(void*);
extern void func_00183618(void*, void*, void*);
extern void func_001736B0(void*);
extern void func_00178398(Recovered_SequenceSlot*);
extern void func_00178350(Recovered_SequenceSlot*, s128, f32);
extern u8 D_003DFFC8[];

void func_001749C8(void) {
    func_00165AE0();
}

s32 func_001749E8(void *arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, s64 *, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 0x18) = arg4;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    return 1;
}

void func_00174A00(s32 arg0, s64 *arg1) {
    s32 temp_17;

    if (arg1 != NULL) {
        temp_17 = M2C_FIELD(arg1, s32 *, 0xC4);
        if ((temp_17 == 1) && (func_00135550(arg1) != NULL) && (M2C_FIELD(func_00135550(arg1), s32 *, 0x80) == temp_17)) {
            func_0018D3A0(func_00135550(arg1) + 0xD10, arg0);
        }
    }
}

s32 Sequence_ClassifyStorage(void* address) {
    s32 kind = func_00107BC0(D_0040F0F0, address);
    if (kind == 2 || kind == 3) return 0;
    if (kind == 4 || kind == 5) return 1;
    return -1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174AD0);

u8 func_00174AD8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 8) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s32 *, 0x14)), u8 *, 4);
}

s32 func_00174AF0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(temp_2, s32 *, 0xC) + (M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_2, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 0x10);
}

f32 func_00174B20(void *arg0, s32 arg1, s32 arg2) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(((M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_3, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 4) + M2C_FIELD(temp_3, s32 *, 0x18)), f32 *, 0);
}

#ifdef NON_MATCHING
// Unmatched: actor-mask virtual-call register allocation differs.
void func_00174B58(void* self, void* actor) {
    Recovered_SequenceVirtual* methods;
    s32 bit = M2C_FIELD(actor, s32*, 0x1EF4);
    s32 mask = (s32)(0x10000u << bit) >> 16;
    M2C_FIELD(self, u16*, 0x1C) = mask | M2C_FIELD(self, u16*, 0x1C);
    methods = M2C_FIELD(self, Recovered_SequenceVirtual**, 0x10);
    methods[6].call((s8*)self + methods[6].adjustment, actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174B58);
#endif

void Sequence_RemoveActor(void* self, void* actor) {
    Recovered_SequenceVirtual* methods;
    /* The stored mask contains sixteen actor slots. */
    M2C_FIELD(self, u16*, 0x1C) &= ~((0x10000u << M2C_FIELD(actor, s32*, 0x1EF4)) >> 16);
    methods = M2C_FIELD(self, Recovered_SequenceVirtual**, 0x10);
    methods[7].call((s8*)self + methods[7].adjustment, actor);
}

void* func_00174BE8(s32 arg0, s32 arg1) { return func_00107D20(arg1); }

void Sequence_ShuffleIndices(void* self, s8* order, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) order[i] = i;
    if (count >= 2) {
        s32 last = count - 1;
        for (i = 0; i < 42; i++) {
            s32 first = func_0016DEF0(D_0040F4D4, 0, last);
            s32 second = func_0016DEF0(D_0040F4D4, 0, last);
            if (first != second) {
                s8 saved = order[first];
                order[first] = order[second];
                order[second] = saved;
            }
        }
    }
}

#ifdef NON_MATCHING
// Unmatched: record-index lifetime and saved-register allocation differ.
void func_00174CD8(s32 self, s32 table, s32 definition) {
    u8 entry;
    func_001749C8();
    entry = M2C_FIELD(definition, u8*, 0x44);
    if (entry != 0xFF) {
        M2C_FIELD(self, void**, 0x28) =
            func_00174BE8(self, M2C_FIELD((entry * 8) + M2C_FIELD(table, s32*, 0x14), u8*, 4));
        return;
    }
    M2C_FIELD(self, void**, 0x28) = NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174CD8);
#endif

s32 func_00174D48(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 2, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x44) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_00174DC8(void) {
    return 1;
}

void func_00174DD0(void) {
    func_001749C8();
}

s32 Sequence_InitializeSlots(Recovered_SequenceState* self, s64 owner, void* definition, s32 table) {
    s32 count;
    Recovered_SequenceSlot* slots;
    void* localState;
    func_001749E8(self, 1, owner, (s32)definition, table);
    self->definition = definition;
    if (M2C_FIELD(definition, u8*, 0x21) != 0xFF) {
        count = func_00174AD8(self, M2C_FIELD(definition, u8*, 0x21));
        localState = (s8*)self + 0x30;
        self->slotCount = count;
        slots = func_00107D20(count * sizeof(Recovered_SequenceSlot));
        {
            s32 remaining = count - 1;
            Recovered_SequenceSlot* slot = slots;
            if (count != 0) {
                do {
                    slot->unk_30 = D_003DFFC8;
                    remaining--;
                    slot++;
                } while (remaining != -1);
            }
        }
        self->slots = slots;
    } else {
        self->slotCount = 0;
        localState = (s8*)self + 0x30;
    }
    func_001736B8(localState, 7);
    func_00173E30(localState, M2C_FIELD(self->definition, u8*, 0x20), M2C_FIELD(self->definition, f32*, 0x18));
    self->active = NULL;
    return 1;
}

s32 func_00174ED8(void) {
    return 1;
}

void func_00174EE0(void *arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(M2C_FIELD(arg0, void **, 0x90), arg1);
}

#ifdef NON_MATCHING
// Unmatched: active-state test and float argument scheduling differ.
void func_00174F20(Recovered_SequenceState* self, void* actor) {
    func_00183238((s8*)actor + 0x1EB0);
    if (self->active == NULL) {
        if (func_0018DDD8((s8*)actor + 0xC94)) {
            self->active = (s8*)D_0040F4D4 + 0x22A30;
        } else {
            self->active = (s8*)self + 0x30;
        }
    }
    {
        f32 value = M2C_FIELD(self->definition, f32*, 0x18);
        s32 mode = M2C_FIELD(self->definition, u8*, 0x20);
        func_00173E30(self->active, mode, value);
    }
    func_00173EE0(self->active, actor);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174F20);
#endif

#ifdef NON_MATCHING
// Unmatched: slot-count lifetime removes a native copy and loop alignment.
s32 func_00174FB0(Recovered_SequenceState* self, Recovered_SequenceSlot* candidate) {
    s32 count = self->slotCount;
    s32 i = 0;
    if (count > 0) {
        Recovered_SequenceSlot* slot = self->slots;
        do {
            if (candidate == slot) return 1;
            i++;
            slot++;
        } while (i < count);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174FB0);
#endif

#ifdef NON_MATCHING
// Unmatched: record-index and byte-offset register allocation differ.
void func_00174FF0(Recovered_SequenceState* self) {
    s32 i;
    s32 offset;
    i = 0;
    if (self->slotCount > 0) {
        offset = 0;
        do {
            union {
                s128 native;
                f32 components[4];
            } value;
            s128* source = (s128*)func_00174AF0((s32)self, M2C_FIELD(self->definition, u8*, 0x21), i);
            i++;
            func_00178398((Recovered_SequenceSlot*)((s8*)self->slots + offset));
            value.native = *source;
            func_00178350((Recovered_SequenceSlot*)((s8*)self->slots + offset), value.native, value.components[3]);
            offset += sizeof(Recovered_SequenceSlot);
        } while (i < self->slotCount);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00174FF0);
#endif

#ifdef NON_MATCHING
// Unmatched: saved-register setup scheduling differs.
void func_00175090(s32 self, s32 table, s32 definition) {
    func_001749C8();
    M2C_FIELD(self, s32*, 0x48) = definition;
    func_00183618((void*)(self + 0x28), (void*)table, (void*)definition);
    func_001736B0((void*)(self + 0x50));
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00175090);
#endif

s32 func_001750E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 3, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    func_00183688(arg0 + 0x28, arg1, arg2);
    func_001736B8(arg0 + 0x50, 7);
    return 1;
}

s32 func_00175158(void) {
    return 1;
}

void func_00175160(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(arg0 + 0x50, arg1);
}

void func_001751A0(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173EE0(arg0 + 0x50, arg1);
}

#ifdef NON_MATCHING
// Unmatched: record-index lifetime and saved-register allocation differ.
void func_001751E0(s32 self, s32 table, s32 definition) {
    u8 entry;
    func_001749C8();
    entry = M2C_FIELD(definition, u8*, 0x27);
    if (entry != 0xFF) {
        M2C_FIELD(self, void**, 0x28) =
            func_00174BE8(self, M2C_FIELD((entry * 8) + M2C_FIELD(table, s32*, 0x14), u8*, 4));
        return;
    }
    M2C_FIELD(self, void**, 0x28) = NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_001751E0);
#endif

s32 func_00175250(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 4, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x27) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_001752D0(void) {
    return 1;
}

void func_001752D8(void) {
    func_001749C8();
}

s32 func_001752F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 5, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    return 1;
}

s32 func_00175340(void) {
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: record-index lifetime and saved-register allocation differ.
void func_00175348(s32 self, s32 table, s32 definition) {
    u8 entry;
    func_001749C8();
    entry = M2C_FIELD(definition, u8*, 0x33);
    if (entry != 0xFF) {
        M2C_FIELD(self, void**, 0x28) =
            func_00174BE8(self, M2C_FIELD((entry * 8) + M2C_FIELD(table, s32*, 0x14), u8*, 4));
        return;
    }
    M2C_FIELD(self, void**, 0x28) = NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_00175348);
#endif

s32 func_001753B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 6, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x33) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_00175438(void) {
    return 1;
}

void func_00175440(void) {
    func_001749C8();
}

s32 func_00175460(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 7, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    return 1;
}

s32 func_001754A8(void) {
    return 1;
}

#ifdef NON_MATCHING
// Unmatched: record-index lifetime and saved-register allocation differ.
void func_001754B0(s32 self, s32 table, s32 definition) {
    u8 entry;
    func_001749C8();
    entry = M2C_FIELD(definition, u8*, 0x2E);
    if (entry != 0xFF) {
        M2C_FIELD(self, void**, 0x28) =
            func_00174BE8(self, M2C_FIELD((entry * 8) + M2C_FIELD(table, s32*, 0x14), u8*, 4));
        return;
    }
    M2C_FIELD(self, void**, 0x28) = NULL;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1749c8", func_001754B0);
#endif

s32 func_00175520(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 8, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x2E) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}
