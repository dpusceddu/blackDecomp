#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003D1138;
extern s32 func_003298D8(void *, s32 *, s32, s32, s32, s32 *);
extern M2C_UNK D_0045C120;
extern s32 func_00329928(void *, s32, s32);

s32 func_003291E0(void *arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 temp_3;
    s32 var_2;

    *(s32 *)(sp + 0) = arg1;
    temp_3 = D_003D1138 == NULL;
    if (arg2 != 0) {
        if (temp_3 != 0) {
            func_003298D8(&D_0045C120, sp, M2C_FIELD(arg0, s32 *, 0x4C), M2C_FIELD(arg0, s32 *, 0x18), 0x10, (sp + 4));
            var_2 = *(s32 *)(sp + 4);
        } else {
            var_2 = M2C_FIELD(arg0, s32 *, 0x4C) + arg1;
        }
    } else if (temp_3 != 0) {
        var_2 = func_00329928(&D_0045C120, arg1, M2C_FIELD(arg0, s32 *, 0x4C));
    } else {
        var_2 = M2C_FIELD(arg0, s32 *, 0x4C) - arg1;
    }
    M2C_FIELD(arg0, s32 *, 0x4C) = var_2;
    return var_2;
}
