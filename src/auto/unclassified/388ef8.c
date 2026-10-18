#include "auto/prelude.h"

extern s32 func_002E34B8();
extern s32 (*D_003C87E0)();

s32 func_00388EF8(s32 arg0, s32 arg1) {
    s32 var_2;

    var_2 = func_002E34B8(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}
