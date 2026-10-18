#include "auto/prelude.h"

extern s32 func_00374188();
extern s32 func_00311B50();
extern s32 func_00377840();
extern s32 func_00322C70();

s32 func_00374348(s32 arg0, s32 arg1, s32 arg2) {
    func_00374188(arg0, 1);
    func_00311B50(M2C_FIELD(arg0, s32 *, 0x80));
    func_00377840(arg0 + 0x84);
    return func_00322C70(arg0, arg1, arg2);
}
