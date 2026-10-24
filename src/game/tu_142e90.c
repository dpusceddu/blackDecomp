#include "include_asm.h"
#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00142E90(s32 *arg0, s32 *arg1) {
    s32 *var_3;
    s32 var_2;

    M2C_FIELD(arg0, s32 *, 0) = (s32) arg1;
    M2C_FIELD(arg0, s8 *, 0x1A) = 1;
    var_3 = (s32 *) (((s8 *) arg0) + 0x14);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    var_2 = 2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    M2C_FIELD(arg0, s8 *, 0x19) = 0;
    do {
        *var_3 = 0;
        var_2 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + -4);
    } while (var_2 >= 0);
    return var_2;
}
