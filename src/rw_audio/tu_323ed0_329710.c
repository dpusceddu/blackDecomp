#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00329750();

s32 func_00329710(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_3;
    s32 temp_8;
    u8 temp_6;

    temp_6 = M2C_FIELD(arg0, u8 *, 8);
    temp_3 = M2C_FIELD(arg1, s32 *, 0);
    temp_2 = (1 << temp_6) - 1;
    temp_8 = ~temp_2;
    return func_00329750(arg0, temp_3 & temp_2, (s32) ((u32) (temp_3 & temp_8) >> temp_6), 0, temp_8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329710", func_00329750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_323ed0_329710", func_00329848);
