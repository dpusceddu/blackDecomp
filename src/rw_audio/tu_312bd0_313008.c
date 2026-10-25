#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040E154;
extern s32 func_003174F0();
extern s32 func_00311300(s32, M2C_UNK);
extern s32 func_00311430();
extern s32 func_003168C8();
extern s32 D_0040E150;

void func_00313008(void) {
    D_0040E154 = 1;
    func_003174F0();
    func_00311300(func_00311430(), 0);
    func_003168C8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313080);

s32 func_00313098(void) {
    return D_0040E150;
}
