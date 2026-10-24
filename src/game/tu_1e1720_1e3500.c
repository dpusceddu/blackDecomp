#include "ps2/prelude.h"

volatile unsigned short func_001E3500(void *arg0)
{
  s32 *new_var;
  s8 *new_var2;
  new_var = (s32 *) (((s8 *) arg0) + 0x28);
  *new_var = 0;
  *((s32 *) (new_var2 = ((s8 *) arg0) + 0x20)) = 0;
  M2C_FIELD(arg0, s8 *, 0x2C) = 0;
  M2C_FIELD(arg0, s32 *, 0x24) = 0;
  M2C_FIELD(arg0, s8 *, 0x2C) = 0;
  return 1;
}
