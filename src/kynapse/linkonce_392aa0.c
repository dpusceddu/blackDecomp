#include "ps2/prelude.h"

extern char D_00407D08[];
const char rodata_00407D08[48] __asm__("D_00407D08") __attribute__((aligned(8))) = "24FindNearestEdgeTraversal" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049BD00;
extern s32 D_0049BCC0;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern M2C_UNK D_00407C70;
extern s32 func_00370168();
extern M2C_UNK D_00407C80;

s32 * func_00392AA0(void) {
    if (D_0049BD00 == 0) {
        if (D_0049BCC0 == 0) {
            if (D_0040EBC0 == 0) {
                func_00370188(&D_0040EBC0, &D_00407C70);
            }
            func_00370168(&D_0049BCC0, &D_00407C80, &D_0040EBC0);
        }
        func_00370168(&D_0049BD00, D_00407D08, &D_0049BCC0);
    }
    return &D_0049BD00;
}
