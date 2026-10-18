#include "auto/prelude.h"

extern s32 D_0049A978;
extern s32 func_0038BA88();
extern s32 func_00370168();
extern M2C_UNK D_0049A948;

s32 func_00389568(s32 arg0) {
    return arg0 + 0x18;
}

u8 func_00389570(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x10);
}

s32 * func_00389578(void) {
    if (D_0049A978 == 0) {
        func_0038BA88();
        func_00370168(&D_0049A978, "Q24Kaim10CHideAgent", &D_0049A948);
    }
    return &D_0049A978;
}
