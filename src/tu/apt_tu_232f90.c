/* Translation unit apt/tu_232f90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern s32 D_0043DEE4;
extern M2C_UNK D_003E1258;
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00240798();
extern M2C_UNK D_003E12F8;
extern s32 func_00107D48();
extern s32 func_00241228(s32);

void func_00233150(void *arg0, s32 arg1)
{
  s32 *new_var;
  *((M2C_UNK **) (((s8 *) arg0) + ((unsigned short) 4))) = &D_003E1E78;
  func_002486D8(arg0 + 8, 2);
  new_var = &D_0043DEE4;
 do { } while (0);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(*new_var, arg0, 0x2C);
  }
}

/* Assembly between the functions: func_002331C0 (184 bytes), func_00233278 (136 bytes), func_00233300 (232 bytes), func_002333E8 (184 bytes), func_002334A0 (72 bytes), func_002334E8 (8 bytes), func_002334F0 (384 bytes), func_00233670 (368 bytes), func_002337E0 (56 bytes), func_00233818 (120 bytes), func_00233890 (352 bytes), func_002339F0 (144 bytes) ... */

s32 func_00233C60(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E1258;
    if (M2C_FIELD(arg0, s32 *, 0x2C) == 1) {
        func_00250198(D_0043DEE0, M2C_FIELD(arg0, s32 *, 8), 0x3C);
    }
    func_00240798(arg0 + 0x24, 2);
    temp_4 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E12F8;
    if (temp_4 != 0) {
        func_002486D8(temp_4, 3);
    }
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = func_00107D48(arg0);
    }
    return var_2;
}

void func_00233CF8(s32 arg0) {
    func_00241228(arg0 + 0x24);
}
