#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00179BD0(void *, s32);

void func_00191C48(void *arg0) {
    func_00179BD0(arg0 + 0xA0, M2C_FIELD(arg0, s32 *, 0x34));
    func_00179BD0(arg0 + 0x110, M2C_FIELD(arg0, s32 *, 0x34));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191C80);
