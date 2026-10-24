#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern void * D_003BE8E0;
extern s32 func_00252B10();

s32 func_0022D880(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_6;
    s32 var_2;

    temp_6 = (M2C_FIELD(arg1, s32 *, 0) + 3) & 0xFFFFFFFC;
    temp_2 = temp_6 + 4;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_2 + M2C_FIELD(temp_6, s32 *, 0));
    var_2 = M2C_FIELD(D_003BE8E0, s32 *, 4);
    if (var_2 != 0) {
        var_2 = M2C_FIELD(arg0, s32 *, 0);
        if (var_2 == 0) {
            var_2 = func_00252B10((s32) D_003BE8E0);
        }
    }
    return var_2;
}
