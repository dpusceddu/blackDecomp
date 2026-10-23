#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_001EC8D8();
extern s32 func_001EBEB8();
extern s32 func_001EC600();

s32 func_001EC970(s32 arg0, s32 arg1, s32 arg2, s128 arg3) {
    s32 temp_2;
    s32 temp_2_2;

    temp_2_2 = func_001EC8D8(arg0, arg1, arg2);
    if (temp_2_2 != 0) {
        if (M2C_FIELD(temp_2_2, s32 *, 0x14) == 3) {
            temp_2 = func_001EBEB8(arg0, M2C_FIELD(temp_2_2, s32 *, 0x10));
            if (temp_2 != 0) {
                return func_001EC600(temp_2, temp_2_2, arg3);
            }
            goto block_4;
        }
        /* Duplicate return node #5. Try simplifying control flow for better match */
        return 0;
    }
block_4:
    return 0;
}
