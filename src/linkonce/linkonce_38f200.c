#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004070A8[];
const char rodata_004070A8[40] __asm__("D_004070A8") __attribute__((aligned(8))) = "Q24Kaim10CTeamClass" "\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BAC0;
extern s32 D_0040EC20;
extern s32 func_00370188();
extern M2C_UNK D_00407068;
extern s32 func_00370168();

s32 * func_0038F200(void) {
    if (D_0049BAC0 == 0) {
        if (D_0040EC20 == 0) {
            func_00370188(&D_0040EC20, &D_00407068);
        }
        func_00370168(&D_0049BAC0, D_004070A8, &D_0040EC20);
    }
    return &D_0049BAC0;
}
