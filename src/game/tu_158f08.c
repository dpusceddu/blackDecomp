/* Translation unit tu_158f08 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00382348();
extern M2C_UNK D_00414D70;
extern s32 func_001E1A70(s32);
extern s32 func_001E2C38(s32, s32);
extern void * D_0040F510;
extern s32 func_001550F0();

void func_00158F08(void *arg0)
{
  func_00382348(&D_00414D70, 0x02B9D6F8);
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
 do { M2C_FIELD(arg0, s16 *, 0x18) = 0; } while (0);
  M2C_FIELD(arg0, s32 *, 0x14) = 0;
  M2C_FIELD(arg0, s8 *, 0x20) = 0;
}

/* Assembly between the functions: func_00158F50 (464 bytes) */

void func_00159120(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_4 != 0) {
        func_001E1A70(temp_4);
    }
}

s32 func_00159148(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x10);
    if (temp_5 != 0) {
        func_001E2C38(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x14), temp_5);
        M2C_FIELD(arg0, s32 *, 0x10) = 0;
    }
    M2C_FIELD(arg0, s32 *, 4) = 0;
    return 1;
}

/* Assembly between the functions: func_00159198 (1952 bytes), func_00159938 (432 bytes), func_00159AE8 (1456 bytes), func_0015A098 (872 bytes), func_0015A400 (1072 bytes), func_0015A830 (160 bytes) */

s32 func_0015A8D0(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 4);
    if (M2C_FIELD(M2C_FIELD(temp_5, void **, 0xF0), s32 *, 0xC4) == 2) {
        if (func_001550F0(M2C_FIELD(temp_5, s32 *, 0xFC), M2C_FIELD(M2C_FIELD(arg0, void **, 8), s32 *, 0x64)) != 0) {
            M2C_FIELD(arg0, u16 *, 0x18) = (u16) (M2C_FIELD(arg0, u16 *, 0x18) + 1);
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}

s32 func_0015A938(void *arg0) {
    return M2C_FIELD(arg0, s16 *, 0x18) < 1;
}

s32 func_0015A948(void *arg0) {
    if ((M2C_FIELD(arg0, s8 *, 0x20) == 2) || (M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), f32 *, 0x20) >= 0.15f)) {
        return 1;
    }
    return 0;
}

/* Assembly between the functions: func_0015A990 (208 bytes), func_0015AA60 (840 bytes), func_0015ADA8 (640 bytes), func_0015B028 (240 bytes), func_0015B118 (584 bytes), func_0015B360 (1424 bytes) */

void func_0015B8F0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x200) = 0;
}
