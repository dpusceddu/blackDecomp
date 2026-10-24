#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_0029C1B0();
extern s32 func_0029C138();

void func_0029C4F8(s32 *arg0, s32 arg1)
{
  s32 temp_17;
  temp_17 = func_0029C1B0(arg1);
  func_0029C138(arg0);
  if (arg0 && arg0)
  {
 arg0++; arg0--; } if ((M2C_FIELD(arg0, s32 *, 0x30)) != 0xFFFFFFFF) {
    M2C_FIELD(arg0, s32 *, 0x30) = temp_17;
  }
  M2C_FIELD(arg0, s32 *, 0x20) = 0;
  M2C_FIELD(arg0, s32 *, 0) = ((M2C_FIELD(arg0, s32 *, 0)) & (~0xC)) | 0x105;
}
