/* Remaining drafts in animation/tu_34b498. */
#include "ps2/prelude.h"

extern s32 func_00347430(s32, s32, s32);
extern s32 func_0034B910();

s32 func_0034B5A8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x14);
}

void func_0034D920(s32 arg0, s32 arg1) {
    func_00347430(arg0, func_0034B910(), arg1);
}
