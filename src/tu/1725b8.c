#include "auto/prelude.h"

extern s32 func_00176F00();
extern s32 func_0017B6F8();
extern void * D_0040F4D4;

void func_001725B8(void *arg0) {
    if ((M2C_FIELD(arg0, void **, 0x10) != NULL) && (func_00176F00(arg0 + 0x14) != 0)) {
        M2C_FIELD(arg0, s32 *, 0xC) = func_0017B6F8(D_0040F4D4 + 0x1290, M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s128 *, 0xA0));
    }
}

s32 func_00172610(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}

void func_00172618(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x10) = arg1;
}

s32 func_00172620(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_00172628(void) {
    return 1;
}

s32 func_00172630(void) {
    return 1;
}

void func_00172638(void) {

}
