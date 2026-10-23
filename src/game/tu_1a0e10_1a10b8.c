#include "auto/prelude.h"

extern s32 func_001A0F48();

s32 func_001A10B8(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0xA) = 0;
    M2C_FIELD(arg0, s8 *, 8) = 0;
    return func_001A0F48(arg0);
}
