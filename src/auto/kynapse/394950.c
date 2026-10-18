#include "auto/prelude.h"

extern char D_00408BD8[];
const char rodata_00408BD8[168] __asm__("D_00408BD8") __attribute__((aligned(8))) = "Q24Kaim22CDynamicAvoidanceClass" "\000" "Q24Kaimt10CMetaClass2ZQ24Kaim17IDynamicAvoidanceZPFPQ24Kaim11CPathFinder_PQ24Kaim17IDynamicAvoidance" "\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BE80;
extern s32 func_00393F38();
extern s32 func_00370168();
extern s32 D_0040EC38;

s32 * func_00394950(void) {
    if (D_0049BE80 == 0) {
        func_00393F38();
        func_00370168(&D_0049BE80, D_00408BD8, &D_0040EC38);
    }
    return &D_0049BE80;
}
