#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00177C90(s32, s32);
extern s32 func_0017B358(s32);
extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_00181A90(s32, M2C_UNK);
extern s32 func_00193990();
extern s32 func_00199F70();
extern s32 func_00193988();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00199988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00199C40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00199D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00199D90);

void func_00199F08(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_4 != 0) {
        func_00177C90(temp_4, M2C_FIELD(arg0, s32 *, 0) + 0x1F00);
        M2C_FIELD(arg0, s32 *, 0x38) = 0;
    }
}

void func_00199F48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    func_0017B358(M2C_FIELD(arg0, s32 *, 0) + 0x1F60);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00199F70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A3E8);

void func_0019A4F0(void *arg0) {
    func_00193980();
    func_00187FE0(M2C_FIELD(arg0, s32 *, 0) + 0x290, 0);
    M2C_FIELD(arg0, s32 *, 8) = func_00181A90(M2C_FIELD(arg0, s32 *, 0) + 0xEC0, 0x37);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0019A538);

void func_0019A578(void **arg0) {
    if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), u8 *, 0x3B) ^ 1) != 0) {
        func_00193990(arg0, 1);
        return;
    }
    if (func_00199F70(M2C_FIELD(arg0, s32 *, 8)) == 0) {
        func_00193990(arg0, 0);
    }
}


void func_0019A648(void *arg0) {
    func_00193988();
    M2C_FIELD(arg0, s32 *, 8) = 0;
}
