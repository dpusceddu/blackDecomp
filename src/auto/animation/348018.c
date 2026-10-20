#include "auto/prelude.h"
#include "mod/animation/instance.h"

extern s32 func_00349278();

void func_00348018(void *arg0)
{
  int new_var;
  s32 temp_3;
  if ((((BkModAnimationInstancePS2*)arg0)->evaluationFlags) == 0)
  {
    temp_3 = ((BkModAnimationInstancePS2*)arg0)->flags;
    new_var = 1;
    if ((temp_3 & new_var) && (temp_3 & 0x10000000))
    {
      ((BkModAnimationInstancePS2*)arg0)->flags = (s32) (temp_3 & 0xEFFFFFFF);
      func_00349278(arg0);
    }
  }
}
