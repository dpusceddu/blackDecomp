#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0014EF58();

void * func_0014EEF0(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7, s8 arg_sp0, s8 arg_sp8) {
    M2C_FIELD(arg0, s64 *, 0) = (s64) arg1;
    M2C_FIELD(arg0, void **, 0x158) = arg2;
    M2C_FIELD(arg0, s8 *, 0x153) = arg_sp8;
    M2C_FIELD(arg0, s8 *, 0x152) = 0;
    M2C_FIELD(arg0, s16 *, 0x150) = 0;
    M2C_FIELD(arg0, s8 *, 0x154) = 0;
    M2C_FIELD(arg0, s8 *, 0x155) = 0;
    return func_0014EF58(arg0, arg3, (void *) ((s32) arg4 & 0xFF), arg5, arg6, (void *) (s16) arg7, (void *) arg_sp0, (void *) arg_sp8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_14eef0", func_0014EF50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_14eef0", func_0014EF58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_14eef0", func_0014F028);
