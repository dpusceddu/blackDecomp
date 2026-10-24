#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00298B78(s32 *, s32 *);

s32 * func_0029B0A8(s32 *arg0) {
    s32 *temp_2;

    func_00298B78(arg0, (s32 *)3);
    if (func_00298B78(arg0, (s32 *)1) != NULL) {
        func_00298B78(arg0, (s32 *)8);
        func_00298B78(arg0, (s32 *)8);
        M2C_FIELD(arg0, s32 **, 0x154) = func_00298B78(arg0, (s32 *)8);
    }
    M2C_FIELD(arg0, s32 **, 0x158) = func_00298B78(arg0, (s32 *)0xE);
    func_00298B78(arg0, (s32 *)1);
    temp_2 = func_00298B78(arg0, (s32 *)0xE);
    M2C_FIELD(arg0, s32 **, 0x15C) = temp_2;
    return temp_2;
}

s32 * func_0029B138(s32 *arg0) {
    func_00298B78(arg0, (s32 *)1);
    func_00298B78(arg0, (s32 *)8);
    func_00298B78(arg0, (s32 *)1);
    func_00298B78(arg0, (s32 *)7);
    func_00298B78(arg0, (s32 *)1);
    func_00298B78(arg0, (s32 *)0x14);
    func_00298B78(arg0, (s32 *)1);
    func_00298B78(arg0, (s32 *)0x16);
    func_00298B78(arg0, (s32 *)1);
    return func_00298B78(arg0, (s32 *)0x16);
}
