#include "auto/prelude.h"

void func_00348378(s32 *arg0, s32 arg1)
{
  s32 *new_var;
  s32 temp_2;
  ;
  if (arg1 == 1)
  {
    *arg0 = (*arg0) & (~0x200);
    return;
  }
  new_var = arg0;
  *new_var = (*arg0) | 0x200;
}
