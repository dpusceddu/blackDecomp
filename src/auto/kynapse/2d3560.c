#include "auto/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_003E3130;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();

s32 func_002D3560(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3130;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}
