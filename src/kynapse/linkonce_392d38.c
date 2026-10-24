#include "ps2/prelude.h"

void func_00392D38(void *arg0)
{
  long new_var;
  new_var = 0xBFF0;
  M2C_FIELD(arg0, s32 *, 0x14) = 0;
  M2C_FIELD(arg0, s64 *, 8) = (s64) (new_var << 0x30);
}
