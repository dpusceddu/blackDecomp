#include "auto/prelude.h"

extern s32 func_0028BB68();
extern s32 func_0028BB80();

s32 func_0028BBA0(s32 arg0)
{
  s32 temp_2;
  u8 temp_17;
  s32 new_var;
  temp_17 = M2C_FIELD(arg0, u8 *, 0xE);
  temp_2 = M2C_FIELD(arg0, s32 *, 4);
  M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 0));
  *((s32 *) (((s8 *) ((unsigned long) arg0)) + 0)) = temp_2;
  new_var = (s32) (temp_17 >> 4);
  func_0028BB68(arg0, (temp_17 & 0xFFFFFFFFFFFFFFFF) & 0xF);
  return func_0028BB80(arg0, new_var);
}
