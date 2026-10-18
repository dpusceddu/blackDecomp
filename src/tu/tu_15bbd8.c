/* Translation unit tu_15bbd8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern void * D_0040F540;
extern void * func_0015D248(void **arg0, s8 arg1, s32 arg2);
extern void ** D_0040F4E0;
extern s32 func_00155178(void *, s32, u8);
extern s32 func_00288790(s32);
extern s32 func_00127060(s32);
extern s32 D_0040F4E4;

s32 func_0015BF38(void) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(D_0040F540, void **, 0x7C), void **, 8), s32 *, 0x1B4);
}

/* Assembly between the functions: func_0015BF50 (312 bytes), func_0015C088 (120 bytes), func_0015C100 (168 bytes), func_0015C1A8 (464 bytes) */

s32 func_0015C378(void *arg0) {
    s32 var_2;
    s8 *temp_3;
    void *temp_2;

    temp_3 = M2C_FIELD(arg0, s8 **, 0x24);
    var_2 = 0;
    if (temp_3 != NULL) {
        temp_2 = func_0015D248(D_0040F4E0, *temp_3, 0);
        var_2 = func_00155178(arg0, M2C_FIELD(temp_2, s32 *, 0x64), M2C_FIELD(temp_2, u8 *, 0x60));
    }
    return var_2;
}

/* Assembly between the functions: func_0015C3C8 (1368 bytes) */

s32 func_0015C920(void *arg0, s8 arg1) {
    s32 var_2;
    s8 *temp_2;
    s8 *temp_4_2;
    s8 var_3;
    s8 var_6;
    void *temp_4;

    if (M2C_FIELD(arg0, u8 *, 0x45) == 0) {
        temp_4 = M2C_FIELD(arg0, void **, 0x20);
        var_3 = 0x7F;
        temp_2 = M2C_FIELD(temp_4, s8 **, 0);
        var_6 = 0x7F;
        if (temp_2 != NULL) {
            var_3 = *temp_2;
        }
        temp_4_2 = M2C_FIELD(temp_4, s8 **, 4);
        if (temp_4_2 != NULL) {
            var_6 = *temp_4_2;
        }
        var_2 = 0;
        if (arg1 != var_3) {
            var_2 = 1;
            if (arg1 == var_6) {
                goto block_7;
            }
        }
    } else {
block_7:
        var_2 = 0;
    }
    return var_2;
}

/* Assembly between the functions: func_0015C970 (320 bytes), func_0015CAB0 (240 bytes), func_0015CBA0 (160 bytes), func_0015CC40 (648 bytes) */

void func_0015CEC8(s32 *arg0) {
    func_00288790(*arg0);
    func_00127060(D_0040F4E4);
}
