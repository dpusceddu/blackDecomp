#include "auto/prelude.h"

extern s32 func_00275340();
extern s32 func_00275398();
extern s32 func_00275260();
extern s32 func_0020DC60();
extern s32 func_0020DE78();

void func_0020DD98(M2C_UNK *arg0, void *arg1) {
    u8 sp[512];
    s32 temp_16;
    s32 temp_17;

    temp_17 = func_00275340(M2C_FIELD(arg0, s32 *, 4));
    temp_16 = 0x100 - temp_17;
    func_00275398(sp, 0x100, M2C_FIELD(arg0, s32 *, 4));
    if (temp_16 > 0) {
        func_00275260(arg1, sp + (temp_17 * 2), temp_16);
    }
    func_0020DC60(arg0, temp_17 + temp_16);
    func_0020DE78(arg0, sp);
}
