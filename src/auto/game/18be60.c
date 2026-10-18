#include "auto/prelude.h"

s32 func_0018BE60(s32 *arg0, void *arg1)
{
  s32 temp_6;
  int new_var;
  temp_6 = *arg0;
  new_var = temp_6 < 0x12;
  if (new_var)
  {
    if (arg1 || new_var)
    {
      M2C_FIELD(arg1, s32 *, 0) = temp_6;
      M2C_FIELD(arg1, s32 *, 4) = (s32) (*arg0);
      return 1;
    }
    else
    {
      M2C_FIELD(arg1, s32 *, 0) = temp_6;
      M2C_FIELD(arg1, s32 *, 4) = (s32) (*arg0);
      return 1;
    }
  }
  return 0;
}
