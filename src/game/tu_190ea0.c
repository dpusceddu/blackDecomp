#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018E458();
extern s32 func_001911A8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00190EA0);

void func_00191010(void *arg0) {
    void *temp_3;
    void *temp_4;

    func_0018E458();
    temp_3 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(arg0, s8 *, 0x15) = 0;
    if ((M2C_FIELD(temp_3, u8 *, 0x28) == 0) && (M2C_FIELD(temp_3, s8 *, 0x29) < 0)) {
        func_001911A8(arg0);
    }
    temp_4 = M2C_FIELD(arg0, void **, 4);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(M2C_FIELD(temp_4, void **, 0x7C), s128 *, 0xA0);
    M2C_FIELD(temp_4, s8 *, 0xD24) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191070);

u8 func_00191110(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x14);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00191158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001911A8);

s32 func_00191270(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0), s8 *, 0x29) == M2C_FIELD(M2C_FIELD(arg0, void **, 4), s32 *, 0x1EF4);
}
