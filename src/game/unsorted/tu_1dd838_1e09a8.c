#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"

#include "ps2/recovered_types.h"
extern void * func_00280680(s32, s32);
extern s32 D_0040F510;
extern void * D_0040F4D0;

s32 func_001E09A8(void *arg0, void *arg1) {
    s128 temp_vf1;
    s128 temp_vf1_2;
    s128 temp_vf1_3;
    s32 var_4;

    temp_vf1 = M2C_FIELD(func_00280680(D_0040F510 + 0xCB7C, 0), s128 *, 0x30);
    var_4 = 1;
    temp_vf1_2 = __ee_vu_sub_keep(temp_vf1, temp_vf1, (s128) M2C_FIELD(arg1, s128 *, 0x20));
    temp_vf1_3 = __ee_vu_mul_keep(temp_vf1_2, temp_vf1_2, temp_vf1_2);
    if (!(__ee_vu_read_x(__ee_vu_sum_keep(temp_vf1_3, temp_vf1_3, __ee_vu_one())) < M2C_FIELD(M2C_FIELD(D_0040F4D0, void **, 0x5AEC), f32 *, 0x344))) {
        var_4 = 0;
    }
    return var_4;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E0A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E0D28);
#ifdef NON_MATCHING
// Unmatched: self and loop index use opposite registers.
#include "game/effects/random_state.h"
extern BkEffectRandomStatePS2 D_0040EB30;
s32 func_001E0E70(void* self) {
    u32 i = 0;
    u32 count = M2C_FIELD(self, u32*, 0x2410);
    if (count) {
        u8* entry = (u8*)self + 0xD0;
        do {
            if (!M2C_FIELD(entry, u8*, 0x44)) {
                u8* base = M2C_FIELD(M2C_FIELD(self, void**, 0x2424), u8**, 0x34) + (M2C_FIELD(entry, s32*, 0x40) << 4);
                if (M2C_FIELD(entry, u8*, 0x45)) {
                    u32 first = D_0040EB30.state;
                    u32 second = D_0040EB30.accumulator;
                    u32 next = (first << 16) + ((s32)first >> 16) + second;
                    D_0040EB30.state = next;
                    D_0040EB30.accumulator = second + next;
                    M2C_FIELD(entry, u8*, 0x44) = (next & 0xFF) >= M2C_FIELD(base + M2C_FIELD(entry, s32*, 0x34), u8*, 8);
                } else {
                    M2C_FIELD(entry, u8*, 0x44) = 0;
                }
            }
            i++;
            count = i < M2C_FIELD(self, u32*, 0x2410);
            entry += 0x50;
        } while (count);
    }
    return count;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E0E70);
#endif
// UNVERIFIED: request type identity; the observed copy covers 16 bytes.
typedef struct { u32 data[4]; } Recovered_EffectRequest;
extern void* func_001E1100(Recovered_EffectRequest*, void*, void*);
extern s32 func_001E0820(void*, Recovered_EffectRequest*, void*, s32);
s32 func_001E0F28(void* self) {
    u32 count = M2C_FIELD(self, u32*, 0x2410);
    u32 i = 0;
    if (count) {
        s32 one = 1;
        u8* entry = (u8*)self + 0xD0;
        do {
            if (!M2C_FIELD(entry, u8*, 0x44)) {
                Recovered_EffectRequest request;
                Recovered_EffectRequest temporary;
                s32 result;
                func_001E1100(&temporary, self, entry);
                request = temporary;
                result = func_001E0820(self, &request, entry, one);
                M2C_FIELD(entry, s32*, 0x40) = result;
                if (result < 0) M2C_FIELD(entry, u8*, 0x44) = one;
            }
            i++;
            count = i < M2C_FIELD(self, u32*, 0x2410);
            entry += 0x50;
        } while (count);
    }
    return count;
}
extern void func_001E16E0(void*);
s32 func_001E0FE8(void* self) {
    u8* entry = (u8*)self + 0x14D0;
    u8* active = (u8*)self + 0x14E8;
    u32 i = 0;
    s32 again;
    M2C_FIELD(self, s32*, 0x2414) = 0;
    do {
        if (*active) {
            func_001E16E0(entry);
            M2C_FIELD(self, s32*, 0x2414)++;
        }
        i++;
        entry += 0x1C;
        again = i < 0x80;
        active += 0x1C;
    } while (again);
    return again;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E1100);
#ifdef NON_MATCHING
// Unmatched: loop return-path scheduling differs.
extern f32 D_003BD390[];
s32 func_001E11F8(void* self, f32 value) {
    s32 i = 0;
    f32* threshold = D_003BD390;
    do {
        s32 next = i + 1;
        if (value <= *threshold) return i;
        threshold++;
        i = next;
        if (next >= 4) return next;
    } while (1);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E11F8);
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E1248);
