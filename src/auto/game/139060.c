#include "auto/prelude.h"

extern s32 func_0016E6B0();
extern s32 D_0040F4D4;
extern s32 func_00135550();
extern s32 func_001354E0();
extern s32 func_0025C2C8();
extern s32 D_0040F4CC;
extern s32 func_0012A280();
extern s32 D_0040F4D0;
extern s32 func_00139838();

s32 func_00139060(s32 arg0, s32 arg1) {
    void *temp_3;

    func_0016E6B0(D_0040F4D4, arg1);
    if (func_00135550(arg1) != 0) {
        func_001354E0(arg1, 0);
    }
    if (M2C_FIELD(arg1, s32 *, 0xB4) != 0) {
        func_0025C2C8(D_0040F4CC, arg1);
    }
    func_0012A280(D_0040F4D0, arg1);
    func_00139838(arg0 + 0x7990, arg1);
    temp_3 = M2C_FIELD(arg1, void **, 0x10);
    return M2C_FIELD(temp_3, s32 (**)(s32), 0x24)(arg1 + M2C_FIELD(temp_3, s16 *, 0x20));
}
