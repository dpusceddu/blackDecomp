#include "auto/prelude.h"

extern s32 func_002174E0();

s32 func_00103158(void *arg0)
{
  func_002174E0(arg0 + 0x210A0);
  M2C_FIELD(arg0, s32 *, 0x21080) = (M2C_FIELD(arg0, s32 *, 0x2107C) = 0);
  return 1;
}
