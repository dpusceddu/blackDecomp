#include "auto/prelude.h"

extern s32 (*D_003CEC68)();
extern s32 (*D_003CEC6C)();

void func_00312C48(s32 arg0) {
    D_003CEC68(arg0 + 0x40);
}

void func_00312C70(void) {
    D_003CEC6C();
}
