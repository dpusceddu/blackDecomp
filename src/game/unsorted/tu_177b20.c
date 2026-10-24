#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00177B20(void *arg0, s32 arg1)
{
  int new_var;
  new_var = 0;
  return (((~(M2C_FIELD(arg0, s32 *, 0x14))) & (M2C_FIELD(arg0, s32 *, 0x18))) & (1 << arg1)) != new_var;
}
