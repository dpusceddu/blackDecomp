#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/vu0_lowering.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0E70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0F28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E0FE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E10C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1100);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E11F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1690);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E16E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1708);
