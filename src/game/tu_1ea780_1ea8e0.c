#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001EAA20(void *, s32, s32, void *, u16);

s32 func_001EA8E0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0) {
    s32 temp_5;
    s32 var_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg1, void **, 0x110);
    var_2 = -1;
    if (temp_3 != NULL) {
        temp_5 = M2C_FIELD(temp_3, s32 *, 0x10);
        if ((temp_5 != -1) && (M2C_FIELD(temp_3, f32 *, 8) <= fparg0)) {
            var_2 = func_001EAA20(arg0, temp_5, M2C_FIELD(temp_3, s32 *, 0xC), arg1, M2C_FIELD(temp_3, u16 *, 0x1C));
        }
    }
    return var_2;
}
