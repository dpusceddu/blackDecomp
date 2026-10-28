#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001D9EA8();

s32 func_001DD728(void *arg0) {
    return func_001D9EA8(M2C_FIELD(arg0, void ***, 0x30));
}
