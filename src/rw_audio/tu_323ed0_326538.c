#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00310978(M2C_UNK *, s32, s32, s32, s32, s32);
extern M2C_UNK D_0045BF80;

void func_00326538(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00310978(&D_0045BF80, 0, arg1, arg0, arg2, arg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326570);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003265D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003266C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326848);
