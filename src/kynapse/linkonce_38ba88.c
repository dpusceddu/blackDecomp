#include "ps2/prelude.h"

extern char D_00405FF0[];
const char rodata_00405FF0[32] __asm__("D_00405FF0") __attribute__((aligned(8))) = "Q24Kaim6CAgent" "\000\000" "Q24Kaim7CObject" "\000";
extern s32 D_0049A948;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_0038BA88(void) {
    if (D_0049A948 == 0) {
        func_00389100();
        func_00370168(&D_0049A948, D_00405FF0, &D_0040EBC0);
    }
    return &D_0049A948;
}
