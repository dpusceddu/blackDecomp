#include "auto/prelude.h"

extern s32 func_00172418();

void func_001723E8(void *arg0) {
    if (func_00172418() != 0) {
        M2C_FIELD(arg0, s8 *, 0x1B5) = 1;
    }
}
