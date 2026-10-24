/* Translation unit tu_14a8f8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00125C60();
extern s32 func_0014B948();
extern void *func_00108120();
extern s32 D_0040F4C4;
extern s32 func_00125E40();
extern s32 func_00125D10();

s32 func_0014AC58(void) {
    return 9;
}

/* Assembly between the functions: func_0014AC60 (56 bytes), func_0014AC98 (344 bytes), func_0014ADF0 (1768 bytes), func_0014B4D8 (928 bytes) */

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

/* Assembly between the functions: func_0014B948 (272 bytes) */

s32 func_0014BA58(void) {
    func_00125E40();
    return 1;
}

/* Assembly between the functions: func_0014BA78 (8 bytes) */

void func_0014BA80(void) {
    func_00125D10();
}

/* Assembly between the functions: func_0014BAA0 (504 bytes) */

void func_0014BC98(void) {

}
