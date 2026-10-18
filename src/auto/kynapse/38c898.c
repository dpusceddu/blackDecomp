#include "auto/prelude.h"

extern char D_004062B8[];
extern char D_004062C8[];
const char rodata_004062B8[16] __asm__("D_004062B8") __attribute__((aligned(8))) = "Q24Kaim7CObject" "\000";
const char rodata_004062C8[32] __asm__("D_004062C8") __attribute__((aligned(8))) = "Q24Kaim5CData" "\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049B080;
extern s32 D_0040EBC0;
extern s32 func_00370188();
extern s32 func_00370168();

s32 * func_0038C898(void) {
    if (D_0049B080 == 0) {
        if (D_0040EBC0 == 0) {
            func_00370188(&D_0040EBC0, D_004062B8);
        }
        func_00370168(&D_0049B080, D_004062C8, &D_0040EBC0);
    }
    return &D_0049B080;
}
