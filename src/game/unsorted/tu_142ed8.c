#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00143550(void *);

s32 func_00142ED8(void *arg0, s32 arg1, s32 arg2) {
    s32 *var_2;
    s32 var_3;

    var_3 = 2;
    var_2 = (s32 *) (((s8 *) arg0) + 0x14);
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (s32 *) (((s8 *) var_2) + -4);
    } while (var_3 >= 0);
    func_00143550(arg0);
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s8 *, 0x1A) = 1;
    M2C_FIELD(arg0, s8 *, 0x18) = (s8) arg2;
    M2C_FIELD(arg0, s8 *, 0x19) = 0;
    return 1;
}
