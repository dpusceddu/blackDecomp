#include "auto/prelude.h"

extern s32 func_001034B0(void *, void *);
extern void * D_0040F0E0;

void func_00105228(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    func_001034B0(D_0040F0E0, D_0040F0E0 + 0x20220);
}

void func_00105258(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x44) = 1;
}
