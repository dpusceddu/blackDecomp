#include "ps2/prelude.h"

extern s32 func_00365D48(s32 *arg0, s16 arg1);

void func_0035D998(void *arg0) {
    func_00365D48(M2C_FIELD(arg0, s32 **, 0x54), M2C_FIELD(arg0, s16 *, 0xE));
}
