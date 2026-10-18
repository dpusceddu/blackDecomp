/* Translation unit kynapse/tu_2d3c90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern char D_00404400[];
const char rodata_00404400[56] __asm__("D_00404400") __attribute__((aligned(8))) = "CHideAgent" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000" "Q24Kaim11CGraphPoint" "\000\000\000\000";
extern s32 func_002E00F0();
extern M2C_UNK D_0044F018;
extern M2C_UNK func_002D3C90;
extern M2C_UNK * D_0044F128;
extern M2C_UNK D_003E2AE0;
extern M2C_UNK D_003E3428;
extern s32 (*D_003C87E0)();
extern s32 func_002DFF98();

void func_002D5008(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E00F0(&D_0044F018, D_00404400, &func_002D3C90, 0, 0, 0);
            return;
        }
        D_0044F128 = &D_003E2AE0;
    }
}

/* Assembly between the functions: func_002D5068 (128 bytes) */

s32 func_002D50E8(s32 arg0, s32 arg1) {
    s32 temp_4;
    s32 temp_4_2;
    s32 var_2;

    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E3428;
    temp_4 = M2C_FIELD(arg0, s32 *, 0x40);
    if (temp_4 != 0) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, s32 *, 0x44);
    if (temp_4_2 != 0) {
        D_003C87E0(temp_4_2);
    }
    func_002DFF98(arg0, 0);
    var_2 = arg1 & 1;
    if (var_2 != 0) {
        var_2 = D_003C87E0(arg0);
    }
    return var_2;
}

s32 func_002D5178(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x10) != 0) {
        return M2C_FIELD(arg0, s32 *, 0xC) != 0;
    }
    return 0;
}

/* Assembly between the functions: func_002D5198 (40 bytes), func_002D51C0 (120 bytes), func_002D5238 (16 bytes), func_002D5248 (224 bytes), func_002D5328 (64 bytes) */

s32 func_002D5368(s32 arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x54) != 0) {
        goto block_2;
    }
    goto block_7;
block_2:
    if (M2C_FIELD(arg0, u8 *, 0x55) != 0) {
        goto block_5;
    }
    goto block_7;
block_5:
    return arg0 + 0x14;
block_7:
    return M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x14) + 0x30;
}

/* Assembly between the functions: func_002D5398 (24 bytes) */

void func_002D53B0(void) {
    func_002D5008(1, 0xFFFF);
}

void func_002D53D0(void) {
    func_002D5008(0, 0xFFFF);
}
