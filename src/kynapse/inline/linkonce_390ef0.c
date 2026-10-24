#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407858[];
const char rodata_00407858[144] __asm__("D_00407858") __attribute__((aligned(8))) = "Q24Kaim15CGraphDataClass" "\000\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim10CGraphDataZPFPQ24Kaim13CSpatialGraph_PQ24Kaim10CGraphData" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BC30;
extern s32 func_003900D8();
extern s32 func_00370168();
extern s32 D_0040EC28;

s32 * func_00390EF0(void) {
    if (D_0049BC30 == 0) {
        func_003900D8();
        func_00370168(&D_0049BC30, D_00407858, &D_0040EC28);
    }
    return &D_0049BC30;
}
