#include "auto/prelude.h"

extern s32 D_0049BCE0;
extern s32 D_0049BCC0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00407C70;
extern s32 func_00370168();
extern M2C_UNK D_00407C80;

s32 * func_003921F0(void) {
    if (D_0049BCE0 == 0) {
        if (D_0049BCC0 == 0) {
            if (D_0040EBC0 == 0) {
                func_00370188(&D_0040EBC0, &D_00407C70);
            }
            func_00370168(&D_0049BCC0, &D_00407C80, &D_0040EBC0);
        }
        func_00370168(&D_0049BCE0, "27FindNearestVisibleTraversal", &D_0049BCC0);
    }
    return &D_0049BCE0;
}
