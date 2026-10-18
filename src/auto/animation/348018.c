#include "auto/prelude.h"

extern s32 func_00349278();

void func_00348018(void *arg0)
{
  int new_var;
  s32 temp_3;
  if ((M2C_FIELD(arg0, s32 *, 0x998)) == 0)
  {
    temp_3 = M2C_FIELD(arg0, s32 *, 0);
    new_var = 1;
    if ((temp_3 & new_var) && (temp_3 & 0x10000000))
    {
      M2C_FIELD(arg0, s32 *, 0) = (s32) (temp_3 & 0xEFFFFFFF);
      func_00349278(arg0);
    }
  }
}
