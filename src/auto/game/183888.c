#include "auto/prelude.h"

s8 func_00183888(void *arg0, s8 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 8;
  if (arg1 < ((*((s32 *) new_var)) - 1))
  {
    arg1 = arg1 + 1;
  }
  else
  {
    arg1 = 0;
  }
  return arg1;
}
