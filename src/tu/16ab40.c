#include "auto/prelude.h"

extern s32 func_00107D20();

void func_0016AB40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11D) = 0;
    M2C_FIELD(arg0, u8 *, 0x11C) = (u8) (M2C_FIELD(arg0, u8 *, 0x11C) ^ 1);
}

s32 func_0016AB58(s32 arg0, s32 arg1)
{
  s32 temp_2;
  temp_2 = func_00107D20(arg1 * 0xC);
  M2C_FIELD(arg0, s16 *, 4) = (s16) arg1;
  temp_2++;
  temp_2--;
  M2C_FIELD(arg0, s32 *, 0) = temp_2;
 do { M2C_FIELD(arg0, s16 *, 6) = 0; } while (0);
  return temp_2;
}

void func_0016ABA0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 6) = 0;
}

void func_0016ABA8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 > 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) = arg1;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 4) = arg2;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 8) = arg3;
        M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + 1);
    }
}
