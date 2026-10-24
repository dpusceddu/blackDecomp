#include "ps2/prelude.h"

extern s32 func_0015A830(s32);
extern s32 func_0015A990(s32);

void func_00156D60(void *arg0) {
    func_0015A830(M2C_FIELD(arg0, s32 *, 0xF4));
}

void func_00156D80(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0xEC), u8 *, 0xC4) != 0) {
        func_0015A990(M2C_FIELD(arg0, s32 *, 0xF4));
        M2C_FIELD(arg0, s32 *, 0xD8) = 0x1E;
    }
}
