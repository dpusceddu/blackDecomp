#include "ps2/prelude.h"

extern M2C_UNK D_0040BEE8;

void func_00370140(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  M2C_UNK *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) arg0;
  if (arg0 != NULL)
  {
    M2C_FIELD(arg0, s32 *, 0xC) = arg3;
    new_var = &D_0040BEE8;
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    *((M2C_UNK **) (new_var2 + 4)) = new_var;
    M2C_FIELD(arg0, s32 *, 8) = arg2;
  }
}
