/* Translation unit tu_1af930 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

void func_001AFC78(void) {

}

/* Assembly between the functions: func_001AFC80 (72 bytes) */

s32 func_001AFCC8(void) {
    return 1;
}

void func_001AFCD0(void) {

}

s32 func_001AFCD8(void *arg0, f32 fparg0) {
    f32 temp_f0;

    if (M2C_FIELD(arg0, s32 *, 4) != -1) {
        temp_f0 = M2C_FIELD(arg0, f32 *, 0) - fparg0;
        M2C_FIELD(arg0, f32 *, 0) = temp_f0;
        if (temp_f0 <= 0.0f) {
            M2C_FIELD(arg0, f32 *, 0) = 0.0f;
            return 1;
        }
    }
    return 0;
}

/* Assembly between the functions: func_001AFD18 (104 bytes), func_001AFD80 (40 bytes) */

s32 func_001AFDA8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

f32 func_001AFDB0(f32 *arg0) {
    return *arg0;
}

s32 func_001AFDB8(s32 arg0) {
    if (arg0 == 0) {
        goto block_3;
    }
    if (arg0 == 1) {
        goto block_4;
    }
    return 1;
block_3:
    return 4;
block_4:
    return 2;
}

/* Assembly between the functions: func_001AFDE0 (88 bytes), func_001AFE38 (168 bytes), func_001AFEE0 (168 bytes) */

s32 func_001AFF88(s32 arg0, s32 arg1)
{
  int new_var;
  new_var = arg0 + (arg1 * 4);
  return M2C_FIELD(new_var, s32 *, 0x214);
}
