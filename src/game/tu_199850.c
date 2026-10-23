#include "auto/prelude.h"

extern s32 func_00193980();
extern void func_001998F8(void **arg0);

void func_00199850(void **arg0) {
    func_00193980();
    M2C_FIELD(*arg0, s8 *, 0x104) = 0;
    func_001998F8(arg0);
}
