#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK * D_003EB798;
extern s32 (*D_003C87E0)();
extern M2C_UNK * D_003E0040;
extern u32 func_002ECAA8();
extern void * D_003C9ED4;
extern f32 D_003C958C;
extern f32 D_003C9590;
extern s32 func_002E4C60();
extern u32 D_003C9594;
extern s32 func_002E91C0();

void func_002E9328(void *arg0, s32 arg1) {
    void *temp_4;
    void *temp_4_2;

    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003EB798;
    temp_4 = M2C_FIELD(arg0, void **, 4);
    if (temp_4 != NULL) {
        D_003C87E0(temp_4);
    }
    temp_4_2 = M2C_FIELD(arg0, void **, 8);
    if (temp_4_2 != NULL) {
        D_003C87E0(temp_4_2);
    }
    M2C_FIELD(arg0, M2C_UNK ***, 0) = &D_003E0040;
    if (arg1 & 1) {
        D_003C87E0(arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E93B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9438);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E94B8);

void func_002E9538(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = fparg0;
}

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "kynapse/layouts/Recovered_ParameterTables.h"
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void func_002E9540(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_28), f32 *, 0) = fparg0;
    }
}

void func_002E9570(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_20), f32 *, 0) = fparg0;
    }
}

void func_002E95A0(Recovered_ParameterTables *arg0, s32 arg1, s32 arg2) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_8)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_24), s32 *, 0) = arg2;
    }
}

void func_002E95D0(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_4)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_2C), f32 *, 0) = fparg0;
    }
}

void func_002E9600(Recovered_ParameterTables *arg0, s32 arg1, f32 fparg0) {
    if ((arg1 >= 0) && ((u32) arg1 < (u32) arg0->field_C)) {
        M2C_FIELD(((arg1 * 4) + arg0->field_30), f32 *, 0) = fparg0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9630);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E96F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E97B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9868);

void func_002E98F0(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_6;

    temp_6 = func_002ECAA8(arg2);
    if ((arg1 >= 0) && ((u32) arg1 < (u32) M2C_FIELD(arg0, u32 *, 4)) && (temp_6 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x18))) {
        M2C_FIELD(((arg1 * 4) + M2C_FIELD(((temp_6 * 0xC) + M2C_FIELD(arg0, s32 *, 0x38)), s32 *, 8)), f32 *, 0) = D_003C958C;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9A58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9B30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9BC8);

void func_002E9CB0(void) {
    D_003C9590 = D_003C958C;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E9CC8);

void func_002E9D10(s32 arg0, void *arg1) {
    u32 temp_2;

    temp_2 = func_002E4C60(arg1);
    if (temp_2 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10)) {
        D_003C9594 = temp_2;
    }
}

void func_002E9D50(s32 arg0, f32 fparg0) {
    if ((arg0 >= 0) && ((u32) arg0 < (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10))) {
        M2C_FIELD(((arg0 * 0x18) + M2C_FIELD(func_002E91C0(), s32 *, 0x34)), f32 *, 0xC) = fparg0;
    }
}

f32 func_002E9DB8(s32 arg0) {
    if ((arg0 < 0) || ((u32) arg0 >= (u32) M2C_FIELD(D_003C9ED4, u32 *, 0x10))) {
        return 0.0f;
    }
    return M2C_FIELD(((arg0 * 0x18) + M2C_FIELD(func_002E91C0(), s32 *, 0x34)), f32 *, 0xC);
}
