#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0032A4B0(void *arg0, void *arg1) {
    f32 *var_4;
    u32 var_2;
    u32 var_3;

    var_2 = M2C_FIELD(arg1, u32 *, 4);
    var_3 = 0;
    if (var_2 != 0) {
        var_4 = (f32 *) (((s8 *) arg0) + 0x18);
        do {
            *var_4 = 1.0f;
            var_3 += 1;
            var_2 = var_3 < (u32) M2C_FIELD(arg1, u32 *, 4);
            var_4 = (f32 *) (((s8 *) var_4) + 4);
        } while (var_2 != 0);
    }
    return (s32) var_2;
}
