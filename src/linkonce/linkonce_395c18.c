#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_003959E8(s32);

s32 * func_00395C18(s32 *arg0, s32 arg1) {
    *arg0 = func_003959E8(arg1);
    return arg0;
}
