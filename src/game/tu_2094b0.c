#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_002094B0(void *arg0) {
    s32 var_2;
    void *var_4;

    var_4 = arg0;
    var_2 = 0x6D;
    do {
        M2C_FIELD(var_4, s32 *, 0) = 0;
        var_2 -= 1;
        M2C_FIELD(var_4, s32 *, 4) = 0;
        var_4 = (void *) (((s8 *) var_4) + 8);
    } while (var_2 >= 0);
    return var_2;
}
