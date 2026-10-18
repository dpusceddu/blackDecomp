#include "auto/prelude.h"

extern s32 func_001080C0();
extern s32 func_001080F0();

void func_00101F90(void) {
    func_001080C0();
}

M2C_UNK * func_00101FB0(void) {
    if (func_001080C0() != 0) {
        return "Main";
    }
    if (func_001080F0() != 0) {
        return "Resource";
    }
    return "Unknown";
}
