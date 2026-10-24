#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void ** D_003C87E4;
extern s32 D_003C87F0;

s32 func_00383CA0(s32 arg0) {
    s32 (*var_2)(s32, s32);
    s32 temp_5;
    void *temp_3;

    temp_3 = *D_003C87E4;
    temp_5 = M2C_FIELD(temp_3, s32 (**)(void *, s32, void **), 0x14)((void *) (((s8 *) D_003C87E4) + M2C_FIELD(temp_3, s16 *, 0x10)), arg0, D_003C87E4);
    var_2 = D_003C87F0;
    if (var_2 != NULL) {
        var_2 = var_2(arg0, temp_5);
    }
    return (s32) var_2;
}
