#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001A24B8();

s32 func_001A35A8(void *arg0)
{
  s8 *new_var;
  func_001A24B8();
  M2C_FIELD(arg0, s8 *, 0x82) = 0;
  new_var = (s8 *) (((s8 *) arg0) + 0x81);
  M2C_FIELD(arg0, s8 *, 0x80) = 0;
  *new_var = 1;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A35E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A36D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A37E8);
