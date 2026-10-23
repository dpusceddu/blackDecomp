#include "auto/prelude.h"

s32 func_003916F0(void *arg0)
{
  int new_var;
  new_var = 2;
  return ((M2C_FIELD(arg0, s32 *, 4)) & new_var) != 0;
}

s32 func_00391700(void *arg0)
{
  int new_var3;
  int new_var;
  s8 *new_var2;
  new_var = 4;
  new_var2 = ((s8 *) arg0) + new_var;
  new_var3 = 0;
  return ((*((s32 *) new_var2)) & new_var) != new_var3;
}

s32 func_00391710(void *arg0)
{
  int new_var;
  new_var = 8;
  return ((M2C_FIELD(arg0, s32 *, 4)) & new_var) != 0;
}

s32 func_00391720(void *arg0)
{
  unsigned char new_var;
  s32 new_var2;
  if ((arg0 && arg0) && arg0)
  {
  }
  new_var2 = M2C_FIELD(arg0, s32 *, 4);
  new_var = new_var2 & 0x10;
  return new_var != 0;
}
