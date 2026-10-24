#include "ps2/prelude.h"

void func_00249CF0(void *arg0)
{
  float new_var;
  new_var = 1.0f;
  M2C_FIELD(arg0, s32 *, 0x3BC) = 0;
  M2C_FIELD(arg0, f32 *, 0x22C) = 1.0f;
  M2C_FIELD(arg0, f32 *, 0) = new_var;
  *((f32 *) (((s8 *) arg0) - -4)) = 1.0f;
  M2C_FIELD(arg0, f32 *, 8) = 1.0f;
  M2C_FIELD(arg0, f32 *, 0xC) = 1.0f;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
  M2C_FIELD(arg0, s32 *, 0x14) = 0;
  M2C_FIELD(arg0, s32 *, 0x18) = 0;
  *((s32 *) (((s8 *) arg0) - -0x1C)) = 0;
  M2C_FIELD(arg0, f32 *, 0x220) = 1.0f;
  M2C_FIELD(arg0, s32 *, 0x224) = 0;
  M2C_FIELD(arg0, s32 *, 0x228) = 0;
  M2C_FIELD(arg0, s32 *, 0x230) = 0;
  M2C_FIELD(arg0, s32 *, 0x234) = 0;
  M2C_FIELD(arg0, s32 *, 0x3B8) = 0;
}
