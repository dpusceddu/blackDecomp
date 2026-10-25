#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018DDE8();
extern s32 func_0018DE48();

s128 func_0018E578(void *arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x7C), s128 *, 0xA0);
}

s32 func_0018E588(void) {
    return 1;
}

void func_0018E590(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 4);
    func_0018DDE8(temp_4 + 0xC94, M2C_FIELD(temp_4, s32 *, 0x754));
}

s32 func_0018E5B8(s32 arg0, s32 arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 4);
    return func_0018DE48((s32) (temp_4 + 0xC94), arg1, M2C_FIELD(temp_4, s32 *, 0x754));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018E680);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018EB78);
