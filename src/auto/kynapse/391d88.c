#include "auto/prelude.h"

extern char D_00407C40[];
const char rodata_00407C40[48] __asm__("D_00407C40") __attribute__((aligned(8))) = "Q24Kaim15CGraphTraversal" "\000\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BCC0;
extern s32 func_00389100();
extern s32 func_00370168();
extern M2C_UNK D_0040EBC0;

s32 * func_00391D88(void) {
    if (D_0049BCC0 == 0) {
        func_00389100();
        func_00370168(&D_0049BCC0, D_00407C40, &D_0040EBC0);
    }
    return &D_0049BCC0;
}
