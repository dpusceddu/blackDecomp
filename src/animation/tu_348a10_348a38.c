#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003D2B04;
extern s32 D_003D2B00;

f32 func_00348A38(s32 arg0, void *arg1) {
    f32 (*temp_2)(void *, s32, s32);
    f32 var_f0;

    var_f0 = 0.0f;
    if ((arg0 >= 0) && (arg0 < D_003D2B04)) {
        temp_2 = M2C_FIELD(((arg0 * 8) + D_003D2B00), f32 (**)(void *, s32, s32), 4);
        if (temp_2 != NULL) {
            var_f0 = temp_2(arg1, arg0, arg0);
        }
    }
    return var_f0;
}
