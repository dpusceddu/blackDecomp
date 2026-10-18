#include "auto/prelude.h"

extern void func_0017B908(void *arg0, void *arg1);
extern void * D_0040F4D4;

void func_0017B310(void *arg0) {
    if ((u32) (M2C_FIELD(arg0, s32 *, 0x24) - 1) < 2U) {
        func_0017B908(D_0040F4D4 + 0x1290, arg0);
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
    }
}
