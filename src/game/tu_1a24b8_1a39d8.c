#include "ps2/prelude.h"

extern s32 func_001A2610();

void func_001A39D8(void *arg0) {
    func_001A2610();
    if (M2C_FIELD(arg0, u8 *, 0x82) != 0) {
        M2C_FIELD(arg0, s8 *, 0x81) = 0;
    }
}
