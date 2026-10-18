#include "auto/prelude.h"

void func_0036AB48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (M2C_FIELD(arg0, s32 *, 0x10) & 0xFFFFFFFE);
}

s32 func_0036AB68(void *arg0)
{
  s32 temp_hi;
  s8 *new_var;
  s32 new_var2;
  temp_hi = ((s32) (M2C_FIELD(arg0, s32 *, 0x24))) % ((s32) (M2C_FIELD(arg0, s32 *, 0x18)));
  new_var2 = temp_hi << 6;
  new_var = (s8 *) arg0;
  *((s32 *) (new_var + 0x24)) = (s32) (temp_hi + 1);
  return (M2C_FIELD(arg0, s32 *, 0x14)) + new_var2;
}

s32 func_0036AB98(s32 arg0, s32 arg1) {
    if (arg1 < 0) {
        goto block_4;
    }
    if (arg1 >= M2C_FIELD(arg0, s32 *, 0x20)) {
        goto block_3;
    }
    goto block_5;
block_3:
block_4:
    return func_0036AB68(arg0);
block_5:
    return M2C_FIELD(arg0, s32 *, 0x1C) + (arg1 << 6);
}
