#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_001C6AB8(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 0) = arg1;
  M2C_FIELD(arg0, s32 *, 4) = arg2;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6F10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C7438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C7748);
