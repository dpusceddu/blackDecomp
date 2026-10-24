#include "ps2/prelude.h"

extern s32 (*D_00451250)();

s32 func_002E27D0(void) {
    return D_00451250() & 0xFF;
}
