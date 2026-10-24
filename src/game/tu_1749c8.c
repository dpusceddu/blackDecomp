#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00165AE0();
extern void * func_00135550();
extern s32 func_0018D3A0();
extern s32 func_00107D20();
extern s32 func_001749E8();
extern s32 func_00174C08();
extern s32 func_00183238(s32);
extern s32 func_00173F18();
extern s32 func_00183688();
extern s32 func_001736B8();
extern s32 func_00173EE0();

void func_001749C8(void) {
    func_00165AE0();
}

s32 func_001749E8(void *arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4) {
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, s64 *, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 0x18) = arg4;
    M2C_FIELD(arg0, s16 *, 0x1C) = 0;
    return 1;
}

void func_00174A00(s32 arg0, s64 *arg1) {
    s32 temp_17;

    if (arg1 != NULL) {
        temp_17 = M2C_FIELD(arg1, s32 *, 0xC4);
        if ((temp_17 == 1) && (func_00135550(arg1) != NULL) && (M2C_FIELD(func_00135550(arg1), s32 *, 0x80) == temp_17)) {
            func_0018D3A0(func_00135550(arg1) + 0xD10, arg0);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174A80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174AD0);

u8 func_00174AD8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 8) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s32 *, 0x14)), u8 *, 4);
}

s32 func_00174AF0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(temp_2, s32 *, 0xC) + (M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_2, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 0x10);
}

f32 func_00174B20(void *arg0, s32 arg1, s32 arg2) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(((M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_3, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 4) + M2C_FIELD(temp_3, s32 *, 0x18)), f32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174BA0);

void func_00174BE8(s32 arg0, s32 arg1) {
    func_00107D20(arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174C08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174CD8);

s32 func_00174D48(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 2, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x44) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_00174DC8(void) {
    return 1;
}

void func_00174DD0(void) {
    func_001749C8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174DF0);

s32 func_00174ED8(void) {
    return 1;
}

void func_00174EE0(void *arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(M2C_FIELD(arg0, void **, 0x90), arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174F20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174FF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00175090);

s32 func_001750E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 3, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    func_00183688(arg0 + 0x28, arg1, arg2);
    func_001736B8(arg0 + 0x50, 7);
    return 1;
}

s32 func_00175158(void) {
    return 1;
}

void func_00175160(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(arg0 + 0x50, arg1);
}

void func_001751A0(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173EE0(arg0 + 0x50, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001751E0);

s32 func_00175250(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 4, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x27) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_001752D0(void) {
    return 1;
}

void func_001752D8(void) {
    func_001749C8();
}

s32 func_001752F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 5, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    return 1;
}

s32 func_00175340(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00175348);

s32 func_001753B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 6, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x33) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}

s32 func_00175438(void) {
    return 1;
}

void func_00175440(void) {
    func_001749C8();
}

s32 func_00175460(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 7, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x28) = arg2;
    return 1;
}

s32 func_001754A8(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001754B0);

s32 func_00175520(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    u8 temp_3;

    func_001749E8(arg0, 8, arg1, arg2, arg3);
    temp_5 = M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    if (temp_5 != 0) {
        temp_3 = M2C_FIELD(((M2C_FIELD(arg2, u8 *, 0x2E) * 8) + M2C_FIELD(arg3, s32 *, 0x14)), u8 *, 4);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) temp_3;
        func_00174C08(arg0, temp_5, (s32) temp_3);
    }
    return 1;
}
