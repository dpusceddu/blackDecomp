#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00345F28();
extern s32 D_003BCEB0;
extern s32 func_00347C70();
extern s32 func_003438D8();

s32 func_0014C640(void *arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    void *temp_5;

    M2C_FIELD(arg0, s8 *, 0x44) = 0;
    temp_5 = M2C_FIELD(arg0, void **, 0x40);
    M2C_FIELD(arg0, s8 *, 0x45) = 0;
    M2C_FIELD(arg0, s8 *, 0x46) = 0;
    M2C_FIELD(arg0, s8 *, 0x47) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    if (temp_5 != NULL) {
        if (func_00345F28(D_003BCEB0, temp_5, sp) != 0) {
            func_00347C70(M2C_FIELD(arg0, void **, 0x40), *(s32 *)(sp + 0));
        }
        func_003438D8(M2C_FIELD(arg0, void **, 0x40));
    }
    M2C_FIELD(arg0, s8 *, 0x49) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014C6B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0014C7C8);
