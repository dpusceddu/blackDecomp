#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_004041C8[];
const char rodata_004041C8[48] __asm__("D_004041C8") __attribute__((aligned(8))) = "Q24Kaim16CVertexTraversal" "\000\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern s32 D_0049A938;
extern s32 func_00389100();
extern s32 func_00370168();
extern s32 D_0040EBC0;

s32 * func_00389400(void) {
    if (D_0049A938 == 0) {
        func_00389100();
        func_00370168(&D_0049A938, D_004041C8, &D_0040EBC0);
    }
    return &D_0049A938;
}
