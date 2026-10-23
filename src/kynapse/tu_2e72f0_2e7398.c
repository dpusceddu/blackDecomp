#include "auto/prelude.h"

s32 func_002E7398(s32 arg0, s32 *arg1)
{
  int new_var2;
  int new_var;
  s8 *new_var3;
  new_var = (*arg1) * 4;
  new_var2 = arg0 + new_var;
  new_var3 = ((s8 *) new_var2) + 4;
  return *((s32 *) new_var3);
}
