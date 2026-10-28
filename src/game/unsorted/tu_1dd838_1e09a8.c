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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E0E70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E0F28);
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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E11F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1dd838_1e09a8", func_001E1248);
