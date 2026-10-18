#include "auto/prelude.h"

extern s32 func_00107AB8();

s32 func_00107A40(s32 arg0)
{
  s32 temp_2;
  M2C_FIELD(arg0, s8 *, 0x3B8) = 1;
  M2C_FIELD(arg0, s32 *, 0x3AC) = 0;
  M2C_FIELD(arg0, s32 *, 0x3B4) = -1;
  temp_2 = func_00107AB8(arg0, 0, 0);
  M2C_FIELD(arg0, s8 *, 0) = 0;
  return temp_2;
}
