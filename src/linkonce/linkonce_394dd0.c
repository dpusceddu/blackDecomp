#include "auto/prelude.h"

extern s32 D_003CE59C;

u8 func_00394DD0(s32 arg0, s32 arg1, s32 arg2)
{
  s32 var_5;
  if (!(arg2 >= arg1))
  {
    var_5 = (((s32) (arg1 * (arg1 - 1))) / 2) + arg2;
 if (0) { }
  }
  else
  {
    var_5 = (((s32) (arg2 * (arg2 - 1))) / 2) + arg1;
  }
  return *((u8 *) (((s8 *) (D_003CE59C + var_5)) + 0));
}
