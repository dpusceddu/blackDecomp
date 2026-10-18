#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00345F28(s8 *, s32 *, s32 *);
extern s32 func_00348F28(s32 *, s32, s32, s32, s32, f32);

s32 func_00349158(s32 *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 var_18;

    var_18 = 0;
    if ((arg0 != NULL) && (arg1 != NULL)) {
        *(s32 *)(sp + 0) = -1;
        if (func_00345F28(arg1, arg0, sp) != NULL) {
            var_18 = func_00348F28(arg0, *(s32 *)(sp + 0), arg3, 0, arg2, 0.0f);
        }
    }
    return var_18;
}
