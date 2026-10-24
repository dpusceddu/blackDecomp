#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

s32 func_003176D0(s32 arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_2 + arg0);
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003176E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00317838);
