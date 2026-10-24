#include "ps2/prelude.h"

extern s32 D_0049BD20;
extern s32 * func_00391D88();
extern s32 func_00370168();
extern s32 D_0049BCC0;

s32 * func_00392DF8(void) {
    if (D_0049BD20 == 0) {
        func_00391D88();
        func_00370168(&D_0049BD20, "26ComputeAccessWaysTraversal", &D_0049BCC0);
    }
    return &D_0049BD20;
}

void func_00392E48(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
}
