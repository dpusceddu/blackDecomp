/* Translation unit tu_25b5d0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_0025C4C8();
extern s32 func_00136F10();
extern s32 func_0025C798();
extern s32 func_0025CA10();
extern s32 func_0025DA20(s32);
extern s32 func_0025C910();
extern s32 func_0032E1B0(s32, void *);
extern s32 func_00100290(s32, s32, M2C_UNK);
extern s32 func_00107B78();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107D20();
extern s32 func_0014C330(s32);
extern s32 func_0025DD38();
extern s32 func_00135570();
extern void * D_0040F4D0;
extern s32 func_0025E2D0();
extern s32 func_0032B6E0();
extern s32 func_002611D0();
extern s32 func_0032CDE0(s32, s32);
extern s32 func_00264130(M2C_UNK, M2C_UNK);

void func_0025C020(void) {

}

s32 func_0025C028(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B44) = 0x37;
    return 1;
}

/* Assembly between the functions: func_0025C040 (320 bytes), func_0025C180 (144 bytes), func_0025C210 (184 bytes) */

s32 func_0025C2C8(s32 arg0, s32 arg1) {
    s32 temp_5;
    s32 temp_v0;

    temp_5 = M2C_FIELD(arg1, s32 *, 0x350);
    if (temp_5 != 0) {
        func_0025C4C8(arg0, temp_5);
    }
    func_00136F10(arg1, 1);
    temp_v0 = func_0025C798(arg0, M2C_FIELD(arg1, s32 *, 0xB4));
    M2C_FIELD(arg1, s32 *, 0xB4) = 0;
    return temp_v0;
}

/* Assembly between the functions: func_0025C320 (152 bytes), func_0025C3B8 (272 bytes), func_0025C4C8 (144 bytes), func_0025C558 (312 bytes) */

void func_0025C690(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg1, s32 *, 0xB4);
    if (temp_5 != 0) {
        func_0025CA10(arg0, temp_5);
    }
}

/* Assembly between the functions: func_0025C6B8 (160 bytes), func_0025C758 (64 bytes), func_0025C798 (216 bytes), func_0025C870 (160 bytes), func_0025C910 (256 bytes), func_0025CA10 (216 bytes) */

void func_0025CAE8(s32 arg0, s32 arg1) {
    func_0025DA20(arg1);
}

/* Assembly between the functions: func_0025CB08 (160 bytes), func_0025CBA8 (160 bytes), func_0025CC48 (88 bytes), func_0025CCA0 (56 bytes) */

void * func_0025CCD8(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 * 0x10) + 0x28);
}

/* Assembly between the functions: func_0025CCE8 (184 bytes) */

s32 func_0025CDA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    temp_2 = func_0025C910(arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B04) = temp_2;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return ~M2C_FIELD(arg0, s32 *, 0x8B04) != 0;
}

/* Assembly between the functions: func_0025CDF0 (56 bytes) */

void func_0025CE28(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B04) = -1;
}

void func_0025CE40(s32 *arg0, void *arg1) {
    if (func_0032E1B0(*arg0, M2C_FIELD(arg1, void **, 0x34)) != 0) {
        func_00100290(*arg0, M2C_FIELD(M2C_FIELD(arg1, void **, 0x34), s32 *, 0xC), 1);
    }
}

void func_0025CE90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s8 *, 0x3D) = 0;
    M2C_FIELD(arg0, s8 *, 0x3E) = 0;
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
    M2C_FIELD(arg0, s16 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 1;
    func_00107B78(&D_0040F0F0, 0xB, 0x10, 0);
    M2C_FIELD(arg0, s32 *, 0x34) = func_00107D20(0x90);
}

/* Assembly between the functions: func_0025CEF8 (416 bytes), func_0025D098 (120 bytes), func_0025D110 (304 bytes), func_0025D240 (720 bytes), func_0025D510 (816 bytes), func_0025D840 (32 bytes), func_0025D860 (128 bytes), func_0025D8E0 (48 bytes), func_0025D910 (128 bytes), func_0025D990 (48 bytes), func_0025D9C0 (80 bytes) */

s32 func_0025DA10(void *arg0) {
    return ((u16) M2C_FIELD(arg0, u16 *, 0x40) >> 9) & 1;
}

/* Assembly between the functions: func_0025DA20 (160 bytes) */

void func_0025DAC0(void *arg0) {
    func_0014C330(M2C_FIELD(arg0, s32 *, 0x30));
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
}

/* Assembly between the functions: func_0025DAF0 (48 bytes), func_0025DB20 (136 bytes), func_0025DBA8 (216 bytes) */

void func_0025DC80(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), void **, 0xC), void **, 0x58), s32 *, 0xAC) = 0;
}

/* Assembly between the functions: func_0025DC98 (112 bytes), func_0025DD08 (48 bytes), func_0025DD38 (1432 bytes), func_0025E2D0 (10568 bytes) */

void func_00260C18(void *arg0)
{
  int new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 4) = 0;
 do { M2C_FIELD(arg0, s32 *, 0x14) = 0; func_0025DD38(); func_00107B78(&D_0040F0F0, 0xB, 0x10, 0); M2C_FIELD(arg0, s32 *, 0xC) = func_00107D20(0x750); } while (0);
  new_var = 0x10;
  *((s8 *) (((s8 *) arg0) + new_var)) = 0;
  arg0++;
  arg0--;
}

s32 func_00260C70(void *arg0, s32 arg1) {
    s32 temp_2;

    M2C_FIELD(arg0, s32 *, 0) = arg1;
    temp_2 = func_00135570(arg1);
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
    if (M2C_FIELD(arg0, u8 *, 0x10) == 0) {
        M2C_FIELD(arg0, u8 *, 0x10) = 1U;
        func_0025E2D0(arg0, temp_2);
    }
    func_0032B6E0(M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s32 *, 0x18) = 7;
    func_002611D0(arg0);
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    return 1;
}

/* Assembly between the functions: func_00260CF8 (648 bytes) */

void func_00260F80(void) {
    func_002611C8();
}

s32 func_00260FA0(s32 *arg0) {
    *arg0 = 0;
    return 1;
}

/* Assembly between the functions: func_00260FB0 (536 bytes) */

void func_002611C8(void) {

}

/* Assembly between the functions: func_002611D0 (2688 bytes), func_00261C50 (2584 bytes), func_00262668 (3152 bytes), func_002632B8 (168 bytes) */

s32 func_00263360(void *arg0, s32 arg1) {
    func_0032CDE0(arg1, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}

void func_00263388(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}

/* Assembly between the functions: func_00263390 (64 bytes) */

s32 func_002633D0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xC), s32 *, 0x58);
}

/* Assembly between the functions: func_002633E0 (376 bytes), func_00263558 (216 bytes), func_00263630 (360 bytes), func_00263798 (280 bytes), func_002638B0 (88 bytes), func_00263908 (152 bytes), func_002639A0 (464 bytes), func_00263B70 (232 bytes), func_00263C58 (552 bytes), func_00263E80 (392 bytes), func_00264008 (16 bytes), func_00264018 (280 bytes) ... */

void func_00265C18(void) {
    func_00264130(1, 0xFFFF);
}
