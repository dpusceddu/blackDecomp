#include "auto/prelude.h"

extern s32 D_0040E154;
extern s32 func_003174F0();
extern s32 func_00311300(s32, M2C_UNK);
extern s32 func_00311430();
extern s32 func_003168C8();

void func_00313008(void) {
    D_0040E154 = 1;
    func_003174F0();
    func_00311300(func_00311430(), 0);
    func_003168C8();
}
