/* Translation unit tu_18f7c8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0018E488();
extern s32 func_00190380(void *, s32, u8);
extern s32 func_0018D698(s32, M2C_UNK);
extern s32 func_00185C38();
extern s32 func_001897E8();
extern s32 func_00180A00(s32);
extern s32 func_0018E4C0();

void func_0018FB40(void *arg0) {
    func_0018E488();
    func_00190380(arg0, M2C_FIELD(arg0, s32 *, 0x2C), M2C_FIELD(arg0, u8 *, 0x3C));
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}

s32 func_0018FB88(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_7;
    s32 var_2;
    void *temp_6;

    temp_6 = M2C_FIELD(arg0, void **, 4);
    temp_5 = M2C_FIELD(arg1, s32 *, 0x380);
    temp_7 = 1 << temp_5;
    var_2 = M2C_FIELD(M2C_FIELD(temp_6, void **, 0x7C), s32 *, 0x3A4);
    if (M2C_FIELD(arg1, s32 *, 0x3A4) != var_2) {
        var_2 = M2C_FIELD(arg1, s32 *, 0x38C);
        if (var_2 == 0) {
            var_2 = M2C_FIELD(temp_6, s32 *, 0x274) & temp_7;
            if (var_2 != temp_7) {
                var_2 = func_00185C38((s32) (temp_6 + 0x6F0), temp_5);
                if (var_2 != 0) {
                    var_2 = func_001897E8((s32) (M2C_FIELD(arg0, void **, 4) + 0x150), M2C_FIELD(arg1, s32 *, 0x380), 0);
                }
            }
        }
    }
    return var_2;
}

/* Assembly between the functions: func_0018FC18 (160 bytes), func_0018FCB8 (200 bytes), func_0018FD80 (168 bytes) */

u8 func_0018FE28(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x40);
}

void func_0018FE30(void *arg0) {
    func_00180A00(M2C_FIELD(arg0, s32 *, 4) + 0xB30);
}

s32 func_0018FE50(void) {
    return 1;
}

/* Assembly between the functions: func_0018FE58 (224 bytes), func_0018FF38 (136 bytes) */

s32 func_0018FFC0(void *arg0, s32 *arg1) {
    void *temp_3;

    func_0018E4C0();
    if (*arg1 == 2) {
        temp_3 = M2C_FIELD(arg0, void **, 0x10);
        M2C_FIELD(temp_3, M2C_UNK (**)(void *, M2C_UNK), 0x84)(arg0 + M2C_FIELD(temp_3, s16 *, 0x80), 3);
    }
    return 0;
}
