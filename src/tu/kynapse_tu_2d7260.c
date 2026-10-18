/* Translation unit kynapse/tu_2d7260 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern char D_004046F8[];
const char rodata_004046F8[56] __asm__("D_004046F8") __attribute__((aligned(8))) = "CWanderAgent" "\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000\000";
extern s32 func_002E00F0();
extern M2C_UNK D_0044F360;
extern M2C_UNK func_002D7260;
extern M2C_UNK * D_0044F470;
extern M2C_UNK D_003E2AE0;
extern M2C_UNK D_003E3BB0;
extern s32 func_002DFF98();
extern s32 (*D_003C87E0)();
extern M2C_UNK D_004514F8;
extern s32 func_002E1C58();
extern M2C_UNK D_004512B0;
extern s32 func_002E0018();

void func_002D74A0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F360, D_004046F8, &func_002D7260, 0, 0, 0);
            return;
        }
        D_0044F470 = &D_003E2AE0;
    }
}

/* Assembly between the functions: func_002D7500 (88 bytes) */

s32 func_002D7558(s32 arg0, s32 arg1) {
    s32 var_2;

    M2C_FIELD(arg0, u32 *, 0) = &D_003E3BB0;
    var_2 = func_002DFF98(arg0, 0);
    if (arg1 & 1) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

/* Assembly between the functions: func_002D75B0 (224 bytes), func_002D7690 (16 bytes) */

s32 func_002D76A0(void *arg0, s32 arg1) {
    s32 temp_2;
    void *temp_3;
    void *temp_4;

    temp_4 = arg0 + 0x10;
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) M2C_FIELD(&D_004514F8, f32 *, 0);
    M2C_FIELD(temp_4, f32 *, 4) = (f32) M2C_FIELD(&D_004514F8, f32 *, 4);
    M2C_FIELD(temp_4, f32 *, 8) = (f32) M2C_FIELD(&D_004514F8, f32 *, 8);
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0x7FFFFFFF;
    temp_2 = func_002E1C58(M2C_FIELD(arg0, void **, 8), &D_004512B0);
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
    M2C_FIELD(arg0, s32 *, 0x24) = temp_2;
    if (func_002E0018(arg0, arg1) == 0) {
        return 0;
    }
    temp_3 = M2C_FIELD(arg0, void **, 0);
    return M2C_FIELD(temp_3, s32 (**)(void *), 0x44)(arg0 + M2C_FIELD(temp_3, s16 *, 0x40)) != 0;
}

/* Assembly between the functions: func_002D7748 (88 bytes), func_002D77A0 (160 bytes), func_002D7840 (240 bytes) */

void func_002D7930(void) {
    func_002D74A0(1, 0xFFFF);
}

void func_002D7950(void) {
    func_002D74A0(0, 0xFFFF);
}
