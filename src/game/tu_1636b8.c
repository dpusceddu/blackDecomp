#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00160EF8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001636B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001637C8);

void func_00163808(void *arg0)
{
  unsigned char new_var;
  func_00160EF8();
  new_var = 8;
  *((s32 *) ((0, ((s8 *) arg0) + 0x18))) = 0;
  M2C_FIELD(arg0, s32 *, 0x38) = new_var;
  M2C_FIELD(arg0, s32 *, 0x3C) = 0;
  M2C_FIELD(arg0, s32 *, 0x34) = 0;
  M2C_FIELD(arg0, s32 *, 0x30) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00163848);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001638F0);
