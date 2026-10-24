#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_003D5328;
extern s32 D_003D532C;
extern M2C_UNK D_003D5330;

f32 func_00351A08(void) {
    s32 temp_2;

    temp_2 = (D_003D5328 & D_003D532C) * 4;
    D_003D5328 += 1;
    return M2C_FIELD((temp_2 + ((s32) &D_003D5330)), f32 *, 0);
}
