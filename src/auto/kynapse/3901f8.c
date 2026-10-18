#include "auto/prelude.h"

extern s32 D_0049BB30;
extern s32 * func_003909A8();
extern s32 func_00370168();
extern M2C_UNK D_00407418;
extern s32 D_0049BBB0;
extern M2C_UNK D_003ECA50;

s32 * func_003901F8(void) {
    if (D_0049BB30 == 0) {
        func_003909A8();
        func_00370168(&D_0049BB30, &D_00407418, &D_0049BBB0);
    }
    return &D_0049BB30;
}

M2C_UNK ** func_00390248(M2C_UNK **arg0) {
    *arg0 = &D_003ECA50;
    return arg0;
}
