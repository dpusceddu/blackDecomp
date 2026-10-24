#include "ps2/prelude.h"

void func_0028BD68(s32 arg0)
{
  s32 temp_2;
  s32 temp_2_2;
  temp_2_2 = M2C_FIELD(arg0, s32 *, 0x10);
  temp_2_2 = M2C_FIELD(arg0, s32 *, 0x10);
  if (temp_2_2 != 0)
  {
    temp_2 = temp_2_2 + arg0;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_2;
  }
  return temp_2;
}
