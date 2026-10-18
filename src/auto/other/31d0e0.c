#include "auto/prelude.h"

extern s32 func_0035C544();

void *func_0031D0E0(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
  s32 new_var;
  new_var = M2C_FIELD(arg1, s32 *, 8);
  func_0035C544(arg3, (M2C_FIELD(arg0, s32 *, 0x4C)) + arg2, new_var);
  return arg0;
}
