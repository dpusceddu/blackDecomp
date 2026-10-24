#include "include_asm.h"
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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A798);

void func_0016A7A0(void) {
    func_00169EF8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AA78);

s32 func_0016AB18(void) {
    func_0016A778();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AB38);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AC08);

void func_0016AC98(void) {
    func_00160E70();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016ACB8);

s32 func_0016AD18(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AD38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AD40);

void func_0016ADE0(void) {
    func_0016B670();
    func_001D4268();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AE08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016AFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B4F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B590);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B668);

void func_0016B670(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 1;
    func_001C31F8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B690);

void func_0016B710(void *arg0) {
    func_001C3228(M2C_FIELD(arg0, f32 *, 0x44));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B730);

void func_0016B758(void) {
    func_001C32B8();
}
