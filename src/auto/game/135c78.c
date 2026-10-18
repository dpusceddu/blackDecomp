#include "auto/prelude.h"

extern void func_00143590();

s32 func_00135C78(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s8 *new_var;
  new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x25C;
  func_00143590(*((void **) new_var), arg2, arg3 & 0xFF);
  M2C_FIELD(arg0, s8 *, 0x3AD) = 1;
  return 1;
}
