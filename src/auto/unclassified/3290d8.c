#include "auto/prelude.h"

extern s32 func_003287F0();

s32 func_003290D8(s32 arg0) {
    if (func_003287F0(arg0, M2C_FIELD(arg0, s32 *, 0x58)) != 0) {
        return M2C_FIELD(arg0, s32 *, 0x4C);
    }
    return 0;
}
