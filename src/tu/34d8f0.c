#include "auto/prelude.h"

extern s32 func_00347430(s32, s32, s32);
extern s32 func_0034B910();

s32 func_0034D8F0(void *arg0)
{
  s32 (*temp_2)();
  s32 new_var;
  temp_2 = *((s32 (**)()) (((s8 *) arg0) + 0x9C0));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0)
  {
    new_var = temp_2();
    return new_var;
  }
  else
  {
    new_var = temp_2();
    return new_var;
  }
}

void func_0034D920(s32 arg0, s32 arg1) {
    func_00347430(arg0, func_0034B910(), arg1);
}
