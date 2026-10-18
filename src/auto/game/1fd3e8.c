#include "auto/prelude.h"

extern s32 func_001FD440();
extern s32 func_001FD648(void *);
extern s32 func_001FBA78(void *);

void func_001FD3E8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x2DB) == 0) {
        func_001FD440();
    }
    if (M2C_FIELD(arg0, u8 *, 0x2D9) == 0) {
        func_001FD648(arg0);
    }
    func_001FBA78(arg0 + 0xE0);
}

s32 func_001FD438(void) {
    return 1;
}
