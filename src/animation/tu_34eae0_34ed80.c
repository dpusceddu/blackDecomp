/* Translation unit animation/tu_34eae0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern f32 D_003D4460;
extern f32 D_003D4464;

void func_0034ED80(void) {

}

void func_0034ED88(f32 fparg0) {
    D_003D4460 += fparg0;
}

void func_0034EDA0(f32 fparg0) {
    D_003D4464 += fparg0;
}

/* Assembly between the functions: func_0034EDB8 (216 bytes), func_0034EE90 (496 bytes), func_0034F080 (320 bytes), func_0034F1C0 (272 bytes) */

s32 func_0034F2D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x998) != 0;
}

f32 func_0034F2E0(void *arg0)
{
  f32 temp_f1;
  temp_f1 = M2C_FIELD(arg0, f32 *, 0x9C8);
  if (temp_f1 == 0.0f)
  {
    return 59.94f;
  }
  if (temp_f1)
  {
    return temp_f1 * 59.94f;
  }
  else
  {
    return temp_f1 * 59.94f;
  }
}
