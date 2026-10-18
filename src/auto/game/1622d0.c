#include "auto/prelude.h"

extern s32 func_00162310();
extern s32 func_00162420();

void func_001622D0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1C) != 0) {
        func_00162310();
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x1C) = 1U;
    func_00162420(arg0);
}
