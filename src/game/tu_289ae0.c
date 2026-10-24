#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018C2E0(s32, s32, s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00289C10);

void func_00289DA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0018C2E0(arg1, arg2, arg3);
}
