#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00177B68(void *arg0, s32 arg1)
{
  int new_var;
  void *new_var2;
  int new_var3;
  new_var = 0x14;
  new_var2 = arg0;
  new_var3 = 1 << arg1;
  return ((*((s32 *) (((s8 *) new_var2) + new_var))) & new_var3) != 0;
}
