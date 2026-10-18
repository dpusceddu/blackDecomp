#include "auto/prelude.h"

extern s32 func_001749E8();
extern s32 func_00183688();
extern s32 func_001736B8();

s32 func_001750E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 3, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    func_00183688(arg0 + 0x28, arg1, arg2);
    func_001736B8(arg0 + 0x50, 7);
    return 1;
}
