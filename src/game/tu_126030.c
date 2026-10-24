#include "ps2/prelude.h"

extern s32 func_0012A1E0();
extern void * D_0040F4D0;

void func_00126030(void *arg0, s128 arg1) {
    M2C_FIELD(arg0, s128 *, 0xA0) = arg1;
    func_0012A1E0(D_0040F4D0, arg0);
}
