#include "auto/prelude.h"

#include "types_ghidra.h"
extern s8 D_003C15F8;
extern s32 func_0029CEE8();

s32 func_0029CF58(void) {
    if (M2C_FIELD(&D_003C15F8, s8 *, 0) == 0) {
        func_0029CEE8();
    }
    return M2C_FIELD(&D_003C15F8, s8 *, 4) == 0x54;
}
