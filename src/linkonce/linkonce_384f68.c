#include "ps2/prelude.h"

void func_00384F68(void *arg0, s32 arg1)
{
  int new_var;
  int new_var2;
  new_var2 = arg1;
  new_var2 = new_var2 != 0;
  new_var = 0x11;
  M2C_FIELD(arg0, s32 *, 0x58) = (s32) (((M2C_FIELD(arg0, s32 *, 0x58)) & 0xFFFDFFFF) | (new_var2 << new_var));
}
