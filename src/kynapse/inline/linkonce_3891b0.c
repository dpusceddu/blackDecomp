#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049A8F8;
extern s32 * func_003893B0();
extern s32 func_00370168();
extern s32 D_0049A928;

s32 * func_003891B0(void) {
    if (D_0049A8F8 == 0) {
        func_003893B0();
        func_00370168(&D_0049A8F8, "Q24Kaim11CGraphPoint", &D_0049A928);
    }
    return &D_0049A8F8;
}
