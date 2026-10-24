#include "ps2/prelude.h"

s32 func_0023E830(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s32 *new_var2;
  s32 *new_var;
  f32 var_f0;
  s32 var_5;
  void *temp_6;
  new_var = (s32 *) (0 + ((s8 *) arg0));
  M2C_FIELD(arg0, s16 *, 0x18) = (s16) arg2;
  M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 4));
  *new_var = arg3;
  M2C_FIELD(arg0, u16 *, 0x1A) = (u16) (M2C_FIELD(arg1, u16 *, 0x38));
  temp_6 = arg1 + 4;
  new_var2 = (s32 *) (((s8 *) arg1) + 4);
  if ((*new_var2) & 4)
  {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (arg1 + 0x10);
    M2C_FIELD(arg0, s32 *, 4) = (s32) (arg1 + 0x10);
  }
  else
  {
    M2C_FIELD(arg0, s32 *, 4) = 0;
  }
  M2C_FIELD(arg0, s32 *, 8) = (s32) ((!((*new_var2) & 8)) ? (0) : (temp_6 + 0x24));
  var_5 = 0;
  if ((*new_var2) & 0x80)
  {
    var_5 = M2C_FIELD(temp_6, s32 *, 0x38);
  }
  M2C_FIELD(arg0, s32 *, 0xC) = var_5;
  var_f0 = 0.0f;
  if ((*new_var2) & 0x10)
  {
    var_f0 = M2C_FIELD(temp_6, f32 *, 0x2C);
  }
  M2C_FIELD(arg0, f32 *, 0x10) = var_f0;
  return arg0;
}
