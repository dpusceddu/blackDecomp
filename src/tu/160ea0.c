#include "auto/prelude.h"

extern s32 func_00165AF8();
extern s32 func_00165B98();
extern s32 func_00165BB0();
extern s32 func_00160E70();
extern s32 func_00165BC8(void *, s32);

s32 func_00160EA0(void *arg0) {
    func_00165AF8();
    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    return 1;
}

void func_00160ED0(void) {

}

s32 func_00160ED8(void) {
    func_00165B98();
    return 1;
}

void func_00160EF8(void) {
    func_00165BB0();
}

void func_00160F18(void) {

}

void func_00160F20(void *arg0, s32 arg1) {
    func_00160E70();
    func_00165BC8(arg0, arg1);
}
