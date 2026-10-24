#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407DD8[];
extern char D_00407E70[];
const char rodata_00407DD8[152] __asm__("D_00407DD8") __attribute__((aligned(8))) = "Q24Kaim15CGraphTraversal" "\000\000\000\000\000\000\000\000" "Q24Kaim10CGraphData" "\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim10CGraphDataZPFPQ24Kaim13CSpatialGraph_PQ24Kaim10CGraphData" "\000\000\000\000\000\000\000\000";
const char rodata_00407E70[48] __asm__("D_00407E70") __attribute__((aligned(8))) = "26ComputeVisibilityTraversal" "\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BD30;
extern s32 D_0049BCC0;
extern s32 func_00389100();
extern s32 func_00370168();
extern s32 D_0040EBC0;

s32 * func_00393200(void) {
    if (D_0049BD30 == 0) {
        if (D_0049BCC0 == 0) {
            func_00389100();
            func_00370168(&D_0049BCC0, D_00407DD8, &D_0040EBC0);
        }
        func_00370168(&D_0049BD30, D_00407E70, &D_0049BCC0);
    }
    return &D_0049BD30;
}
