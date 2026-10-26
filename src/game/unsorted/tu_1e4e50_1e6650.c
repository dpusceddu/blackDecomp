#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"
#include "game/playback_state_pool.h"

extern void * func_001E51E0();
extern s32 func_001E63B8();
extern void * D_0040F4D0;
extern s32 func_00135550();
extern s32 func_001848C0();
extern Recovered_PlaybackServices* D_0040F510;
extern void* func_001D8478(void*);
extern void func_001D84C8(void*, void*);
extern s32 D_003BD4D0;
/* The callee return width is UNVERIFIED; this caller consumes its low byte. */
extern s8 func_001E60A8(void*, u64);

/* Partial slot pool; the capacity and slot meanings are UNVERIFIED. */
typedef struct Recovered_SlotPool {
    void* unk_00[18];
    u8 unk_48[20];
    s32 unk_5C;
    s16 unk_60;
    u16 unk_62;
} Recovered_SlotPool;
typedef char RecoveredSlotPointerIs32[(sizeof(void*) == 4) ? 1 : -1];

/* Partial state initialized with a slot pool; other fields are UNVERIFIED. */
typedef struct Recovered_PoolState {
    s32 unk_00;
    Recovered_SlotPool* unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 unk_10[4];
    u32 unk_14;
    u8 unk_18[8];
    u8 unk_20;
    u8 unk_21[3];
    s32 unk_24;
    u8 unk_28[4];
    f32 unk_2C;
    s32 unk_30;
    s32 unk_34;
} Recovered_PoolState;

/* Partial playback owner; field meanings outside the matched calls are UNVERIFIED. */
typedef struct Recovered_PlaybackOwner {
    u8 unk_00[0xB0];
    void* unk_B0[1];
    void* unk_B4[1];
    Recovered_PlaybackState* unk_B8;
    u8 unk_BC;
} Recovered_PlaybackOwner;

void* func_001E69E8(Recovered_SlotPool*);
void func_001E6A40(Recovered_SlotPool*, void*);

s32 func_001E6650(void *arg0, s32 arg1, s64 arg2, s32 arg3) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = arg2;
    if ((M2C_FIELD(arg0, u8 *, 0x184) == 0) && (func_001E51E0(M2C_FIELD(arg0, void **, 0x16C), arg0 + 0x160, sp) != NULL)) {
        M2C_FIELD(arg0, s32 *, 0x168) = arg1;
        func_001E63B8(arg0, *(s64 *)(sp + 0), arg3);
        M2C_FIELD(arg0, s32 *, 0x180) = arg3;
        M2C_FIELD(arg0, s64 *, 0x178) = *(s64 *)(sp + 0);
        M2C_FIELD(arg0, u8 *, 0x184) = 1U;
        M2C_FIELD(arg0, f32 *, 0x174) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    }
    return 0;
}

s32 func_001E66F0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 1;
    return arg0;
}

void func_001E6700(Recovered_PlaybackOwner* owner, u64 key) {
    u32 index;
    owner->unk_B8 = PlaybackStatePool_Acquire(D_0040F510->playbackPools.states, key);
    for (index = 0; index < 1; index++) { owner->unk_B4[index] = 0; }
    for (index = 0; index < 1; index++) {
        owner->unk_B0[index] = func_001E69E8(M2C_FIELD(D_0040F510->playbackPools.unk_4BD8, Recovered_SlotPool**, 4));
    }
    owner->unk_BC = 0;
}
void func_001E67B8(Recovered_PlaybackOwner* owner) {
    u32 index;
    for (index = 0; index < 1; index++) { owner->unk_B4[index] = 0; }
    for (index = 0; index < 1; index++) {
        func_001E6A40(M2C_FIELD(D_0040F510->playbackPools.unk_4BD8, Recovered_SlotPool**, 4), owner->unk_B0[index]);
        owner->unk_B0[index] = 0;
    }
    PlaybackStatePool_Release(D_0040F510->playbackPools.states, owner->unk_B8);
    owner->unk_B8 = 0;
}
#ifdef NON_MATCHING
// Unmatched: pool and index use swapped saved registers.
void func_001E6878(Recovered_SlotPool* pool) {
    int index = 0;
    M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), s8*, 0x19) = 9;
    pool->unk_60 = M2C_FIELD(M2C_FIELD(D_0040F4D0, void**, 0x5AEC), s8*, 0x19) + 6;
    if (pool->unk_60 > 0) {
        u8* used = pool->unk_48;
        void** slot = pool->unk_00;
        do {
            *slot = func_001D8478(M2C_FIELD(D_0040F510, void**, 0xCBD4));
            used[index] = 0;
            index++;
            slot++;
        } while (index < pool->unk_60);
    }
    pool->unk_5C = 0;
    pool->unk_62 = pool->unk_60;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6878);
