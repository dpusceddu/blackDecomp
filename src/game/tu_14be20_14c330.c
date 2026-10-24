#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00175A00(s32, void *, M2C_UNK);
extern s32 D_0040F4D4;
extern s32 func_0017BD10(s32, s32);
extern s32 func_00175AB8(s32, s32, M2C_UNK);

void func_0014C330(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x10);
    if (M2C_FIELD(temp_3, s32 (**)(void *), 0xD4)(arg0 + M2C_FIELD(temp_3, s16 *, 0xD0)) != 0) {
        func_00175A00(D_0040F4D4 + 0xA48, arg0, 0);
    }
}

void func_0014C380(s32 arg0) {
    func_0017BD10(D_0040F4D4 + 0xCD4, arg0);
    func_00175AB8(D_0040F4D4 + 0xA48, arg0, 0);
}

s32 func_0014C3D0(void *arg0) {
    return (u32) (M2C_FIELD(arg0, s32 *, 0xC4) - 3) < 2U;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014C3E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014C488);
