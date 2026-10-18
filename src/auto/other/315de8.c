#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00315380();
extern M2C_UNK D_0040A2D8;
extern s32 func_00311278();
extern M2C_UNK func_003112E0;
extern M2C_UNK * func_00312C48();
extern s32 func_00315440();
extern s32 func_003159C8();

void * func_00315DE8(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_4;
    s32 var_18;
    void *var_17;

    var_17 = arg0;
    var_18 = arg1;
    if (var_17 == NULL) {
        var_17 = func_00315380(&D_0040A2D8);
    }
    if (var_18 == 0) {
        *(s32 *)(sp + 0) = 0;
        *(s32 *)(sp + 4) = M2C_FIELD(var_17, s32 *, 0x40);
        func_00311278(&func_003112E0, sp);
        var_18 = *(s32 *)(sp + 0);
    }
    temp_4 = M2C_FIELD(var_17, s32 *, 0x44);
    if ((temp_4 != 0) && (M2C_FIELD(arg5, M2C_UNK **, 0x50) == NULL)) {
        M2C_FIELD(arg5, M2C_UNK **, 0x50) = func_00312C48(temp_4, 0x30806);
        M2C_FIELD(arg5, s32 *, 0x54) = (s32) (M2C_FIELD(arg5, s32 *, 0x54) | 8);
    }
    M2C_FIELD(arg5, s32 *, 0x58) = var_18;
    M2C_FIELD(arg5, void **, 0xC) = var_17;
    if (func_00315440(var_17, arg5 + 0x2C) == 0) {
        func_003159C8(arg5, arg5 + 0x10, 0);
    }
    if (arg4 != 0) {
        if (M2C_FIELD(arg5, u8 *, 0x39) == 1) {
            M2C_FIELD(arg5, s32 *, 0x54) = (s32) (M2C_FIELD(arg5, s32 *, 0x54) | 2);
        }
    }
    return arg5;
}
