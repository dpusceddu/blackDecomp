#include "auto/prelude.h"

#include "types_ghidra.h"

void func_0030E278(void *arg0, s32 arg1, s32 arg2) {
    s32 *temp_2;
    s32 temp_3;
    s32 temp_5;

    if (arg2 != -1) {
        temp_5 = M2C_FIELD(arg0, s32 *, 4);
        M2C_FIELD(((arg2 * 0x24) + temp_5), s32 *, 0x20) = (s32) M2C_FIELD(((arg1 * 0x24) + temp_5), s32 *, 0x20);
    } else {
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) M2C_FIELD(((arg1 * 0x24) + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0x20);
    }
    temp_3 = arg1 * 0x24;
    M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0x20) = (s32) M2C_FIELD(arg0, s32 *, 0x44);
    M2C_FIELD(arg0, s32 *, 0x44) = arg1;
    temp_2 = func_0030E6B8(arg0, M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 4)), u32 *, 0x14));
    if (temp_2 != NULL) {
        *temp_2 -= 1;
    }
}
