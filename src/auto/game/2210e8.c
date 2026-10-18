#include "auto/prelude.h"

extern s32 func_0023DB58(void *, s32);

void func_002210E8(void) {

}

void func_002210F0(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) + 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}

void func_00221140(s32 arg0, void *arg1) {
    void *temp_16;
    void *temp_4;

    temp_16 = M2C_FIELD(arg1, void **, 4);
    func_0023DB58(temp_16, M2C_FIELD(M2C_FIELD(temp_16, void **, 0x48), s32 *, 0x18) - 1);
    temp_4 = M2C_FIELD(temp_16, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
}
