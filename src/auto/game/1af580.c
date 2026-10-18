#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_001AF1A0(void *, s32, s32, s32);

s32 func_001AF580(s32 arg0, void *arg1)
{
  s32 temp_16;
  int new_var;
  s32 temp_16_2;
  s32 temp_16_3;
  s32 temp_16_4;
  int new_var2;
  s32 temp_16_5;
  func_001AF1A0(arg0 + 0xCA58, arg0, arg0 + (new_var = 0x9088), M2C_FIELD(arg1, s32 *, 0));
  temp_16 = M2C_FIELD(arg1, s32 *, 0);
  func_001AF1A0(arg0 + 0xCA70, (temp_16 * 0x14) + arg0, arg0 + ((temp_16 * 8) + new_var), M2C_FIELD(arg1, s32 *, 4));
  temp_16_2 = temp_16 + (M2C_FIELD(arg1, s32 *, 4));
  new_var2 = (temp_16_2 * 0x14) + arg0;
  func_001AF1A0(arg0 + 0xCA88, new_var2, arg0 + ((temp_16_2 * 8) + new_var), M2C_FIELD(arg1, s32 *, 8));
  temp_16_3 = temp_16_2 + (M2C_FIELD(arg1, s32 *, 8));
  func_001AF1A0(arg0 + 0xCAA0, (temp_16_3 * 0x14) + arg0, 0, M2C_FIELD(arg1, s32 *, 0xC));
  temp_16_4 = temp_16_3 + (M2C_FIELD(arg1, s32 *, 0xC));
  func_001AF1A0(arg0 + 0xCAB8, (temp_16_4 * 0x14) + arg0, 0, M2C_FIELD(arg1, s32 *, 0x10));
  temp_16_5 = temp_16_4 + (M2C_FIELD(arg1, s32 *, 0x10));
  func_001AF1A0(arg0 + 0xCAD0, (temp_16_5 * 0x14) + arg0, 0, M2C_FIELD(arg1, s32 *, 0x14));
  func_001AF1A0(arg0 + 0xCAE8, ((temp_16_5 + (M2C_FIELD(arg1, s32 *, 0x14))) * 0x14) + arg0, 0, M2C_FIELD(arg1, s32 *, 0x18));
  return 1;
}
