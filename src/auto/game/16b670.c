#include "auto/prelude.h"

extern s32 func_001C31F8();

void func_0016B670(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 1;
    func_001C31F8();
}
