#include "auto/prelude.h"

extern s32 func_0010B160();

s32 func_0010EAC0(s32 arg0, s32 arg1) {
    func_0010B160(arg0);
    M2C_FIELD(arg0, s32 *, 0x34) = arg1;
    return 1;
}
