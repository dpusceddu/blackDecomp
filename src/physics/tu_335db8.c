#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00335DB8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335DB8);

void func_00335F00(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x3C);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335F18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_335db8", func_00335F20);

void func_00335FB0(void) {
    func_00335DB8(1, 0xFFFF);
}

void func_00335FD0(void) {
    func_00335DB8(0, 0xFFFF);
}
