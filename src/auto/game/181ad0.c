#include "auto/prelude.h"

extern s32 func_0018BE88();
extern s32 func_00181B08();

void func_00181AD0(void *arg0, s32 arg1) {
    u8 sp[8];
    if (arg1 != 0) {
        func_0018BE88(sp);
        func_00181B08(arg0, sp);
    }
}
