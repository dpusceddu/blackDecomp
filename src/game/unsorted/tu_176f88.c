#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00176F88(void *arg0)
{
  M2C_FIELD(arg0, s8 *, 0x10) = 0;
  arg0++;
  arg0--;
  M2C_FIELD(arg0, s32 *, 8) = 0;
  M2C_FIELD(arg0, s32 *, 4) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_176f88", func_00176FA8);
