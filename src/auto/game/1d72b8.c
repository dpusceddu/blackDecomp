#include "auto/prelude.h"

extern void * func_001092F8();

void func_001D72B8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s8 *, 0x90) = 0;
}

void func_001D72C0(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BEC) = func_001092F8();
}

void func_001D72E8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C04) = func_001092F8();
}

void func_001D7310(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1BF4) = func_001092F8();
}

void func_001D7338(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, void **, 0x1C08) = func_001092F8();
}
