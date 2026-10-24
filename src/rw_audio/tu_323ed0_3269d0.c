#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_003269D0(s32 arg0, void *arg1)
{
  s8 *new_var;
  M2C_FIELD(arg1, s32 *, 0) = 0x30;
  new_var = ((s8 *) arg1) + 4;
  *((s32 *) new_var) = 1;
  M2C_FIELD(arg1, s32 *, 8) = 1;
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003269F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326A28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326A60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00326A80);
