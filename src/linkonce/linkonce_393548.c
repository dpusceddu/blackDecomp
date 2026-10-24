#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407ED8[];
const char rodata_00407ED8[48] __asm__("D_00407ED8") __attribute__((aligned(8))) = "Q24Kaim10CAstarData" "\000\000\000\000\000" "Q24Kaim14CZeroHeuristic" "\000";
extern s32 D_0049BD40;
extern s32 func_00390060();
extern s32 func_00370168();
extern M2C_UNK D_0049BB20;

s32 * func_00393548(void) {
    if (D_0049BD40 == 0) {
        func_00390060();
        func_00370168(&D_0049BD40, D_00407ED8, &D_0049BB20);
    }
    return &D_0049BD40;
}
