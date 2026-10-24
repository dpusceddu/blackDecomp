#include "ps2/prelude.h"

s32 func_00173FB8(s32 *arg0, s32 arg1)
{
  int new_var;
  new_var = 1 << arg1;
  return ((*arg0) & new_var) != 0;
}
