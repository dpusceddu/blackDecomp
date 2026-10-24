#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204FF0();

void func_00206A28(void *arg0) {
    func_00204FF0();
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206A58);
