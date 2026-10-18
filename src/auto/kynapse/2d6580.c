#include "auto/prelude.h"

extern s32 func_002D61B8();

s32 func_002D6580(void *arg0, u32 arg1) {
    if (arg1 < (u32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), u32 *, 8)) {
        M2C_FIELD(arg0, u32 *, 0x3C) = arg1;
        return 1;
    }
    return 0;
}

void func_002D65A8(void) {
    func_002D61B8(1, 0xFFFF);
}

void func_002D65C8(void) {
    func_002D61B8(0, 0xFFFF);
}
