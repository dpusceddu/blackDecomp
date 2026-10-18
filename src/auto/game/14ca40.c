#include "auto/prelude.h"

extern s32 func_00343F38();
extern s32 func_00343ED0(void *);

void func_0014CA40(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x20) = func_00343F38();
    func_00343ED0(arg0);
}
