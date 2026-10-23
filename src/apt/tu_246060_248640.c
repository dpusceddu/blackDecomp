/* Translation unit apt/tu_246060 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern volatile unsigned char func_00248C78();
extern s32 func_0024C300();
extern s32 (*D_003BFAB0)();
extern void * D_0043DC18;
extern void * D_0043DDF8;
extern void func_00249CF0();

s32 func_00248640(void *arg0)
{
  int new_var;
  short temp_2;
  temp_2 = func_00248C78(*((s32 *) (((s8 *) arg0) - (-(8 ^ 0)))));
  if (temp_2 == 0)
  {
    new_var = -1;
    return new_var;
 } if (temp_2) {
    return func_0024C300(temp_2);
  }
  else
  {
    return func_0024C300(temp_2);
  }
}

/* Assembly between the functions: func_00248678 (96 bytes), func_002486D8 (264 bytes), func_002487E0 (232 bytes), func_002488C8 (8 bytes), func_002488D0 (456 bytes), func_00248A98 (480 bytes), func_00248C78 (288 bytes), func_00248D98 (328 bytes), func_00248EE0 (104 bytes), func_00248F48 (104 bytes), func_00248FB0 (248 bytes), func_002490A8 (1120 bytes) ... */

void func_00249958(void *arg0, u32 *arg1) {
    s32 var_16;
    void *temp_2;
    void *temp_5;
    void *temp_5_2;
    void *temp_5_3;

    temp_5 = M2C_FIELD(arg0, void **, 8);
    if (temp_5 != NULL) {
        D_003BFAB0(arg1, temp_5, D_0043DC18 + 8);
    }
    temp_5_2 = M2C_FIELD(arg0, void **, 0xC);
    if (temp_5_2 != NULL) {
        D_003BFAB0(arg1, temp_5_2, D_0043DDF8 + 8);
    }
    if (M2C_FIELD(arg0, s32 *, 4) != 0) {
        var_16 = 0;
        if (M2C_FIELD(arg0, s32 *, 0) > 0) {
            do {
                temp_2 = (var_16 * 8) + M2C_FIELD(arg0, s32 *, 4);
                temp_5_3 = M2C_FIELD(temp_2, void **, 4);
                if (temp_5_3 != NULL) {
                    D_003BFAB0(arg1, temp_5_3, M2C_FIELD(temp_2, s32 *, 0) + 8);
                }
                var_16 += 1;
            } while (var_16 < M2C_FIELD(arg0, s32 *, 0));
        }
    }
}

/* Assembly between the functions: func_00249A38 (456 bytes), func_00249C00 (128 bytes), func_00249C80 (72 bytes) */

s32 func_00249CC8(s32 arg0) {
    func_00249CF0();
    return arg0;
}
