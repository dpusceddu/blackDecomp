#include "auto/prelude.h"

extern s32 D_0049BB40;
extern s32 * func_003909A8();
extern s32 func_00370168();
extern s32 D_0049BBB0;

s32 * func_003902A8(void) {
    if (D_0049BB40 == 0) {
        func_003909A8();
        func_00370168(&D_0049BB40, "Q24Kaim22CConstraintStealthPath", &D_0049BBB0);
    }
    return &D_0049BB40;
}
