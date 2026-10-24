#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00160E70();
extern s32 func_00160EA0();
extern s32 func_00160ED8();

void func_00161ED0(void) {
    func_00160E70();
}

s32 func_00161EF0(void *arg0, s64 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s64 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x24) = arg2;
    M2C_FIELD(arg0, s32 *, 0x20) = arg3;
    func_00160EA0();
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    return 1;
}

s32 func_00161F30(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00161F50);
