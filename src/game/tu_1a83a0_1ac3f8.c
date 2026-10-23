#include "auto/prelude.h"

extern void ** func_001AC040();

f32 func_001AC3F8(void) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (M2C_FIELD(*func_001AC040(), u8 *, 0x3A9) != 0) {
        var_f0 = 1.0f;
    }
    return var_f0;
}
