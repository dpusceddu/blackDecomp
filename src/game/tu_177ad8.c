#include "auto/prelude.h"

s32 func_00177AD8(void *arg0, s32 arg1)
{
  s32 new_var;
  return (new_var = ((M2C_FIELD(arg0, s32 *, 0x14)) & (~(M2C_FIELD(arg0, s32 *, 0x18)))) & (1 << (new_var = arg1))) != 0;
}
