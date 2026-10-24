#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0038E730();
extern s32 (*D_003C87E0)();

s32 func_0038E7C0(s32 arg0, s32 arg1) {
    s32 var_2;

    var_2 = func_0038E730(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}
