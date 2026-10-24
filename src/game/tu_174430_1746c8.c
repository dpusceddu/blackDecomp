#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00178408(void *, s32, s32, s64, s32, u8, s32, u8);
extern void * D_0040F4D4;

void func_001746C8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x28) = 1;
}

void func_001746D8(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x28) = 0;
}

s32 func_001746E0(void *arg0) {
    s32 temp_2;

    temp_2 = func_00178408(D_0040F4D4 + 0xFA4, M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x1C), M2C_FIELD(arg0, s64 *, 0x40), M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, u8 *, 0xC), M2C_FIELD(arg0, s32 *, 0x38), M2C_FIELD(arg0, u8 *, 0x29));
    if (temp_2 == 0) {
        return 0;
    }
    M2C_FIELD(arg0, s32 *, 0x24) = temp_2;
    return 1;
}
