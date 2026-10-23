#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00345F28();
extern s32 func_00347C08(s32 *, s32, s32, f32);

s32 func_00347CA0(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 var_18;

    var_18 = 0;
    if ((arg0 != NULL) && (arg1 != 0)) {
        *(s32 *)(sp + 0) = -1;
        if (func_00345F28(arg1, arg0, sp) != 0) {
            var_18 = func_00347C08(arg0, *(s32 *)(sp + 0), arg2, fparg0);
        }
    }
    return var_18;
}
