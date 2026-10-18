#include "auto/prelude.h"

extern s32 func_0014B948();
extern void *func_00108120();
extern s32 D_0040F4C4;

s32 func_0014B8E0(void *arg0, void *arg1, unsigned char arg2)
{
  s64 new_var;
  s8 *new_var2;
  new_var2 = ((s8 *) arg0) + 0xD8;
  *((void **) new_var2) = arg1;
  new_var = M2C_FIELD(arg1, s64 *, 0x48);
  M2C_FIELD(arg0, s64 *, 0) = (s64) new_var;
  func_0014B948(arg0, func_00108120(D_0040F4C4, M2C_FIELD(arg1, s64 *, 0x40)), arg2 & 0xFF, *((void **) new_var2));
  M2C_FIELD(arg0, s8 *, 0xEE) = 0;
  return 1;
}
