#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00405EC0[];
const char rodata_00405EC0[48] __asm__("D_00405EC0") __attribute__((aligned(8))) = "Q24Kaim7CScript" "\000" "Q24Kaim7CObject" "\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049ABF8;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_0038B3F8(void) {
    if (D_0049ABF8 == 0) {
        func_00389100();
        func_00370168(&D_0049ABF8, D_00405EC0, &D_0040EBC0);
    }
    return &D_0049ABF8;
}
