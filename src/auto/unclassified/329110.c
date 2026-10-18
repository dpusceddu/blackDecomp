#include "auto/prelude.h"

extern s32 func_00316400(s32, M2C_UNK *);
extern M2C_UNK D_004092D0;
extern s32 func_00312C70(s32);
extern s32 func_00328E60();

void func_00329110(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x29) & 1) && (func_00316400(M2C_FIELD(arg0, s32 *, 0x14), &D_004092D0) != 0)) {
        func_00312C70(M2C_FIELD(arg0, s32 *, 0x4C));
        return;
    }
    func_00328E60(M2C_FIELD(arg0, s32 *, 0x4C));
}
