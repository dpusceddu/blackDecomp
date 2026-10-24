#include "include_asm.h"

#include "ps2/prelude.h"

extern char D_00408A40[];
const char rodata_00408A40[204] __asm__("D_00408A40") __attribute__((aligned(8))) = "Q34Kaimt8CVarList1ZQ24Kaim4CGap9CIterator" "\000\000\000\000\000\000\000" "Q24Kaimt10CMetaClass2ZQ24Kaim17IDynamicAvoidanceZPFPQ24Kaim11CPathFinder_PQ24Kaim17IDynamicAvoidance" "\000\000\000\000" "Q24Kaim17IDynamicAvoidance" "\000\000\000\000\000\000\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000";
extern s32 D_0049BE40;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00408888;
extern s32 func_00370168();

s32 * func_003945A8(void) {
    if (D_0049BE40 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, &D_00408888);
        }
        func_00370168(&D_0049BE40, D_00408A40, &D_0040EBC0);
    }
    return &D_0049BE40;
}
