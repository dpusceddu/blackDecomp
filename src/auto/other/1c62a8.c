#include "auto/prelude.h"

s32 func_001C62A8(s32 arg0)
{
  int new_var;
  s32 temp_2;
  s32 temp_2_2;
  temp_2 = M2C_FIELD(arg0, s32 *, 0x20);
  if (temp_2 != 0)
  {
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (temp_2 + arg0);
  }
  temp_2_2 = M2C_FIELD(arg0, s32 *, 0x24);
  new_var = 0xFF;
  if (temp_2_2 != 0)
  {
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (temp_2_2 + arg0);
  }
  M2C_FIELD(arg0, s8 *, 0x28) = new_var;
  new_var = new_var;
  return new_var;
}
