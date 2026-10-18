#include "auto/prelude.h"

extern s32 func_001435D0();
extern void func_00144038();
extern s32 D_003BCEAC;

void func_00143688(void *arg0)
{
  s32 temp_17;
  s32 temp_18;
  temp_17 = arg0 + 8;
  func_001435D0(temp_17, 0xD);
  temp_18 = arg0 + 0x40;
  func_001435D0(temp_18, 0xE);
  M2C_FIELD(arg0, s32 *, 0x80) = temp_17;
  M2C_FIELD(arg0, s32 *, 0x7C) = temp_18;
  M2C_FIELD(arg0, s8 *, 0xC4) = 0;
  func_00144038(arg0, D_003BCEAC);
  M2C_FIELD(arg0, s8 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 0xC8) = 1;
}
