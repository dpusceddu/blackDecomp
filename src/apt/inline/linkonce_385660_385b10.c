#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00252030(s32, s32, s32);
extern s32 func_0024FA38(s32, M2C_UNK);
extern s32 D_0043DEE4;

void func_00385B10(s32 arg0, s32 arg1) {
    func_00252030(func_0024FA38(D_0043DEE4, 0x34), arg0, arg1);
}

s32 func_00385B60(void *arg0) {
    return *M2C_FIELD(arg0, s32 **, 0x30);
}

s32 func_00385B70(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 4);
}

s32 func_00385B80(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30) + 0x1C;
}

s32 func_00385B90(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0x10);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00385BA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00385BF0);
