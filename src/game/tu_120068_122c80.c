#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_00122C80(void *arg0) {
    s32 var_3;
    void *var_2;

    M2C_FIELD(arg0, s32 *, 0x1A0) = 0;
    var_3 = 3;
    M2C_FIELD(arg0, s32 *, 0x1A4) = 0;
    var_2 = (void *) (((s8 *) arg0) + 0x1BB);
    M2C_FIELD(arg0, s32 *, 0x1A8) = 0;
    M2C_FIELD(arg0, s32 *, 0x1AC) = 0;
    M2C_FIELD(arg0, s32 *, 0x1B0) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B4) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B5) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B6) = 0;
    do {
        M2C_FIELD(var_2, s8 *, -4) = 0;
        var_3 -= 1;
        M2C_FIELD(var_2, s8 *, 0) = 0;
        var_2 = (void *) (((s8 *) var_2) + 1);
    } while (var_3 >= 0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00122CC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00122D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00122D48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00122D98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00122DE0);
