#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_0017B358();
extern s32 func_00173690();
extern s32 func_00180AA0(void *, s128, M2C_UNK, f32);

void func_00180AE0(void *arg0, s128 arg1) {
    M2C_FIELD(arg0, s8 *, 0x70) = 1;
    M2C_FIELD(arg0, s128 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x74) = 2;
    func_0017B358(arg0 + 0x110);
    func_00173690(arg0 + 0x148);
    M2C_FIELD(arg0, s8 *, 0x14D) = 1;
    M2C_FIELD(arg0, s8 *, 0x14F) = 0;
}

void func_00180B38(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = fparg0;
}

void func_00180B40(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x140);
    func_00180AA0(temp_2 + 0xB30, M2C_FIELD(M2C_FIELD(temp_2, void **, 0x7C), s128 *, 0xA0), 2, M2C_FIELD(temp_2, f32 *, 0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180ae0", func_00180B70);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1804f8_180ae0", func_00180BC0);
