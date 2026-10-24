#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00153690(void *arg0)
{
  s8 *new_var;
  *((s32 *) (new_var = ((s8 *) arg0) + 0x10)) = 0;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 4) = 0;
  M2C_FIELD(arg0, s32 *, 8) = 0;
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
  return 1;
}
