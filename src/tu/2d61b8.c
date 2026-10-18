#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044F130;
extern M2C_UNK func_002D53F0;
extern M2C_UNK * D_0044F240;
extern M2C_UNK D_003E2AE0;
extern s32 func_002DFF10();
extern M2C_UNK D_003E3688;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();

void func_002D61B8(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F130, "CPathWayAgent", &func_002D53F0, 0, 0, 0);
            return;
        }
        D_0044F240 = &D_003E2AE0;
    }
}

void * func_002D6218(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3688;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
    M2C_FIELD(arg0, s32 *, 0x3C) = 0;
    return arg0;
}

s32 func_002D6278(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3688;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}
