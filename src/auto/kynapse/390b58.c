#include "auto/prelude.h"

extern char D_00407628[];
const char rodata_00407628[40] __asm__("D_00407628") __attribute__((aligned(8))) = "Q24Kaim11IConstraint" "\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BBE0;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_00390B58(void) {
    if (D_0049BBE0 == 0) {
        func_00389100();
        func_00370168(&D_0049BBE0, D_00407628, &D_0040EBC0);
    }
    return &D_0049BBE0;
}
