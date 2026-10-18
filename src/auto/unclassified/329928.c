#include "auto/prelude.h"

s32 func_00329928(void *arg0, s32 arg1, s32 arg2)
{
  u8 *new_var2;
  s32 temp_3;
  int new_var;
  new_var2 = (u8 *) (((s8 *) arg0) + 8);
  temp_3 = (1 << (*new_var2)) - ((char) 1);
  new_var = arg1 & temp_3;
  return ((arg2 & temp_3) - new_var) * (M2C_FIELD(arg0, s32 *, 0x14));
}
