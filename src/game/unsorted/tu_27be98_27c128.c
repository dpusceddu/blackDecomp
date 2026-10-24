#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0027C088(s32, s32, u32, u32);
extern s32 func_0027C1B0(s32, s8 *, s32, s8 *);

s32 func_0027C128(s32 arg0, s8 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_0027C088(arg0 + 4, arg2, (u32) arg3, (u32) arg4);
    func_0027C1B0(arg0, arg1, arg2, M2C_FIELD(arg0, s8 **, 0x2011C));
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C1A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C1A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C1B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C270);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0027C278);
