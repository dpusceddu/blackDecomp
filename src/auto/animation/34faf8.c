#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00343FE0();
extern s32 func_003438E0();

s32 func_0034FAF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));
    func_00343FE0((s32) sp, arg3);
    return func_003438E0(arg1, (s32) sp, arg2, M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0xC));
}
