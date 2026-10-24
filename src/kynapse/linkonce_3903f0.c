#include "ps2/prelude.h"

extern s32 D_0049BB60;
extern s32 * func_003909A8();
extern s32 func_00370168();
extern s32 D_0049BBB0;

s32 * func_003903F0(void) {
    if (D_0049BB60 == 0) {
        func_003909A8();
        func_00370168(&D_0049BB60, "Q24Kaim26CConstraintPointToFleePath", &D_0049BBB0);
    }
    return &D_0049BB60;
}
