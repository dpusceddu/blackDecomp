#include "auto/prelude.h"

void *func_0033A3B0(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var2;
  int new_var;
  new_var2 = ((s8 *) arg0) + 4;
  *((s32 *) new_var2) = 0x10;
  new_var = (arg1 << 7) + 0x100;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((new_var + (arg2 << 7)) + (arg2 * 0x60)) + 0x27E0);
  return arg0;
}
