#include "auto/prelude.h"

extern s32 func_001B37C8();
extern s32 D_0040F4D8;
extern s32 func_001B61C0();

s32 func_00127A40(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0xD8) != 0xFFFF) {
        func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0xD8));
    }
    if (M2C_FIELD(arg0, s32 *, 0xD4) != 0) {
        func_001B61C0(D_0040F4D8 + 0x512E0, arg0);
        M2C_FIELD(arg0, s32 *, 0xD4) = 0;
    }
    return 1;
}

void func_00127AB8(void) {

}

void func_00127AC0(void) {

}
