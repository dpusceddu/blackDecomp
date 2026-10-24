#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0038F000();
extern M2C_UNK D_00451540;
extern M2C_UNK func_002EC918;
extern M2C_UNK D_003EBB30;
extern M2C_UNK * D_00451650;
extern M2C_UNK D_003EBB48;
extern s32 D_003E8420;

void func_002EC8A0(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_0038F000(&D_00451540, "CTeam", &func_002EC918, 0, 0, 0);
            M2C_FIELD(&D_00451540, M2C_UNK **, 0x110) = &D_003EBB30;
            return;
        }
        D_00451650 = &D_003EBB48;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EC918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002EC9D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002ECAA8);

s32 func_002ECAF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038F000(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EBB30;
    return arg0;
}

void func_002ECB30(void) {
    D_003E8420 = 0;
}

void func_002ECB40(void) {
    func_002EC8A0(1, 0xFFFF);
}

void func_002ECB60(void) {
    func_002EC8A0(0, 0xFFFF);
}
