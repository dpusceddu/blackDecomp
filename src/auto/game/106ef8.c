#include "auto/prelude.h"

extern s32 func_00105228();
extern void * D_0040F0E0;

void func_00106EF8(void *arg0) {
    void *temp_5;
    void *temp_6;

    temp_5 = arg0 + 0xC;
    temp_6 = M2C_FIELD(arg0, void **, 0x48);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 1);
    if ((s16) (M2C_FIELD(temp_5, u16 *, 0x14) - M2C_FIELD(temp_5, u16 *, 0x16)) >= (s32) M2C_FIELD(temp_6, u8 *, 0xF)) {
        func_00105228(D_0040F0E0 + 0x20220, 5, temp_6);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4, temp_6);
}

void func_00106F80(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 2);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), u8 *, 0x35) != 0) {
        func_00105228(D_0040F0E0 + 0x20220, 5);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4);
}
