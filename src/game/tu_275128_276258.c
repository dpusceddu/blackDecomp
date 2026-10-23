#include "auto/prelude.h"

extern void func_002763B0();
extern s32 func_00274138();

void func_00276258(void *arg0) {
    func_002763B0();
    func_00274138(M2C_FIELD(arg0, s32 *, 0x48) + 0x40, arg0 - 8);
}
