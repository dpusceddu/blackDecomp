#include "auto/prelude.h"
#include "types_ghidra.h"

s32 func_00322DD8(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    func_00322E00(arg0, 0, (s32) sp);
    return *(s32 *)(sp + 0);
}

s32 func_00322E00(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s32 *, 0x28);
    return arg0;
}
