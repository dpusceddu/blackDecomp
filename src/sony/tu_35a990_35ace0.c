#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern M2C_UNK D_0047A1C0;
extern s32 func_0035ACA0(s32, void *, s32, s32);

s32 func_0035ACE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 *temp_16;
    s32 *temp_17;
    s32 temp_6;
    s32 temp_7;
    s32 var_2;

    temp_7 = arg0 * 0x2010;
    temp_17 = temp_7 + ((s32) &D_0047A1C0);
    temp_6 = *temp_17;
    var_2 = 1;
    if (temp_6 != -1) {
        temp_16 = temp_7 + (((s32) &D_0047A1C0) + 0xC);
        var_2 = func_0035ACA0(arg0, temp_7 + (((s32) &D_0047A1C0) + 0x10), temp_6, *temp_16);
        *temp_17 = -1;
        *temp_16 = 0;
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035AD50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B0E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B2B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B2F8);
