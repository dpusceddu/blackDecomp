#include "auto/prelude.h"

extern s32 func_00174320();
extern void func_0017B3C0(void *arg0);

void func_0017B220(void) {
    func_00174320();
}

void func_0017B240(s32 arg0) {
    func_0017B3C0(arg0 + 0x10);
}

void func_0017B260(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}
