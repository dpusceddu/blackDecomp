#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001ADEA8(s32);
extern s32 func_001ADF18();
extern s32 func_001ADF30();

void func_001AE050(void) {

}

void func_001AE058(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + 1);
}

void func_001AE068(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) - 1);
}

void func_001AE078(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x24) = arg1;
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
}

void func_001AE088(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
}

void func_001AE090(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AE098);

void func_001AE0A8(void *arg0) {
    func_001ADEA8(arg0 + 0xC);
}

void func_001AE0C8(s32 arg0) {
    func_001ADF18(arg0 + 0xC);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AE0E8);

s32 func_001AE0F0(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0xC;
    func_001ADF18(temp_16, arg1);
    return func_001ADF30(temp_16, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0A20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0D88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0E00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B0F70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2B68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2C40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2CD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B2D70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6188);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B61C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B6328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BEBA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1C48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1CD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C79D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C7D08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C7DB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C8108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C81F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C8420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C8478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C8560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CAB20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CADD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CB3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CC3A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CCAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CCF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CD360);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CD650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CD8D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CDA28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CDAE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CDB98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CDD98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CE1B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CE3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CE780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CE9E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CEB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CEDA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CEF38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CF1D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CF340);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CF530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CF6C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CF8C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFA58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFB00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFB50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001CFE50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD748);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD7B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001DD7C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E45A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E8B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E9C68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED2C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED2E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED4A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED4F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED578);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED830);
