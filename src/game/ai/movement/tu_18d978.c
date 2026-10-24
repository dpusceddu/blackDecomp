#include "include_asm.h"
#include "ps2/prelude.h"

void func_0018D978(void *arg0, unsigned int arg1)
{
  float new_var;
  new_var = -1.0f;
  M2C_FIELD(arg0, s32 *, 0) = arg1;
  M2C_FIELD(arg0, f32 *, 0x10) = new_var;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  M2C_FIELD(arg0, s8 *, 0x20) = 0;
  M2C_FIELD(arg0, s32 *, 0x14) = 0;
  M2C_FIELD(arg0, s32 *, 0x18) = 0;
}
