#include "auto/prelude.h"

extern char D_004083A0[];
extern char D_004083C8[];
const char rodata_004083A0[40] __asm__("D_004083A0") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000" "Q24Kaim12CTraceResult" "\000\000\000";
const char rodata_004083C8[40] __asm__("D_004083C8") __attribute__((aligned(8))) = "Q34Kaim11CPathFinder15CConstraintInfo" "\000\000\000";
extern s32 D_0049BD50;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_00393860(void) {
    if (D_0049BD50 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_004083A0);
        }
        func_00370168(&D_0049BD50, D_004083C8, &D_0040EBC0);
    }
    return &D_0049BD50;
}
