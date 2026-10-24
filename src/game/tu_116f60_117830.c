#include "ps2/prelude.h"

extern void func_00118248();

void func_00117830(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xA2) = 1;
    func_00118248(arg0 + 0x60);
}
