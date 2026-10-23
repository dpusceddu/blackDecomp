/* Translation unit tu_27fcf8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

s32 func_0027FE68(void) {
    return 1;
}

/* Assembly between the functions: func_0027FE70 (144 bytes), func_0027FF00 (112 bytes), func_0027FF70 (8 bytes), func_0027FF78 (392 bytes) */

s32 func_00280100(s32 arg0, void *arg1)
{
  s32 temp_2;
  void *temp_3;
  temp_2 = M2C_FIELD(arg1, s32 *, 0x1024);
  if (temp_2 == 0)
  {
    temp_3 = *((void **) (((s8 *) arg1) + 0x1030));
    (*((M2C_UNK (**)(void *)) (((s8 *) temp_3) + 0x24)))(arg1 + (M2C_FIELD(temp_3, s16 *, 0x20)));
    M2C_FIELD(arg1, s8 *, 0x102E) = (M2C_FIELD(arg1, s8 *, 0x102D) = 0);
  }
  else
  {
    M2C_FIELD(arg1, s32 *, 0x1024) = (s32) (temp_2 - 1);
  }
  return 1;
}

/* Assembly between the functions: func_00280158 (8 bytes), func_00280160 (160 bytes), func_00280200 (168 bytes), func_002802A8 (120 bytes) */

void func_00280320(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x102D) = 0;
}
