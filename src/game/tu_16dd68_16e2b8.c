#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s8 * func_00172C88(void *, s128, s128);
extern s8 * func_0016E588(void *, s128);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0016E2B8(void *arg0, s128 arg1, s128 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s8 *var_2;

    if (arg3 != 0) {
        return func_00172C88(arg0 + 0x22800, arg1, arg2);
    }
    var_2 = func_0016E588(arg0, arg2);
    if (var_2 != NULL) {
        var_2 = func_00181F48(var_2 + 0xC80, 0, 0x11, 0.0f, 1.0f);
    }
    return var_2;
}
