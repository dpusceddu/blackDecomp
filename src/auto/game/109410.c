#include "auto/prelude.h"

extern s32 func_0035CBC0();

void func_00109410(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_16;

    temp_16 = (arg2 * 0x140) + arg0;
    func_0035CBC0(temp_16 + 0x14);
    M2C_FIELD(temp_16, s32 *, 0x114) = arg3;
    M2C_FIELD(temp_16, s32 *, 0x118) = arg4;
    M2C_FIELD(temp_16, s8 *, 0x13A) = 1;
}
