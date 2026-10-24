#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00395D10();
extern s32 func_00395C48();

s32 func_00395DD8(s32 arg0, s32 arg1) {
    func_00395D10(arg0, M2C_FIELD(arg1, s32 *, 0) + 8);
    return func_00395C48(arg0, arg1);
}

s32 func_00395E20(s32 arg0, s32 arg1) {
    func_00395C48(arg0, M2C_FIELD(arg1, s32 *, 0) + 0xC);
    return func_00395D10(arg0, arg1);
}
