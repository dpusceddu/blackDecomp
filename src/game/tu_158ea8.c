#include "ps2/prelude.h"

extern s32 func_00155118();

void func_00158EA8(void *arg0, s16 arg1) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xF4), s16 *, 0x18) = arg1;
    if ((arg1 == 0) && (func_00155118(M2C_FIELD(arg0, s32 *, 0xFC), M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0xF4), void **, 8), s32 *, 0x64)) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x10B) = 1;
        return;
    }
    M2C_FIELD(arg0, s8 *, 0x10B) = 0;
}
