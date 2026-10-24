#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BB50;
extern s32 * func_003909A8();
extern s32 func_00370168();
extern s32 D_0049BBB0;

s32 * func_00390350(void) {
    if (D_0049BB50 == 0) {
        func_003909A8();
        func_00370168(&D_0049BB50, "Q24Kaim32CConstraintConeVisionStealthPath", &D_0049BBB0);
    }
    return &D_0049BB50;
}
