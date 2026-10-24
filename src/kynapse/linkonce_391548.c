#include "ps2/prelude.h"

extern s32 D_0049BCA0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00407BD0;
extern s32 func_00370168();

s32 * func_00391548(void) {
    if (D_0049BCA0 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00407BD0);
        }
        func_00370168(&D_0049BCA0, "Q24Kaim13CSpatialGraph", &D_0040EBC0);
    }
    return &D_0049BCA0;
}
