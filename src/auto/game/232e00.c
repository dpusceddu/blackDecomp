#include "auto/prelude.h"

s32 func_00232E00(void *arg0)
{
  s32 temp_3;
  temp_3 = ((s32) (((M2C_FIELD(arg0, s32 *, 8)) - (M2C_FIELD(arg0, s32 *, 4))) * 0xCCCCCCCD)) >> 2;
  if (temp_3 < 0)
  {
    if (temp_3)
    {
      return temp_3 + (M2C_FIELD(arg0, s32 *, 0x10));
    }
    else
    {
      return temp_3 + (M2C_FIELD(arg0, s32 *, 0x10));
    }
  }
  if (!temp_3)
  {
  }
  return temp_3;
}
