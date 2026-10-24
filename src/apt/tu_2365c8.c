#include "ps2/prelude.h"

extern s32 func_0023DB58();
extern void * D_0043DF40;

s32 func_002365C8(s32 arg0) {
    void *temp_4;

    func_0023DB58(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), s32 *, 0x18) + 1);
    temp_4 = M2C_FIELD(arg0, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
    return (s32) D_0043DF40;
}

s32 func_00236618(s32 arg0) {
    void *temp_4;

    func_0023DB58(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), s32 *, 0x18) - 1);
    temp_4 = M2C_FIELD(arg0, void **, 0x48);
    M2C_FIELD(temp_4, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_4, s32 *, 0x1C) & 0xFDFFFFFF);
    return (s32) D_0043DF40;
}
