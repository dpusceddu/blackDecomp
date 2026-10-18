#include "auto/prelude.h"

extern s32 func_0013EE28();

s32 func_0013F298(void *arg0)
{
  int new_var;
  new_var = 0x98;
  func_0013EE28();
  M2C_FIELD(arg0, s8 *, 0x9D) = (*((s32 *) (((s8 *) arg0) + new_var)) = 0);
  return 1;
}
