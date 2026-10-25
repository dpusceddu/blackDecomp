#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00188238();
extern s32 func_00188780(s32);
extern s32 func_001884E0(s32);
extern s32 func_00188358(s32);
extern s32 func_001580E0();
extern s32 * func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00162580();
extern void * func_0015D2A8();
extern s32 D_0040F4E0;
extern void * D_0040F4D0;
extern s32 func_00158088();
extern s32 func_00173640(void **, f32);
extern s32 func_00173610();

void func_00187F90(s32 arg0) {
    func_00188238();
    func_00188780(arg0);
    func_001884E0(arg0);
    func_001886E0(arg0);
    func_00188358(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00187FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00187FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_001880D8);

void func_00188148(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 2) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00188150);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00188238);

u8 func_00188350(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x24);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00188358);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_001884E0);

void func_001886E0(void *arg0) {
    s32 temp_18;
    s32 temp_5;

    temp_18 = M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), void **, 0x7C), s32 *, 0x2A4);
    if (func_001580E0(temp_18) < M2C_FIELD(arg0, s32 *, 0x20)) {
        temp_5 = M2C_FIELD(arg0, s32 *, 8);
        if ((temp_5 != -1) && (M2C_FIELD(func_00179258(D_0040F4D4 + 0xFA8, temp_5), s32 *, 4) == 1)) {
            func_00162580(M2C_FIELD(func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(arg0, s32 *, 8)), s32 *, 8));
        }
        M2C_FIELD(arg0, s32 *, 0x20) = func_001580E0(temp_18);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_187f90", func_00188780);

void func_00188940(void *arg0, s32 arg1) {
    s8 *temp_17;
    void *temp_18;
    void *temp_3;

    if (arg1 != 0) {
        temp_3 = M2C_FIELD(arg0, void **, 0x3AC);
        temp_17 = M2C_FIELD(M2C_FIELD(temp_3, void **, 0x7C), s8 **, 0x2A4);
        if (temp_17 == NULL) {
            M2C_FIELD(temp_3, s8 *, 0x6CD) = 0;
            return;
        }
        temp_18 = func_0015D2A8(D_0040F4E0, *temp_17);
        M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) + M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
        if (M2C_FIELD(temp_18, u8 *, 0x10) == 0) {
            if (func_00158088(temp_17) != 0) {
                M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 0;
                func_00173640(arg0 + 0x10, M2C_FIELD(temp_18, f32 *, 0xC));
                return;
            }
            if (func_00173610(arg0 + 0x10) != 0) {
                goto block_7;
            }
        } else {
block_7:
            M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 1;
        }
    } else {
        M2C_FIELD(M2C_FIELD(arg0, void **, 0x3AC), s8 *, 0x6CD) = 0;
    }
}
