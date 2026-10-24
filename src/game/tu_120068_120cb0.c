#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0011D490();
extern s32 func_0011D430();

void func_00120CB0(void) {
    func_0011D490();
}

s32 func_00120CD0(s32 arg0) {
    return func_0011D430(arg0, 1);
}
