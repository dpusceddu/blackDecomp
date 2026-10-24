#include "ps2/prelude.h"

extern s32 func_003107E0();

void *func_0031A548(void *arg0, s32 arg1, s32 *arg2)
{
  s32 temp_4;
  s32 var_3;
  s8 *new_var;
  temp_4 = M2C_FIELD(arg0, s32 *, 0x60);
  if ((temp_4 != 0) && ((*((u8 *) (new_var = ((s8 *) arg0) + 0x8A))) & 2))
  {
    var_3 = func_003107E0(temp_4, 9, 2, 0);
 do { } while (0);
  }
  else
  {
    var_3 = M2C_FIELD(arg0, s32 *, 0x6C);
  }
  M2C_FIELD(arg0, s32 *, 0x6C) = var_3;
  *arg2 = var_3;
  return arg0;
}
