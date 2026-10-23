#include "auto/prelude.h"

extern s32 func_002DA0B0();
extern s32 D_00450EB8;
extern s32 D_00450FD8;
extern s32 D_004510F0;

void func_002DA188(void) {
    func_002DA0B0(1, 0xFFFF);
}

void func_002DA1A8(void) {
    func_002DA0B0(0, 0xFFFF);
}

s32 func_002DA1C8(void) {
    if ((D_00450EB8 == -1) || (D_00450FD8 == -1) || (D_004510F0 == -1)) {
        return 0;
    }
    return 1;
}
