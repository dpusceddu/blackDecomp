#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00396190();
extern s32 func_003960C8();

s32 func_00396258(s32 arg0, s32 arg1) {
    func_00396190(arg0, M2C_FIELD(arg1, s32 *, 0) + 8);
    return func_003960C8(arg0, arg1);
}

s32 func_003962A0(s32 arg0, s32 arg1) {
    func_003960C8(arg0, M2C_FIELD(arg1, s32 *, 0) + 0xC);
    return func_00396190(arg0, arg1);
}
