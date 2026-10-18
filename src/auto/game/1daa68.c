#include "auto/prelude.h"

extern s32 func_0031D528();

void func_001DAA68(void *arg0) {
    func_0031D528(arg0 + 0x18, M2C_FIELD(arg0, s32 *, 0xD0) * M2C_FIELD(arg0, s32 *, 0xDC), M2C_FIELD(arg0, s32 *, 0xC0), M2C_FIELD(arg0, s32 *, 0xD8));
    M2C_FIELD(arg0, s8 *, 0xF8) = 1;
    M2C_FIELD(arg0, s32 *, 0xD0) = (s32) ((M2C_FIELD(arg0, s32 *, 0xD0) + 1) % 2);
}
