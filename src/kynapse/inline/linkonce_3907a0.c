#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BBA0;
extern s32 func_00390AE0();
extern s32 func_00370168();
extern M2C_UNK D_0049BBC0;
extern M2C_UNK D_003EC900;

s32 * func_003907A0(void) {
    if (D_0049BBA0 == 0) {
        func_00390AE0();
        func_00370168(&D_0049BBA0, "Q24Kaim18CPathCostHeuristic", &D_0049BBC0);
    }
    return &D_0049BBA0;
}

void * func_003907F0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003EC900;
    return arg0;
}
