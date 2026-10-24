#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00271650(void *);
extern s32 func_00294A08();

s32 func_00271BE8(s32 *arg0) {
    s32 *var_16;

    var_16 = arg0;
    do {
        func_00271650(var_16);
        var_16 = (s32 *) (((s8 *) var_16) + 0x18);
    } while ((s32) var_16 < (s32) ((s32 *) (((s8 *) arg0) + 0x30)));
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
    M2C_FIELD(arg0, s32 *, 0x120) = 1;
    return func_00294A08();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00271C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00271F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002721D8);
