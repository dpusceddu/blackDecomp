#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00274E40();
extern s32 func_0016EA10();
extern void func_0016EC78();
extern s32 func_00107B08();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107AB8();
extern void * func_00107D20();
extern s32 func_00274E68();
extern s32 func_0016EF00();
extern s32 func_0016F3D0();
extern s32 func_002D15A0();
extern s32 func_002D8448();
extern s32 func_002DA1C8();
extern s32 func_002F0DA8();
extern s32 func_003054F8();
extern s32 func_0030D130();
extern s32 func_0016F9A8();
extern s32 func_0016EA80();
extern void func_0016FB48();
extern s32 D_003C9ED4;
extern void * D_0040F4D4;

void func_0016EB80(void *arg0) {
    s32 temp_18;
    void *temp_19;

    temp_18 = arg0 + 0x50;
    M2C_FIELD(arg0, s32 *, 0x6C) = 0;
    M2C_FIELD(arg0, s8 *, 0x4C) = 0;
    M2C_FIELD(arg0, s8 *, 0x4D) = 0;
    func_00274E40(temp_18);
    func_0016EA10(arg0 + 0x7C, 0x10);
    func_0016EA10(arg0 + 0x88, 1);
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    func_0016EC78(arg0);
    func_0016ED80(arg0);
    func_00107B08(&D_0040F0F0, 0, 0);
    func_00107AB8(&D_0040F0F0, 2, 0);
    temp_19 = func_00107D20(0x40000);
    func_00107B08(&D_0040F0F0, 2, 0);
    func_00107AB8(&D_0040F0F0, 0, 0);
    func_00274E40(temp_18);
    func_00274E68(temp_18, temp_19, 0x40000);
    func_0016EF00(arg0);
    func_0016F3D0(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016EC78);

void func_0016ED80(void) {
    if ((func_002D15A0() != 0) && (func_002D8448() != 0) && (func_002DA1C8() != 0) && (func_002F0DA8() != 0) && (func_003054F8() != 0)) {
        func_0030D130();
    }
}

s32 func_0016EDF0(void *arg0) {
    func_0016F9A8();
    func_0016EA80(arg0 + 0x7C);
    func_0016EA80(arg0 + 0x88);
    func_0016FB48();
    M2C_FIELD(arg0, s8 *, 0x4C) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016EE38);

s32 func_0016EE70(void *arg0) {
    if (D_003C9ED4 != 0) {
        M2C_FIELD(arg0, s32 *, 0x6C) = 0;
    }
    M2C_FIELD(arg0, s8 *, 0x4C) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016EE90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016EE98);

s32 func_0016EEE8(void) {
    return 0;
}

void func_0016EEF0(void) {

}

s32 func_0016EEF8(void) {
    return 8;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016EF00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016F3D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016F9A8);

s32 func_0016FA38(void) {
    return M2C_FIELD(D_0040F4D4, s32 *, 0x22B98);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016FA50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016FAB0);

s32 func_0016FB18(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        goto block_3;
    }
    if (arg1 != 2) {
        goto block_4;
    }
    return arg0 + 0x88;
block_3:
    return arg0 + 0x7C;
block_4:
    return 0;
}
