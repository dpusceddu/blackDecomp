/* Translation unit kynapse/tu_3067a0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 D_004549C4;
extern s32 func_003071A8();
extern f32 D_003CD89C;
extern s32 func_0030B750();

s32 func_0030B7A8(s32 arg0)
{
  s32 *var_2;
  var_2 = &D_004549C4;
  if ((M2C_FIELD(arg0, s32 *, 0x1C)) & D_004549C4)
  {
    var_2 = func_003071A8();
    return (s32) var_2;
    var_2 = &D_004549C4;
  }
}

/* Assembly between the functions: func_0030B7E0 (184 bytes) */

void func_0030B898(void) {
    func_003071A8();
}

void func_0030B8B8(f32 fparg0) {
    if (fparg0 >= 0.0f) {
        D_003CD89C = fparg0;
    }
}

void func_0030B8E0(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xE8) = fparg0;
    }
}

void func_0030B900(void *arg0, f32 fparg0) {
    if (fparg0 >= 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xEC) = fparg0;
    }
}

void func_0030B920(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF0) = (f32) (fparg0 * 0.5f);
    }
}

void func_0030B958(void *arg0, f32 fparg0) {
    if (fparg0 > 0.0f) {
        M2C_FIELD(arg0, f32 *, 0xF4) = (f32) (fparg0 * M2C_FIELD(arg0, f32 *, 8));
    }
}

/* Assembly between the functions: func_0030B988 (136 bytes), func_0030BA10 (8 bytes) */

void func_0030BA18(void) {
    func_0030B750(1, 0xFFFF);
}

void func_0030BA38(void) {
    func_0030B750(0, 0xFFFF);
}
