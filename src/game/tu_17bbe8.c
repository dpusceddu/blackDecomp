#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0017BBE8(void *arg0, void *arg1) {
    s32 var_5;
    s8 *var_3;

    var_3 = (s8 *) (((s8 *) arg0) + 0x81);
    var_5 = 1;
    M2C_FIELD(arg0, s32 *, 0x84) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
    do {
        *var_3 = 0;
        var_5 -= 1;
        var_3 = (s8 *) (((s8 *) var_3) + -1);
    } while (var_5 >= 0);
    return 1;
}
