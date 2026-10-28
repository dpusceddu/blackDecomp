#include "ps2/prelude.h"

s32 func_001DC448(void* owner) {
    switch (M2C_FIELD(owner, u32*, 0x1930)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 14:
        case 15:
        default: break;
        case 6: M2C_FIELD(owner, u32*, 0x1930) = 5; break;
        case 10:
        case 11: M2C_FIELD(owner, u32*, 0x1930) = 12;
        case 7:
        case 8:
        case 9:
        case 12:
        case 13: return 0;
    }
    return 1;
}
