#include "auto/prelude.h"

extern void func_001A7450();
extern s32 func_001A6E58();

s32 func_001A5EE8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x54) != 0) {
        func_001A7450();
        if (M2C_FIELD(arg0, s32 *, 0x58) != 0) {
            func_001A6E58(arg0);
        }
    }
    M2C_FIELD(arg0, s8 *, 0xB8) = 0;
    return 1;
}
