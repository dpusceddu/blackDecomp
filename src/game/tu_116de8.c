#include "ps2/prelude.h"

void func_00116DE8(void *arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  new_var = (s8 *) arg0;
  *((f32 *) (new_var + 0x24)) = -1.0f;
  M2C_FIELD(arg0, s8 *, 0x20) = 0;
 if (1) { } if (1) { } if (1) { *((f32 *) (new_var + 0x24)) = -1.0f; }
}

void func_00116E00(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  M2C_FIELD(arg0, s32 *, 0x14) = arg1;
  M2C_FIELD(arg0, f32 *, 0x24) = -1.0f;
  M2C_FIELD(arg0, s32 *, 0x18) = arg2;
  M2C_FIELD(arg0, s32 *, 0x1C) = arg3;
  M2C_FIELD(arg0, s8 *, 0x20) = 1;
  M2C_FIELD(arg0, f32 *, 0x24) = -1.0f;
}
