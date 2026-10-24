#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_0026BC88(void *arg0, f32 fparg0) {
    s32 var_3;

    var_3 = 0;
    if ((fparg0 < 1.0f) && (fparg0 >= 0.0f)) {
        var_3 = 1;
    }
    if ((M2C_FIELD(arg0, u8 *, 0xC) == 0) || (var_3 == 0)) {
        return 0;
    }
    M2C_FIELD(arg0, s8 *, 0x47) = (s8) (s32) (fparg0 * 255.0f);
    return 1;
}
