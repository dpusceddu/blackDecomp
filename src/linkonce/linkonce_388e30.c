#include "ps2/prelude.h"

void func_00388E30(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_00388E40(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

void func_00388E48(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_00388E58(void *arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 8);
}

void func_00388E70(void) {

}

s32 func_00388E78(void) {
    return 0;
}

s32 func_00388E80(s32 arg0, s32 arg1) {
    return arg1;
}
