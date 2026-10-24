#include "include_asm.h"
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
extern s32 * func_0032E320();
extern M2C_UNK D_0043F3F0;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025B5D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025B6D0);

void func_0025C020(void) {

}

s32 func_0025C028(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B44) = 0x37;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C040);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C210);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C4C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C558);

void func_0025C690(s32 arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg1, s32 *, 0xB4);
    if (temp_5 != 0) {
        func_0025CA10(arg0, temp_5);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C758);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C870);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025C910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CA10);

void func_0025CAE8(s32 arg0, s32 arg1) {
    func_0025DA20(arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CB08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CBA8);

s32 func_0025CC48(s32 *arg0, s32 arg1) {
    return M2C_FIELD(((((s32) ((arg1 - *func_0032E320(*arg0)) * 0xBA2E8BA3) >> 4) * 4) + ((s32) &D_0043F3F0)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CCA0);

void * func_0025CCD8(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 * 0x10) + 0x28);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CCE8);

s32 func_0025CDA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    temp_2 = func_0025C910(arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B04) = temp_2;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return ~M2C_FIELD(arg0, s32 *, 0x8B04) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CDF0);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025CEF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D098);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D510);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D860);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D8E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D910);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025D9C0);

s32 func_0025DA10(void *arg0) {
    return ((u16) M2C_FIELD(arg0, u16 *, 0x40) >> 9) & 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DA20);

void func_0025DAC0(void *arg0) {
    func_0014C330(M2C_FIELD(arg0, s32 *, 0x30));
    M2C_FIELD(arg0, s8 *, 0x3F) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DAF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DBA8);

void func_0025DC80(void *arg0) {
    M2C_FIELD(M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x34), void **, 0xC), void **, 0x58), s32 *, 0xAC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DC98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DD08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025DD38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0025E2D0);

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00260CF8);

void func_00260F80(void) {
    func_002611C8();
}

s32 func_00260FA0(s32 *arg0) {
    *arg0 = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00260FB0);

void func_002611C8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002611D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00261C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00262668);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002632B8);

s32 func_00263360(void *arg0, s32 arg1) {
    func_0032CDE0(arg1, M2C_FIELD(arg0, s32 *, 8));
    return 1;
}

void func_00263388(void *arg0) {
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263390);

s32 func_002633D0(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xC), s32 *, 0x58);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002633E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263798);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002638B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002639A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00263E80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00264008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00264018);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00264130);

void func_00265C18(void) {
    func_00264130(1, 0xFFFF);
}
