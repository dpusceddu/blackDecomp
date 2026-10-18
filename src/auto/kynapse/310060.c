#include "auto/prelude.h"

extern s32 func_0030F678();

s32 func_00310060(s32 arg0)
{
  *((s8 *) (((s8 *) arg0) + (0x48 & 0xFFFFFFFF))) = 0;
  M2C_FIELD(arg0, s32 *, 0x24) = 0x48 * 0;
  M2C_FIELD(arg0, s8 *, 0x52) = (M2C_FIELD(arg0, s8 *, 0x49) = 1);
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x24);
}

s32 func_003100A0(s32 arg0)
{
  M2C_FIELD(arg0, s8 *, 0x48) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s8 *, 0x52) = 1;
  arg0++;
  arg0--;
  M2C_FIELD(arg0, s8 *, 0x49) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x28);
}
