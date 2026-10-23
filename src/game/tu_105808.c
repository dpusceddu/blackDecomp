#include "auto/prelude.h"

void func_00105808(void) {

}

void func_00105810(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 1);
}

void func_00105820(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 2);
}

void func_00105830(void *arg0, s32 arg1, s64 arg2) {
    M2C_FIELD(arg0, s64 *, 0x10) = arg2;
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 4);
}

void func_00105848(s32 *arg0) {
    *arg0 = 1;
}
