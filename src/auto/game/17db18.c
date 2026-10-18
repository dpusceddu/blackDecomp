#include "auto/prelude.h"

extern s32 func_0017E770();

void func_0017DB18(void *arg0) {
    if (func_0017E770() == 0) {
        M2C_FIELD(arg0, s8 *, 0x7E) = 1;
    }
}
