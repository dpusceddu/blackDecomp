#include "auto/prelude.h"

void func_0017BDC0(s32 arg0, s32 arg1, s32 arg2)
{
  u8 *temp_3;
  int new_var;
  new_var = arg0 + 0x80;
  temp_3 = new_var + arg1;
  *((s32 *) (((s8 *) (arg0 + (((*temp_3) * 4) + (arg1 << 6)))) + 0)) = arg2;
  *temp_3 += 1;
}
