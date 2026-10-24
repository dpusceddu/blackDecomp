#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00250058();
extern s32 D_0043DEE0;
extern s32 func_0035C6EC();
extern u16 D_003BFAF8;

s32 func_00252C58(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_16;
    s32 temp_2;

    if (arg2 != 0) {
        temp_16 = (arg2 + 0xC) & 0xFFFFFFFC;
        temp_2 = func_00250058(D_0043DEE0, temp_16);
        M2C_FIELD(arg0, s32 *, 0) = temp_2;
        M2C_FIELD(temp_2, s16 *, 0) = 1;
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), s16 *, 4) = (s16) (temp_16 - 9);
        func_0035C6EC(M2C_FIELD(arg0, s32 *, 0) + 8, arg1, arg2);
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), s16 *, 2) = (s16) arg2;
        M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), s16 *, 6) = 0;
        M2C_FIELD((M2C_FIELD(arg0, s32 *, 0) + arg2), s8 *, 8) = 0;
    } else {
        M2C_FIELD(arg0, s32 *, 0) = (s32) &D_003BFAF8;
        D_003BFAF8 += 1;
    }
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252D28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252E08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252E10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252F20);