#endif
void func_001E6948(Recovered_SlotPool* pool) {
    int index;
    for (index = 0; index < pool->unk_60; index++) {
        func_001D84C8(M2C_FIELD(D_0040F510, void**, 0xCBD4), pool->unk_00[index]);
    }
    pool->unk_5C = 1;
    pool->unk_62 = pool->unk_60;
}

s16 func_001E69E0(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0x62);
}

void* func_001E69E8(Recovered_SlotPool* pool) {
    int index;
    for (index = 0; index < pool->unk_60; index++) {
        if (pool->unk_48[index] == 0) {
            pool->unk_48[index] = 1;
            pool->unk_62--;
            return pool->unk_00[index];
        }
    }
    return 0;
}

void func_001E6A40(Recovered_SlotPool* pool, void* object) {
    int index = 0;
    if (pool->unk_60 > 0) {
        u8* used = pool->unk_48;
        void** slot = pool->unk_00;
        do {
            if (*slot == object) {
                used[index] = 0;
                pool->unk_62++;
                return;
            }
            index++;
            slot++;
        } while (index < pool->unk_60);
    }
}
void func_001E6A98(Recovered_PoolState* state, u32 value) {
    void* pools = D_0040F510->playbackPools.unk_4BD8;
    Recovered_SlotPool* slot_pool = M2C_FIELD(pools, Recovered_SlotPool**, 4);
    state->unk_14 = value;
    state->unk_04 = slot_pool;
    state->unk_24 = -1;
    state->unk_2C = 0.5f;
    state->unk_08 = 0;
    state->unk_0C = 0;
    D_003BD4D0 = 0;
    state->unk_30 = 0;
    state->unk_34 = 0;
    state->unk_00 = 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6AF0);

s32 func_001E6AF8(s32 arg0, void *arg1) {
    s32 temp_2;

    if (((M2C_FIELD(arg1, s32 *, 0x38C) ^ 1) != 0) && (func_00135550(arg1) != 0)) {
        temp_2 = func_001848C0(func_00135550(arg1) + 0x6F0);
        return (func_001E6B70(arg0, temp_2) == 0) ? 0 : temp_2;
    }
    return 0;
}

s32 func_001E6B70(s32 arg0, void *arg1) {
    s32 var_2;

    var_2 = 0;
    if (arg1 != NULL) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x348) != 0;
    }
    return var_2;
}

/* The meanings of these 64-bit keys are UNVERIFIED. */
s32 func_001E6B88(void* owner, u64 key) { return key == 0x81F2D7A540000000UL || key == 0x8218186380000000UL; }
s32 func_001E6BD0(Recovered_PoolState* state, void* unused, u64 key) {
    s8 found = func_001E60A8(state->unk_04, key);
    state->unk_20 = found;
    if (found & 0xFF) {
        s32 allowed = ((u32)state->unk_00 - 3U) >= 2U;
        if (allowed) { return 1; }
    } else {
        if (state->unk_00 == 0) { return 1; }
    }
    return 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E6E50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1e4e50_1e6650", func_001E7078);

s32 func_001E7118(void *arg0) {
    s32 var_5;

    var_5 = 1;
    if (!((M2C_FIELD(arg0, f32 *, 0x30) + M2C_FIELD(arg0, f32 *, 0x34)) < M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_5 = 0;
    }
    return var_5;
}


void func_001E75F0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 1;
}
