#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00395890();
extern s32 func_003957C8();

s32 func_00395958(s32 arg0, s32 arg1) {
    func_00395890(arg0, M2C_FIELD(arg1, s32 *, 0) + 8);
    return func_003957C8(arg0, arg1);
}

s32 func_003959A0(s32 arg0, s32 arg1) {
    func_003957C8(arg0, M2C_FIELD(arg1, s32 *, 0) + 0xC);
    return func_00395890(arg0, arg1);
}
