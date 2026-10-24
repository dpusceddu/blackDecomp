#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

const char rodata_0040BEC8[32] __asm__("D_0040BEC8") __attribute__((aligned(8))) = "9exception" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern char D_0040BEC8[];
extern s32 D_0040EC40;

s32 * func_00370090(void) {
    if (D_0040EC40 == 0) {
        func_00370188(&D_0040EC40, D_0040BEC8);
    }
    return &D_0040EC40;
}
