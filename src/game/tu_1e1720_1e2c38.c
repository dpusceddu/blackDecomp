#include "auto/prelude.h"

extern s32 func_001E1BA0();

void func_001E2C38(s32 arg0, void *arg1) {
    func_001E1BA0(arg1);
    M2C_FIELD(arg1, s8 *, 0x78) = 0;
}
