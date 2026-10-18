#include "auto/prelude.h"

extern M2C_UNK D_0040BEE8;

void *func_00370448(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  int new_var;
  new_var = 0;
  do
  {
  }
  while (new_var);
  M2C_FIELD(arg0, s32 *, 0) = arg1;
  M2C_FIELD(arg0, s32 *, 8) = arg2;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_0040BEE8;
  M2C_FIELD(arg0, s32 *, 0xC) = arg3;
  return arg0;
}
