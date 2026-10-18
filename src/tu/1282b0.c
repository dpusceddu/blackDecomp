#include "auto/prelude.h"

s32 func_001282B0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xD0);
}

void func_001282B8(void *arg0)
{
  s8 *new_var;
  int new_var2;
  new_var = (s8 *) arg0;
  new_var2 = 0xFFFF;
  *((s16 *) (new_var + 0xD8)) = new_var2;
}
