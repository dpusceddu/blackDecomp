#include "auto/prelude.h"

extern s32 func_00125C60();
extern s32 func_0014B948();
extern void *func_00108120();
extern s32 D_0040F4C4;

s32 func_0014B878(void) {
    return 5;
}

void func_0014B880(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x110) = (f32) (M2C_FIELD(arg0, f32 *, 0x110) + 2.0f);
}

void func_0014B8A0(void *arg0) {
    void *temp_3;

    func_00125C60();
    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    M2C_FIELD(arg0, s32 *, 0xC4) = M2C_FIELD(temp_3, s32 (**)(void *), 0x94)(arg0 + M2C_FIELD(temp_3, s16 *, 0x90));
    M2C_FIELD(arg0, s32 *, 0xD8) = 0;
}

s32 func_0014B8E0(void *arg0, void *arg1, unsigned char arg2)
{
  s64 new_var;
  s8 *new_var2;
  new_var2 = ((s8 *) arg0) + 0xD8;
  *((void **) new_var2) = arg1;
  new_var = M2C_FIELD(arg1, s64 *, 0x48);
  M2C_FIELD(arg0, s64 *, 0) = (s64) new_var;
  func_0014B948(arg0, func_00108120(D_0040F4C4, M2C_FIELD(arg1, s64 *, 0x40)), arg2 & 0xFF, *((void **) new_var2));
  M2C_FIELD(arg0, s8 *, 0xEE) = 0;
  return 1;
}
