/* Translation unit tu_136f10 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern void * D_0040F4BC;
extern s32 D_003BD140;
extern unsigned char D_004147C0;

void func_00137318(s64 *arg0, s64 arg1) {
    *arg0 = arg1;
}

/* Assembly between the functions: func_00137320 (304 bytes), func_00137450 (64 bytes), func_00137490 (104 bytes), func_001374F8 (40 bytes), func_00137520 (72 bytes), func_00137568 (432 bytes), func_00137718 (472 bytes) */

f32 func_001378F0(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC0) * M2C_FIELD(D_0040F4BC, f32 *, 0x1660);
}

/* Assembly between the functions: func_00137908 (368 bytes), func_00137A78 (104 bytes) */

s32 func_00137AE0(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x2A4);
    if (temp_2 != NULL) {
        return M2C_FIELD(M2C_FIELD(temp_2, void **, 0xE8), s32 *, 0xC) + 0x10;
    }
    return D_003BD140;
}

/* Assembly between the functions: func_00137B08 (128 bytes), func_00137B88 (280 bytes), func_00137CA0 (488 bytes), func_00137E88 (168 bytes), func_00137F30 (136 bytes), func_00137FB8 (552 bytes), func_001381E0 (184 bytes), func_00138298 (136 bytes) */

s32 func_00138320(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

/* Assembly between the functions: func_00138328 (16 bytes) */

void func_00138338(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

s32 func_00138340(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

/* Assembly between the functions: func_00138348 (24 bytes), func_00138360 (24 bytes) */

void *func_00138378(s32 arg0)
{
  int new_var;
  new_var = arg0 & 0xFFFFFFFFFFFFFFFF;
  return (new_var << 6) + (&D_004147C0);
}

/* Assembly between the functions: func_00138390 (216 bytes), func_00138468 (8 bytes) */

void func_00138470(void *arg0, void *arg1) {
    f32 var_f1;

    var_f1 = 0.0f;
    M2C_FIELD(arg0, void **, 0) = arg1;
    if (M2C_FIELD(arg1, f32 *, 0x308) > 0.0f) {
        var_f1 = 1.0f / func_001378F0(arg1);
    }
    M2C_FIELD(arg0, f32 *, 4) = var_f1;
}
