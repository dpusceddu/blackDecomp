#include "auto/prelude.h"

extern s32 func_001B1080();

s32 func_001BFEA0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    func_001B1080(arg0);
    return 1;
}
