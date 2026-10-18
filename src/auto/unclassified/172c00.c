#include "auto/prelude.h"

s32 func_00172C00(s32 arg0, s32 arg1, s32 arg2)
{
  s8 *new_var;
  new_var = (s8 *) (arg0 + (arg1 * 4));
  *((s32 *) (new_var + 0x64)) = arg2;
  return 1;
}
