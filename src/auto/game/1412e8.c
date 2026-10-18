#include "auto/prelude.h"

void func_001412E8(void *arg0, s32 arg1)
{
  s8 *new_var;
  s32 temp_3;
  temp_3 = M2C_FIELD(arg0, s32 *, 0x4DC);
  new_var = ((s8 *) (arg0 + (temp_3 * 4))) + 0x4B8;
  *((s32 *) new_var) = arg1;
  M2C_FIELD(arg0, s32 *, 0x4DC) = (s32) (temp_3 + 1);
}
