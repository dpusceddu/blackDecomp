/* Translation unit tu_1dd838 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_001DFC78();
extern s32 func_001E0FE8(void *);
extern void func_001E10C0(void *arg0);
extern s32 func_001DEEB8();
extern s32 func_001E0D28();
extern s32 func_001E0F28(void *);
extern s32 func_001E0E70(void *);
extern s32 func_001E0A30(void *);
extern f32 func_001ED820(s32);
extern void * D_0040F510;
extern s8 func_00281120();
extern f32 D_003BD390;

void func_001E0440(void *arg0) {
    func_001DFC78();
    func_001E0FE8(arg0);
    func_001E10C0(arg0);
    func_001E1068(arg0);
}

/* Assembly between the functions: func_001E0480 (208 bytes), func_001E0550 (416 bytes), func_001E06F0 (120 bytes), func_001E0768 (136 bytes), func_001E07F0 (48 bytes), func_001E0820 (264 bytes), func_001E0928 (8 bytes), func_001E0930 (120 bytes), func_001E09A8 (136 bytes), func_001E0A30 (760 bytes), func_001E0D28 (328 bytes), func_001E0E70 (184 bytes) ... */

void func_001E1068(void *arg0) {
    u8 sp[8];
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_3 != -1) {
        if (temp_3 == 0) {
            func_001DEEB8(sp, M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, u8 *, 0x24), 0);
        }
        M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - 1);
    }
}

void func_001E10C0(void *arg0) {
    func_001E0D28();
    func_001E0F28(arg0);
    func_001E0E70(arg0);
    func_001E0A30(arg0);
}

/* Assembly between the functions: func_001E1100 (248 bytes), func_001E11F8 (72 bytes) */

s32 func_001E1240(s32 arg0, void *arg1) {
    return M2C_FIELD(arg1, s32 *, 0x30);
}

/* Assembly between the functions: func_001E1248 (1096 bytes) */

void func_001E1690(void *arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        M2C_FIELD(arg0, f32 *, 0x242C) = func_001ED820(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x2C));
        return;
    }
    M2C_FIELD(arg0, f32 *, 0x242C) = 0.0f;
}

void func_001E16E0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x18) = func_00281120();
}

f32 func_001E1708(s32 arg0, s32 arg1) {
    return (&D_003BD390)[arg1];
}
