/* Translation unit physics/tu_32bc70 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_0032BC70();
extern s32 func_0032D248();
extern s32 func_0032D358();
extern s32 func_0032D590();
extern s32 func_0032D7C0();
extern s32 func_0032D990();
extern s32 func_0032DCE8();
extern s32 func_0032FAF8();
extern s32 func_0037C4E0();
extern s32 func_0032DF00(M2C_UNK, M2C_UNK);

void * func_0032E0E0(void *arg0) {
    u8 sp[24] __attribute__((aligned(16)));
    func_0032BC70(sp);
    M2C_FIELD(arg0, s32 *, 4) = 0x80;
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 20);
    return arg0;
}

/* Assembly between the functions: func_0032E120 (144 bytes) */

s32 func_0032E1B0(void *arg0, u32 *arg1) {
    s32 var_8;
    u32 temp_6;

    var_8 = 0;
    if (arg1 != NULL) {
        temp_6 = *arg1;
        if ((temp_6 < (u32) M2C_FIELD(arg0, u32 *, 0x28)) && (M2C_FIELD(((temp_6 * 4) + M2C_FIELD(arg0, s32 *, 0x44)), s32 *, 0) == arg1)) {
            var_8 = ((u32) M2C_FIELD((((temp_6 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0x60)), u32 *, 0) >> (temp_6 & 0x1F)) & 1;
        }
    }
    return var_8;
}

/* Assembly between the functions: func_0032E208 (16 bytes), func_0032E218 (136 bytes) */

void func_0032E2A0(void *arg0, void *arg1, s32 arg2) {
    s32 *temp_3;
    s32 *temp_3_2;
    u32 temp_2;
    u32 temp_2_2;

    if (arg2 != 0) {
        temp_2 = M2C_FIELD(arg1, u32 *, 0x60);
        temp_3 = ((temp_2 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0xA8);
        *temp_3 |= 1 << (temp_2 & 0x1F);
        return;
    }
    temp_2_2 = M2C_FIELD(arg1, u32 *, 0x60);
    temp_3_2 = ((temp_2_2 >> 5) * 4) + M2C_FIELD(arg0, s32 *, 0xA8);
    *temp_3_2 &= ~(1 << (temp_2_2 & 0x1F));
}

/* Assembly between the functions: func_0032E310 (16 bytes) */

s32 func_0032E320(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x18);
}

void func_0032E328(void *arg0) {
    func_0032D248();
    func_0032D358(arg0);
    func_0032D590(arg0);
    func_0032D7C0(arg0);
    func_0032D990(arg0, M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0x20));
    func_0032DCE8(arg0);
    func_0032FAF8(M2C_FIELD(arg0, void **, 0x1C));
    func_0037C4E0(M2C_FIELD(arg0, s32 *, 0x18));
}

void func_0032E390(void) {
    func_0032DF00(1, 0xFFFF);
}

void func_0032E3B0(void) {
    func_0032DF00(0, 0xFFFF);
}
