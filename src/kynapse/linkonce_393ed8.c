#include "ps2/prelude.h"

extern s32 D_0049BDB0;
extern s32 * func_00393F78();
extern s32 func_00370168();
extern s32 D_0049BDC0;
extern M2C_UNK D_00455AD0;
extern s32 D_0040EC38;
extern s32 func_00370188();

s32 * func_00393ED8(void) {
    if (D_0049BDB0 == 0) {
        func_00393F78();
        func_00370168(&D_0049BDB0, "Q24Kaim25CRepulsorDynamicAvoidance", &D_0049BDC0);
    }
    return &D_0049BDB0;
}

M2C_UNK * func_00393F28(void) {
    return &D_00455AD0;
}

s32 * func_00393F38(void) {
    if (D_0040EC38 == 0) {
        func_00370188(&D_0040EC38, "Q24Kaimt10CMetaClass2ZQ24Kaim17IDynamicAvoidanceZPFPQ24Kaim11CPathFinder_PQ24Kaim17IDynamicAvoidance");
    }
    return &D_0040EC38;
}
