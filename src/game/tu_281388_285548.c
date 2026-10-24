#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00285548(void *arg0) {
    s32 temp_3;
    s32 var_5;
    s32 var_6;
    void *var_4;

    var_4 = (void *) (((s8 *) arg0) + 0x13A0);
    var_6 = 0;
    var_5 = 0;
    do {
        if (M2C_FIELD(var_4, u8 *, 0x35) != 0) {
            var_6 |= 1 << var_5;
        }
        var_5 += 1;
        var_4 = (void *) (((s8 *) var_4) + 0x3C);
    } while (var_5 < 0xB);
    if (var_5 < 0x18) {
        do {
            temp_3 = 1 << var_5;
            var_5 += 1;
            var_6 |= temp_3;
        } while (var_5 < 0x18);
    }
    return var_6;
}
