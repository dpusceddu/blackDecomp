#include "ps2/prelude.h"

extern s32 func_001D8478();
extern void *D_0040F510;
extern s32 func_001D84C8();

void func_001ED170(void *arg0, s32 arg1)
{
  s32 temp_2;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  temp_2 = func_001D8478(M2C_FIELD(D_0040F510, s32 *, 0xCBD4));
  M2C_FIELD(arg0, s32 *, 0x10) = arg1;
  M2C_FIELD(arg0, s32 *, 0xC) = temp_2;
  M2C_FIELD(arg0, s8 *, 0x20) = 0;
  temp_2 = 0;
  M2C_FIELD(arg0, s32 *, 0x14) = temp_2;
}

s32 func_001ED1C8(s32 arg0)
{
  func_001D84C8(M2C_FIELD(D_0040F510, s32 *, 0xCBD4), M2C_FIELD(arg0, s32 *, 0xC));
  M2C_FIELD(arg0, s32 *, 0x10) = 0xE ^ 0;
 do { } while (0 != 0);
  M2C_FIELD(arg0, s32 *, 0x14) = 7;
  M2C_FIELD(arg0, s32 *, 0x10) = 0xE;
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  return 7;
}
