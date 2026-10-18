#include "auto/prelude.h"

extern s32 func_0035C6EC();

void func_0027B648(void *arg0, s32 arg1, s32 arg2)
{
  M2C_FIELD(arg0, s32 *, 8) = arg1;
  M2C_FIELD(arg0, s32 *, 0xC) = arg2;
  M2C_FIELD(arg0, s32 *, 0) = (M2C_FIELD(arg0, s32 *, 4) = 0);
  func_0035C6EC(arg1, 0, arg2 << 5);
}
