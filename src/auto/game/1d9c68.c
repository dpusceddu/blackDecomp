#include "auto/prelude.h"

extern s32 func_001D9D00();

s32 func_001D9C68(s32 arg0, s32 arg1)
{
  unsigned int new_var;
  s32 temp_3;
  if (func_001D9D00(arg0, arg1) != 0)
  {
    return 0;
  }
  temp_3 = M2C_FIELD(arg0, s32 *, 0x14);
  new_var = (arg1 ^ 0) * 8;
  return ((M2C_FIELD(arg0, s32 *, 0x10)) + (temp_3 * (*((s32 *) (((s8 *) (arg0 + new_var)) + 4))))) + ((temp_3 * (M2C_FIELD(arg0, s32 *, 0x24))) * arg1);
}
