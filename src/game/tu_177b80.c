#include "auto/prelude.h"

s32 func_00177B80(void *arg0, s32 arg1)
{
  int new_var;
  new_var = 1 << arg1;
  return ((M2C_FIELD(arg0, s32 *, 0x18)) & new_var) != 0;
}
