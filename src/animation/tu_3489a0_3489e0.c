#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 * func_003489A8();

s32 func_003489E0(void) {
    s32 *temp_2;
    s32 var_16;

    var_16 = -1;
    temp_2 = func_003489A8();
    if (temp_2 != NULL) {
        var_16 = *temp_2;
    }
    return var_16;
}
