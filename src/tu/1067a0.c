#include "auto/prelude.h"

extern s32 func_00105228();
extern void * D_0040F0E0;
extern s32 func_00153420(void *);

void func_001067A0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) | 2);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), u8 *, 0x35) != 0) {
        func_00105228(D_0040F0E0 + 0x20220, 5);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4);
}

void func_00106808(void *arg0, s32 arg1, s64 arg2) {
    M2C_FIELD(arg0, s64 *, 0x10) = arg2;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) | 4);
}

void func_00106820(void *arg0, s64 arg1) {
    M2C_FIELD(arg0, s64 *, 0x18) = arg1;
}

s64 func_00106828(void *arg0) {
    return M2C_FIELD(arg0, s64 *, 0x18);
}

void func_00106830(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s64 *, 0x30) = 0;
    func_00153420(arg0 + 0xC);
}
