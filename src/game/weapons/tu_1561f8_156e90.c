#include "include_asm.h"
#include "ps2/prelude.h"

void func_00156E90(void *arg0) {
    s32 temp_3;

    if ((M2C_FIELD((M2C_FIELD(M2C_FIELD(arg0, void **, 0xFC), s32 *, 0x14) + M2C_FIELD(arg0, s8 *, 0)), u8 *, 0) != 0) && (temp_3 = M2C_FIELD(arg0, s32 *, 0xD8), (temp_3 != 1)) && (temp_3 != 2) && (temp_3 != 8) && (temp_3 != 0xB) && (temp_3 != 9)) {
        if (M2C_FIELD(arg0, u8 *, 0x108) != 0) {
            M2C_FIELD(arg0, s32 *, 0xD8) = 0x18;
            return;
        }
        M2C_FIELD(arg0, s32 *, 0xD8) = 0x17;
    }
}
