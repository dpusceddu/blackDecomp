#include "auto/prelude.h"

s32 func_001412C0(void *arg0)
{
  int new_var;
  s32 temp_3;
  temp_3 = *((s32 *) (((s8 *) arg0) + (0x4B4 ^ 0)));
  if (temp_3 != (-1))
  {
    new_var = temp_3 * 4;
    return *((s32 *) (((s8 *) (arg0 + new_var)) + 0x490));
  }
  if (temp_3 || arg0)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}
