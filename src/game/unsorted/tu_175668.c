#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001749E8();

s32 func_00175668(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 0xA, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    return 1;
}
