#include "auto/prelude.h"

s32 func_0036AB68(void *arg0)
{
  s32 temp_hi;
  s8 *new_var;
  s32 new_var2;
  temp_hi = ((s32) (M2C_FIELD(arg0, s32 *, 0x24))) % ((s32) (M2C_FIELD(arg0, s32 *, 0x18)));
  new_var2 = temp_hi << 6;
  new_var = (s8 *) arg0;
  *((s32 *) (new_var + 0x24)) = (s32) (temp_hi + 1);
  return (M2C_FIELD(arg0, s32 *, 0x14)) + new_var2;
}
