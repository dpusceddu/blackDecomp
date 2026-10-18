#include "auto/prelude.h"

extern s32 func_00107D20();

void func_00155088(void *arg0, s8 arg1)
{
  M2C_FIELD(arg0, s8 *, 0x18) = arg1;
  if (1)
  {
  }
 do { M2C_FIELD(arg0, s32 *, 0x14) = func_00107D20(arg1, arg1); } while (0);
}
