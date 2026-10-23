#include "auto/prelude.h"

extern s32 func_001DD6C0(void *);

void func_001D9250(void *arg0) {
    if ((u32) (M2C_FIELD(arg0, s32 *, 4) - 5) < 2U) {
        func_001DD6C0(M2C_FIELD(arg0, void **, 0x10));
        M2C_FIELD(arg0, s32 *, 4) = 7;
    }
}
