#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00345F28(s8 *, s32 *, s32 *);
extern s32 * func_00348470(s32 *, s8 *);

s32 * func_00348560(s32 *arg0, s8 *arg1, s8 *arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 *var_2;

    *(s32 *)(sp + 0) = -1;
    var_2 = func_00345F28(arg1, arg0, sp);
    if (var_2 != NULL) {
        var_2 = func_00348470(arg0, arg2);
    }
    return var_2;
}
