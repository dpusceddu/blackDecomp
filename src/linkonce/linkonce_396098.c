#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00395E68(s32);

s32 * func_00396098(s32 *arg0, s32 arg1) {
    *arg0 = func_00395E68(arg1);
    return arg0;
}
