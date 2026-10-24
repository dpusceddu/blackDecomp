#include "ps2/prelude.h"

extern s32 func_001735E0();
extern s32 func_00173610();
extern s32 func_00173690();
extern s32 func_00193A28();

s32 func_001975D0(s32 arg0) {
    s32 temp_16;
    s32 var_2;

    temp_16 = arg0 + 8;
    var_2 = func_001735E0(temp_16);
    if (var_2 != 0) {
        var_2 = func_00173610(temp_16);
        if (var_2 != 0) {
            func_00173690(temp_16);
            var_2 = func_00193A28(arg0, 0x1F, 0);
        }
    }
    return var_2;
}
