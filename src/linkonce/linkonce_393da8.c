#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00408538[];
const char rodata_00408538[120] __asm__("D_00408538") __attribute__((aligned(8))) = "Q24Kaimt10CStringMap2ZPFRQ24Kaim11CPathFinderRQ24Kaim4MoveRCQ24Kaim7CVector_UcUi16" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BDA0;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_00393DA8(void) {
    if (D_0049BDA0 == 0) {
        func_00389100();
        func_00370168(&D_0049BDA0, D_00408538, &D_0040EBC0);
    }
    return &D_0049BDA0;
}
