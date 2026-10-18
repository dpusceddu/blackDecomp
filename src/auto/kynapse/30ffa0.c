#include "auto/prelude.h"

extern s32 func_0030F678();

s32 func_0030FFA0(s32 arg0)
{
  s8 *new_var;
  M2C_FIELD(arg0, s8 *, 0x49) = 0;
  new_var = ((s8 *) arg0) + 0x51;
  M2C_FIELD(arg0, s32 *, 0x18) = 0;
  M2C_FIELD(arg0, s8 *, 0x48) = 1;
  *((s8 *) new_var) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x18);
}

s32 func_0030FFE0(s32 arg0)
{
  M2C_FIELD(arg0, s8 *, 0x49) = 0;
  M2C_FIELD(arg0, s8 *, 0x48) = 1;
  M2C_FIELD(arg0, s32 *, 0x1C) = 0;
  M2C_FIELD(arg0, s8 *, 0x51) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x1C);
}
