#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001ADD78(void *, s32, s32, s32);

s32 func_001ADF58(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    func_001ADD78((void *) (((s8 *) arg0) + 0xC), arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 1;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ADFC0);
