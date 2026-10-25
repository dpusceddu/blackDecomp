#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_002E00F0();
extern M2C_UNK D_0044EF00;
extern M2C_UNK func_002D38C8;
extern M2C_UNK * D_0044F010;
extern M2C_UNK D_003E2AE0;
extern s32 func_002DFF10();
extern M2C_UNK D_003E32D0;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();

void func_002D3970(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044EF00, "CGotoAgent", &func_002D38C8, 0, 0, 0);
            return;
        }
        D_0044F010 = &D_003E2AE0;
    }
}

void * func_002D39D0(void *arg0) {
    func_002DFF10();
    M2C_FIELD(arg0, s8 *, 0x10) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E32D0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}

s32 func_002D3A10(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E32D0;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}


s32 func_002D3B00(void) {
    return 1;
}


void func_002D3C50(void) {
    func_002D3970(1, 0xFFFF);
}

void func_002D3C70(void) {
    func_002D3970(0, 0xFFFF);
}
