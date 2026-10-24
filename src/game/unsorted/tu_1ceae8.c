#include "include_asm.h"
#include "ps2/prelude.h"

void func_001CEAE8(s32 arg0, s32 arg1)
{
  s32 temp_2;
  int new_var;
  s8 *new_var2;
  s32 temp_2_2;
  temp_2_2 = M2C_FIELD(arg1, s32 *, 4);
  new_var = temp_2_2 != 0;
  new_var2 = ((s8 *) arg1) + 4;
  temp_2 = temp_2_2 + arg1;
  if (new_var)
  {
    *((s32 *) new_var2) = temp_2_2 + arg1;
  }
  return temp_2_2 + arg1;
}
