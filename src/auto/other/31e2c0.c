#include "auto/prelude.h"

extern s32 func_00317A78();
extern s32 func_00318880();
extern s32 func_00312C48();

s32 func_0031E2C0(s32 arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_3 & 0x40) {
        return func_00317A78(M2C_FIELD(arg0, s32 *, 0x48), M2C_FIELD(arg0, s32 *, 0x58));
    }
    if (temp_3 & 0x80) {
        return func_00318880(M2C_FIELD(arg0, s32 *, 0x48), arg1);
    }
    return func_00312C48(arg1, M2C_FIELD(arg0, s32 *, 0x58));
}
