#include "auto/prelude.h"

extern s32 func_00179960(s32);

void func_001796E0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x74) != 0) {
        func_00179960(M2C_FIELD(arg0, s32 *, 0x70));
    }
}
