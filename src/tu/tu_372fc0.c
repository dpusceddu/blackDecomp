/* Translation unit tu_372fc0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern int D_003E0040;
extern void (*D_003C87E0)(void *);
extern s32 func_002E3918();
extern s32 (*D_0045127C)();
extern M2C_UNK D_0040C418;
extern s32 (*D_00451280)();

void func_00373268(void **arg0, int arg1)
{
    *arg0 = &D_003E0040;
    if (arg1 & 1) D_003C87E0(arg0);
}

s32 func_003732A0(s32 arg0, void *arg1) {
    s32 temp_2;
    s32 temp_2_2;

    temp_2 = func_002E3918(arg1);
    if (temp_2 != 0) {
        temp_2_2 = D_0045127C(temp_2, &D_0040C418);
        if (temp_2_2 != 0) {
            M2C_FIELD(arg1, s32 *, 8) = temp_2_2;
            return 1;
        }
    }
    M2C_FIELD(arg1, s32 *, 8) = 0;
    return 0;
}

/* Assembly between the functions: func_00373300 (72 bytes) */

void func_00373348(s32 arg0, void *arg1) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg1, s32 *, 8);
    if (temp_4 != 0) {
        D_00451280(temp_4);
    }
}
