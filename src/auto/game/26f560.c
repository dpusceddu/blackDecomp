#include "auto/prelude.h"

s32 func_0026F560(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xD8);
    if (temp_2 < 0) {
        return -1;
    }
    return temp_2 << 0xA;
}
