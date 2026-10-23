#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001077B8(s32, s32, s32, f32, f32);
extern s32 func_00107800(s32, s32, s32, f32, f32, f32, f32);

s32 func_00107730(s32 arg0, s32 arg1, s8 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    s32 var_2;

    switch (arg1) {                                 /* irregular */
    case 0:
        var_2 = func_001077B8(arg0, (s32) arg2, arg3, fparg0, fparg1);
block_5:
        return var_2;
    case 1:
        var_2 = func_00107800(arg0, (s32) arg2, arg3, fparg0, fparg1, fparg2, fparg3);
        goto block_5;
    default:
        return 1;
    }
}
