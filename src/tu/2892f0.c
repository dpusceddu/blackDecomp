#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_00288E28();
extern s32 func_00289028();
extern s32 func_00288FB0();

s32 func_002892F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[24] __attribute__((aligned(16)));

    func_00288E28((s32) sp, arg1 + 0x10, arg2, 0, (s32) "Periodic", 1);
    func_00289028((s32) (sp + 16), (s32) sp, (s32) "Period", arg3);
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 0);
    return arg0;
}

s32 func_00289360(s32 arg0, s32 arg1, s32 arg2) {
    func_00288FB0(arg0, arg1 + 0x28, arg2);
    return arg0;
}
