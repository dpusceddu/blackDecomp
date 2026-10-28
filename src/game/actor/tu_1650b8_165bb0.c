#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165DF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00165F30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00166808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167208);
extern void func_00167AA8(void *, void *, s64);

s32 func_00167A10(void *arg0, void *arg1, void *arg2) {
    s32 i;
    u8 result = M2C_FIELD(arg1, u8 *, 0xE);
    if (result == 0 && arg2 != 0) {
        i = 0;
        if (M2C_FIELD(arg2, u8 *, 4) != 0) {
            do {
                s64 *entry = (s64 *) (i * 8 + M2C_FIELD(arg2, s32 *, 0));
                i++;
                func_00167AA8(arg0, arg1, *entry);
            } while (i < M2C_FIELD(arg2, u8 *, 4));
        }
        result = 1;
        M2C_FIELD(arg1, u8 *, 0xE) = 1;
    }
    return result;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00167AA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00168618);
#ifdef NON_MATCHING
// Unmatched: setup copies and cursor registers differ (17 instructions under O2).
void* func_00169898(void* state, s64 key) {
    s64** entries;
    entries = M2C_FIELD(state, s64***, 0x48);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x0);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    entries = M2C_FIELD(state, s64***, 0x4C);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x2);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169898);
#endif
#ifdef NON_MATCHING
// Unmatched: setup copies and cursor registers differ (17 instructions under O2).
void* func_00169920(void* state, s64 key) {
    s64** entries;
    entries = M2C_FIELD(state, s64***, 0x70);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x14);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    entries = M2C_FIELD(state, s64***, 0x74);
    if (entries) {
        u16 count = M2C_FIELD(state, u16*, 0x16);
        s32 i = 0;
        if (count) {
            s64** cursor = entries;
            do {
                s64* entry = *cursor;
                i++;
                if (key == *entry) return entry;
                cursor++;
            } while (i < count);
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169920);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001699A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00169AA0);
void func_00169B88(void* state) {
    s32 i;
    for (i = 0; i < M2C_FIELD(state, u16*, 0x44); i++) {
        void* entry = M2C_FIELD(state, void***, 0xD0)[i];
        M2C_FIELD(entry, s8*, 0x11C) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D7F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016D958);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016DC80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E7A8);
extern s128 D_004432A0;
void func_0016E7F8(void* arg0) {
    void* base = (char*)arg0 + 0x20000;
    s128 value;
    M2C_FIELD(base, s32*, 0x2BCC) = 0;
    value = D_004432A0;
    M2C_FIELD(base, s32*, 0x2BD0) = 0;
    M2C_FIELD(base, s128*, 0x2BE0) = value;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E820);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0016E928);
typedef struct {
    void** entries;
    u8* occupied;
    s32 count;
} Recovered_ActorPool;

extern void* func_00107D20(u32);

void func_0016EA10(Recovered_ActorPool* pool, s32 count) {
    s32 i;
    pool->count = count;
    pool->entries = func_00107D20(count * 4);
    pool->occupied = func_00107D20(pool->count);
    for (i = 0; i < pool->count; i++) pool->entries[i] = 0;
}
void* func_0016EAD0(Recovered_ActorPool* pool) {
    s32 i;
    for (i = 0; i < pool->count; i++) {
        if (!pool->occupied[i]) {
            pool->occupied[i] = 1;
            return pool->entries[i];
        }
    }
    return 0;
}
void func_0016EB28(Recovered_ActorPool* pool, void* entry) {
    s32 i;
    for (i = 0; i < pool->count; i++) {
        if (pool->entries[i] == entry) {
            pool->occupied[i] = 0;
            return;
        }
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00171ED0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001721E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001722A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001740A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00174930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176310);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176EE0);
typedef struct {
    s32 unk_00, unk_04, unk_08, unk_0C;
    s8 pending;
} Recovered_PairState;

void func_00176FB0(Recovered_PairState* state, s32 first, s32 second) {
    if (state->pending == 0) {
        state->unk_00 = first;
        state->unk_08 = second;
        state->pending = 1;
    } else {
        state->unk_04 = first;
        state->unk_0C = second;
        state->pending = 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00176FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177030);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001770E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177A70);
s32 func_00177AA0(void* state, s32 value) {
    if (M2C_FIELD(state, s32*, 0x28) == value) return 1;
    if (M2C_FIELD(state, s32*, 0x28) != 0) return 0;
    M2C_FIELD(state, s32*, 0x28) = value;
    return 1;
}

s32 func_00177B48(void* state, s32 bit) {
    u32 mask = 1U << bit;
    return (~(M2C_FIELD(state, u32*, 0x14) | M2C_FIELD(state, u32*, 0x18)) & mask) != 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177C90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00177D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001793C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_00179BD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017A9F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AB40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AF20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_0017AFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A7F88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A80F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1650b8_165bb0", func_001A8350);
