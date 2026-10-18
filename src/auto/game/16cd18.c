#include "auto/prelude.h"

extern s32 func_00273888();
extern void * D_0040F4D0;
extern M2C_UNK func_0016CD58;

void func_0016CD18(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11C) = 1;
    func_00273888(D_0040F4D0 + 0x4920, arg0 + 0x160, &func_0016CD58, arg0);
}
