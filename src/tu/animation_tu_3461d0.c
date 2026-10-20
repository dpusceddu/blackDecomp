/* Translation unit animation/tu_3461d0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "mod/animation/pose_cache.h"

extern s8 D_003D20D0;
extern s32 D_0046A500;
extern s32 D_003D20E0;
extern s32 func_00347738(M2C_UNK, M2C_UNK);

void func_003461D0(s8 arg0) {
    BkModPoseCacheEnablePS2(arg0);
}

void func_003461E0(void) {
    BkModPoseCacheClearPS2();
}

/* Assembly between the functions: func_003461F0 (64 bytes), func_00346230 (736 bytes), func_00346510 (344 bytes), func_00346668 (728 bytes), func_00346940 (880 bytes), func_00346CB0 (648 bytes) */

void func_00346F38(s32 arg0) {
    BkModPoseCacheForceBonePS2(arg0);
}

void func_00346F48(void) {
    D_003D20E0 = -1;
}

/* Assembly between the functions: func_00346F58 (736 bytes), func_00347238 (72 bytes), func_00347280 (432 bytes), func_00347430 (200 bytes), func_003474F8 (96 bytes), func_00347558 (168 bytes), func_00347600 (312 bytes), func_00347738 (152 bytes) */

void func_003477D0(void) {
    func_00347738(1, 0xFFFF);
}
