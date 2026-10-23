#include "auto/prelude.h"

extern s32 func_003949A0();
extern M2C_UNK D_003F1118;
extern s32 D_003EFCC0;

s32 func_0030D0E0(s32 arg0, s32 arg1, s32 arg2) {
    func_003949A0(arg0, arg1, arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003F1118;
    return arg0;
}

void func_0030D120(void) {
    D_003EFCC0 = 0;
}
