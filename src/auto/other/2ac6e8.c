#include "auto/prelude.h"

extern s32 D_004494D0;
extern void func_002CF888();

s32 func_002AC6E8(s32 arg0, s32 arg1, s32 arg2) {
    s32 (*temp_18)(s32, s32, s32);

    temp_18 = D_004494D0;
    func_002CF888();
    return (temp_18(arg0, arg1, arg2) == 0) ? 0 : arg0;
}
