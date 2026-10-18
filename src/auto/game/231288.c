#include "auto/prelude.h"

extern M2C_UNK D_003E1208;
extern s32 func_00244CE8();
extern void func_00244CF8();
extern void func_00233C60();
extern s32 func_00250198();
extern s32 D_0043DEE0;

void func_00231288(u16 *arg0, s32 arg1) {
    u16 *temp_4;

    M2C_FIELD(arg0, M2C_UNK **, 0x14) = &D_003E1208;
    temp_4 = M2C_FIELD(arg0, u16 **, 0x34);
    if (temp_4 != NULL) {
        if (func_00244CE8(temp_4) == 0) {
            func_00244CF8(M2C_FIELD(arg0, u16 **, 0x34));
        }
    }
    func_00233C60(arg0, 0);
    if (arg1 & 1) {
        func_00250198(D_0043DEE0, arg0, 0x38);
    }
}
