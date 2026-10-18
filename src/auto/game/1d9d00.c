#include "auto/prelude.h"

s32 func_001D9D00(void *arg0, s32 arg1)
{
  s32 *new_var;
  s8 *new_var2;
  new_var = &(M2C_FIELD(arg0, s32 *, 0x24));
  new_var2 = (s8 *) (arg0 + (arg1 * 8));
  return (*((s32 *) (new_var2 + 4))) == (*new_var);
}
