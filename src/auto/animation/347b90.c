#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003509E0(s32 *, s32, s32, s32, f32, f32, f32);

s32 func_00347B90(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1) {
    s32 var_4;

    var_4 = 0;
    if (arg0 != NULL) {
        if (arg1 != -1) {
            func_003509E0(arg0, arg1, arg2, arg3, fparg0, 0.0f, fparg1);
            var_4 = 1;
            *arg0 &= 0xFFDFFFFF;
        }
        *arg0 &= 0xEDFFFFFE;
    }
    return var_4;
}
