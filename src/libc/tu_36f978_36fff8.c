#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 D_0049BED0;
extern s32 * func_00370090();
extern s32 D_0040EC40;

s32 * func_0036FFF8(void) {
    if (D_0049BED0 == 0) {
        func_00370090();
        func_00370168(&D_0049BED0, "13bad_exception", &D_0040EC40);
    }
    return &D_0049BED0;
}
