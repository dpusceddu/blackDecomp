#include "auto/prelude.h"

void *func_0033AD90(void *arg0, s32 arg1, s32 arg2)
{
  int new_var;
  new_var = 0x110;
  M2C_FIELD(arg0, s32 *, 4) = 0x10;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((((((arg1 << 5) << 2) + new_var) + (arg2 << 7)) + (arg2 * 0x60)) + (arg2 * 0xD0)) + 0x2880);
  return arg0;
}
