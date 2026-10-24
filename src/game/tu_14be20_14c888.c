#include "ps2/prelude.h"

extern s32 func_00272488();
extern s32 func_00348470();

void func_0014C888(void *arg0, s64 arg1) {
    u8 sp[8];
    func_00272488(arg1, sp);
    func_00348470(M2C_FIELD(arg0, s32 *, 0x40), sp);
}
