#include "ps2/prelude.h"

extern s32 D_0049BB80;
extern s32 func_00390AE0();
extern s32 func_00370168();
extern M2C_UNK D_0049BBC0;

s32 * func_003905E0(void) {
    if (D_0049BB80 == 0) {
        func_00390AE0();
        func_00370168(&D_0049BB80, "Q24Kaim27CHeuristicEuclidianDistance", &D_0049BBC0);
    }
    return &D_0049BB80;
}
