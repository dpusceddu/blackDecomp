#include "auto/prelude.h"

extern char D_00407920[];
const char rodata_00407920[48] __asm__("D_00407920") __attribute__((aligned(8))) = "Q24Kaim13CPathCostData" "\000\000" "Q24Kaim14CZeroHeuristic" "\000";
extern s32 D_0049BC40;
extern s32 func_00390060();
extern s32 func_00370168();
extern M2C_UNK D_0049BB20;

s32 * func_003910D0(void) {
    if (D_0049BC40 == 0) {
        func_00390060();
        func_00370168(&D_0049BC40, D_00407920, &D_0049BB20);
    }
    return &D_0049BC40;
}
