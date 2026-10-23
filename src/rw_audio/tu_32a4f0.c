#include "auto/prelude.h"

void func_0032A4F0(void *arg0, s32 arg1)
{
  M2C_FIELD(arg0, s32 *, 8) = arg1;
  M2C_FIELD(arg0, f32 *, 0x10) = 1.0f;
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((M2C_FIELD(arg0, s32 *, 0)) | 4) & 0xFFFFFFF7);
  M2C_FIELD(arg0, s32 *, 4) = 1;
  M2C_FIELD(arg0, s32 *, 0x14) = (M2C_FIELD(arg0, s32 *, 0xC) = 0);
}
