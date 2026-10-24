#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00353518();

s32 func_00353550(s32 arg0, s32 arg1, s32 arg2)
{
  s32 temp_2;
  s32 temp_3;
  s32 var_2;
  void *temp_7;
  temp_7 = arg0 + 0x30;
  temp_3 = M2C_FIELD(arg0, s32 *, 0x440);
  M2C_FIELD(arg1, s32 *, 0xC) = (M2C_FIELD(arg0, s32 *, 0x440) = arg1);
  M2C_FIELD(arg1, s32 *, 8) = arg1;
  if ((temp_3 != temp_7) && (arg2 != 0))
  {
    temp_2 = M2C_FIELD(temp_7, s32 *, 0xC);
    *((void **) (((s8 *) temp_3) + 8)) = temp_7;
    M2C_FIELD(temp_3, s32 *, 0xC) = temp_2;
    M2C_FIELD(temp_7, s32 *, 0xC) = temp_3;
    M2C_FIELD(temp_2, s32 *, 8) = temp_3;
  }
  var_2 = M2C_FIELD(arg0, s32 *, 0x478);
  if (var_2 == 0)
  {
    var_2 = func_00353518(arg0);
  }
  return var_2;
}
