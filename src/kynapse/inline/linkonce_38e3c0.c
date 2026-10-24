#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00406A98[];
const char rodata_00406A98[48] __asm__("D_00406A98") __attribute__((aligned(8))) = "Q24Kaim15CPointInfoClass" "\000\000\000\000\000\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 D_0049BA40;
extern s32 D_0040EC10;
extern s32 func_00370188();
extern M2C_UNK D_00406A50;
extern s32 func_00370168();

s32 * func_0038E3C0(void) {
    if (D_0049BA40 == 0) {
        if (D_0040EC10 == 0) {
            func_00370188(&D_0040EC10, &D_00406A50);
        }
        func_00370168(&D_0049BA40, D_00406A98, &D_0040EC10);
    }
    return &D_0049BA40;
}
