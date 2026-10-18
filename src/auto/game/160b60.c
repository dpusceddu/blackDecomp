#include "auto/prelude.h"

extern s32 func_001F2A38();
extern s32 D_0040F51C;
extern s32 func_00108818();
extern s32 D_0040F4C4;

void func_00160B60(s64 **arg0, s32 arg1) {
    if ((u32) (M2C_FIELD(arg0, s32 *, 8) - 1) >= 3U) {
        M2C_FIELD(arg0, s32 *, 8) = 1;
        if (arg1 != 0) {
            func_001F2A38(D_0040F51C, func_00108818(D_0040F4C4, M2C_FIELD(M2C_FIELD(arg0, s64 **, 0), s32 *, 0x10)), arg0);
        }
    }
}
