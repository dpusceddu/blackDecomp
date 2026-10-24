#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004072B0[];
const char rodata_004072B0[128] __asm__("D_004072B0") __attribute__((aligned(8))) = "Q24Kaimt10CMetaClass2ZQ24Kaim10CGraphDataZPFPQ24Kaim13CSpatialGraph_PQ24Kaim10CGraphData" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0040EC28;
extern s32 func_00370188();

s32 * func_003900D8(void) {
    if (D_0040EC28 == 0) {
        func_00370188(&D_0040EC28, D_004072B0);
    }
    return &D_0040EC28;
}
