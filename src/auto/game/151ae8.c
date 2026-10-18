#include "auto/prelude.h"

extern s32 func_0014C140();
extern void * func_001AFD80();
extern s32 func_00151B40();

void func_00151AE8(void *arg0) {
    void *temp_2;

    func_0014C140();
    temp_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, u16 *, 0x5A) & 0x10)) {
        func_00151B40(arg0, 0, 0);
    }
}
