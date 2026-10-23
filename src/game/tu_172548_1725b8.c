/* Translation unit tu_172548 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00176F00();
extern s32 func_0017B6F8();
extern void * D_0040F4D4;
extern void * D_0040F4D0;

void func_001725B8(void *arg0) {
    if ((M2C_FIELD(arg0, void **, 0x10) != NULL) && (func_00176F00(arg0 + 0x14) != 0)) {
        M2C_FIELD(arg0, s32 *, 0xC) = func_0017B6F8(D_0040F4D4 + 0x1290, M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s128 *, 0xA0));
    }
}

s32 func_00172610(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

void func_00172618(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

s32 func_00172620(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00172628(void) {
    return 1;
}

s32 func_00172630(void) {
    return 1;
}

void func_00172638(void) {

}

/* Assembly between the functions: func_00172640 (96 bytes), func_001726A0 (96 bytes) */

void func_00172700(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

/* Assembly between the functions: func_00172708 (184 bytes), func_001727C0 (88 bytes) */

s32 func_00172818(void) {
    return 1;
}

s32 func_00172820(void) {
    return 1;
}

void func_00172828(void) {

}

/* Assembly between the functions: func_00172830 (456 bytes), func_001729F8 (520 bytes) */

s32 func_00172C00(s32 arg0, s32 arg1, s32 arg2)
{
  s8 *new_var;
  new_var = (s8 *) (arg0 + (arg1 * 4));
  *((s32 *) (new_var + 0x64)) = arg2;
  return 1;
}

/* Assembly between the functions: func_00172C18 (56 bytes), func_00172C50 (56 bytes), func_00172C88 (416 bytes), func_00172E28 (88 bytes), func_00172E80 (88 bytes), func_00172ED8 (136 bytes), func_00172F60 (128 bytes), func_00172FE0 (72 bytes), func_00173028 (320 bytes), func_00173168 (40 bytes) */

void func_00173190(void *arg0, s128 arg1) {
    M2C_FIELD(arg0, s128 *, 0x230) = arg1;
}

/* Assembly between the functions: func_00173198 (144 bytes), func_00173228 (328 bytes), func_00173370 (224 bytes), func_00173450 (56 bytes), func_00173488 (216 bytes), func_00173560 (128 bytes) */

s32 func_001735E0(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (*arg0 == -1.0f) {
        var_2 = 0;
    }
    return var_2;
}

s32 func_00173610(f32 *arg0) {
    s32 var_2;

    var_2 = 1;
    if (!(*arg0 <= M2C_FIELD(D_0040F4D0, f32 *, 0x20))) {
        var_2 = 0;
    }
    return var_2;
}

void func_00173640(f32 *arg0, f32 fparg0) {
    *arg0 = M2C_FIELD(D_0040F4D0, f32 *, 0x20) + fparg0;
}

/* Assembly between the functions: func_00173658 (32 bytes) */

f32 func_00173678(f32 *arg0) {
    return *arg0 - M2C_FIELD(D_0040F4D0, f32 *, 0x20);
}

void func_00173690(f32 *arg0) {
    *arg0 = -1.0f;
}

void func_001736A0(f32 *arg0, f32 fparg0) {
    *arg0 += fparg0;
}

void func_001736B0(void) {

}
