#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BCB0;
extern s32 * func_00391D88();
extern s32 func_00370168();
extern s32 D_0049BCC0;

s32 * func_00391768(void) {
    if (D_0049BCB0 == 0) {
        func_00391D88();
        func_00370168(&D_0049BCB0, "28SaveFastBinaryGraphTraversal", &D_0049BCC0);
    }
    return &D_0049BCB0;
}
