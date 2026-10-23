#include "auto/prelude.h"

extern s32 func_00193980();
extern s128 * func_00185FE8();
extern s32 func_001954C0();
extern s32 func_00195640();
extern s32 func_00193988();
extern s32 func_00193990();

void func_00195438(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) *func_00185FE8(M2C_FIELD(arg0, s32 *, 0) + 0x90);
    func_001954C0(arg0);
    func_00195640(arg0);
}

void func_00195480(void) {
    func_00193988();
}

s32 func_001954A0(s32 arg0) {
    return func_00193990(arg0, 0);
}
