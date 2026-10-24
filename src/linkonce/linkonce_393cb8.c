#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BD70;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_00393CB8(void) {
    if (D_0049BD70 == 0) {
        func_00389100();
        func_00370168(&D_0049BD70, "Q24Kaimt10CStringMap2ZPFRQ24Kaim11CPathFinder_UcUi16", &D_0040EBC0);
    }
    return &D_0049BD70;
}
