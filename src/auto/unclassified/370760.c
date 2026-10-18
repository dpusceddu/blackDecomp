#include "auto/prelude.h"

const char rodata_0040BFD8[32] __asm__("D_0040BFD8") __attribute__((aligned(8))) = "9type_info" "\000\000\000\000\000\000" "bad_alloc" "\000\000\000\000\000\000\000";
extern char D_0040BFD8[];
#include "types_ghidra.h"
extern s32 D_0040EC48;

s32 * func_00370760(void) {
    if (D_0040EC48 == 0) {
        func_00370188(&D_0040EC48, D_0040BFD8);
    }
    return &D_0040EC48;
}
