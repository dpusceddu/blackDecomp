/* Translation unit tu_16a720 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00169EB8();
extern s32 func_00169EF8();
extern s32 func_00107D20();
extern s32 func_00160E70();
extern s32 func_00160ED8();
extern s32 func_001D4268();
extern s32 func_001C31F8();
extern s32 func_001C3228(f32);
extern s32 func_001C32B8();

s32 func_0016A778(void) {
    func_00169EB8();
    return 1;
}

/* Assembly between the functions: func_0016A798 (8 bytes) */

void func_0016A7A0(void) {
    func_00169EF8();
}

/* Assembly between the functions: func_0016A7C0 (696 bytes), func_0016AA78 (160 bytes) */

s32 func_0016AB18(void) {
    func_0016A778();
    return 1;
}

/* Assembly between the functions: func_0016AB38 (8 bytes) */

void func_0016AB40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x11D) = 0;
    M2C_FIELD(arg0, u8 *, 0x11C) = (u8) (M2C_FIELD(arg0, u8 *, 0x11C) ^ 1);
}

s32 func_0016AB58(s32 arg0, s32 arg1)
{
  s32 temp_2;
  temp_2 = func_00107D20(arg1 * 0xC);
  M2C_FIELD(arg0, s16 *, 4) = (s16) arg1;
  temp_2++;
  temp_2--;
  M2C_FIELD(arg0, s32 *, 0) = temp_2;
 do { M2C_FIELD(arg0, s16 *, 6) = 0; } while (0);
  return temp_2;
}

void func_0016ABA0(void *arg0) {
    M2C_FIELD(arg0, s16 *, 6) = 0;
}

void func_0016ABA8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 > 0) {
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) = arg1;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 4) = arg2;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 6) * 0xC) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 8) = arg3;
        M2C_FIELD(arg0, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 6) + 1);
    }
}

/* Assembly between the functions: func_0016AC08 (144 bytes) */

void func_0016AC98(void) {
    func_00160E70();
}

/* Assembly between the functions: func_0016ACB8 (96 bytes) */

s32 func_0016AD18(void) {
    func_00160ED8();
    return 1;
}

/* Assembly between the functions: func_0016AD38 (8 bytes), func_0016AD40 (160 bytes) */

void func_0016ADE0(void) {
    func_0016B670();
    func_001D4268();
}

/* Assembly between the functions: func_0016AE08 (424 bytes), func_0016AFB0 (360 bytes), func_0016B118 (992 bytes), func_0016B4F8 (152 bytes), func_0016B590 (80 bytes), func_0016B5E0 (80 bytes), func_0016B630 (56 bytes), func_0016B668 (8 bytes) */

void func_0016B670(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 1;
    func_001C31F8();
}

/* Assembly between the functions: func_0016B690 (128 bytes) */

void func_0016B710(void *arg0) {
    func_001C3228(M2C_FIELD(arg0, f32 *, 0x44));
}

/* Assembly between the functions: func_0016B730 (40 bytes) */

void func_0016B758(void) {
    func_001C32B8();
}
