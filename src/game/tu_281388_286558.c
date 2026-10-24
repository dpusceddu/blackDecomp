/* Translation unit tu_281388 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002867F0();
extern s32 func_00286C10(M2C_UNK, M2C_UNK);

s32 func_00286558(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x2870);
    var_2 = temp_3 < 2;
    if (temp_3 >= 0) {
        if (var_2 == 0) {
            var_2 = temp_3 < 4;
            if (var_2 != 0) {
                var_2 = func_002867F0(arg0, 0);
            }
        }
    }
    return var_2;
}

/* Assembly between the functions: func_00286598 (256 bytes), func_00286698 (136 bytes), func_00286720 (80 bytes), func_00286770 (80 bytes) */

s32 func_002867C0(s32 arg0, s32 arg1, s32 arg2)
{
  s32 *temp_2_2;
  s32 *temp_5;
  void *temp_2;
  temp_2_2 = *((s32 **) (((s8 *) (arg0 ^ 0)) + 0x286C));
  *temp_2_2 = arg1;
  temp_2 = temp_2_2;
  temp_2 = temp_2 + 4;
  temp_5 = *((s32 **) (((s8 *) arg0) + 0x2868));
  *((s32 **) (((s8 *) arg0) + 0x286C)) = (s32 *) (temp_2 - (-(arg2 * 4)));
  *temp_5 += 1;
  return (s32) temp_2;
}

/* Assembly between the functions: func_002867F0 (136 bytes), func_00286878 (280 bytes), func_00286990 (640 bytes), func_00286C10 (112 bytes) */

void func_00286C80(void) {
    func_00286C10(1, 0xFFFF);
}
