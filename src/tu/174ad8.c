#include "auto/prelude.h"
#include "types_ghidra.h"

u8 func_00174AD8(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 8) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x18), s32 *, 0x14)), u8 *, 4);
}

s32 func_00174AF0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(temp_2, s32 *, 0xC) + (M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_2, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 0x10);
}

f32 func_00174B20(void *arg0, s32 arg1, s32 arg2) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x18);
    return M2C_FIELD(((M2C_FIELD(((arg2 * 2) + M2C_FIELD(((arg1 * 8) + M2C_FIELD(temp_3, s32 *, 0x14)), s32 *, 0)), u16 *, 0) * 4) + M2C_FIELD(temp_3, s32 *, 0x18)), f32 *, 0);
}
