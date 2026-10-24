#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 D_0047EA08;

s32 func_0035B6D0(s32 arg0, s32 arg1, s32 arg2)
{
  void *temp_7;
  temp_7 = ((s32) (&D_0047EA08)) + (arg0 * 0x24);
  *((s32 *) (((s8 *) (((s32) (&D_0047EA08)) + (arg0 * 0x24))) + 0x1C)) = arg1;
  *((s32 *) (((s8 *) (((s32) (&D_0047EA08)) + (arg0 * 0x24))) + 0x20)) = arg2;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B6F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035B910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BA10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BBD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BD10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BE18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035BFD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C160);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C298);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C2D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C308);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0035C428);

s32 func_0035C470(s32 arg0) {
    s32 temp_4;

    temp_4 = arg0 * 0x24;
    if (M2C_FIELD((temp_4 + ((s32) &D_0047EA08)), s32 *, 0) == 0) {
        return -1;
    }
    return M2C_FIELD((((s32) &D_0047EA08) + temp_4), s32 *, 4);
}
