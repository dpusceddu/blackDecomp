#include "ps2/prelude.h"

void func_00149BE8(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_7;
  s32 new_var;
  u8 var_2;
  arg1 = arg1;
  arg1 = arg1 * 2;
  temp_7 = arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC));
  var_2 = *temp_7;
  new_var = M2C_FIELD(arg0, s32 *, 0x1AC);
  if (var_2 == 0)
  {
    *temp_7 = 1;
    ;
    *((s8 *) ((arg1 + (M2C_FIELD(arg0, s32 *, 0x1AC))) + 1)) = (s8) arg2;
  }
  return (s32) (arg1 + new_var);
}
