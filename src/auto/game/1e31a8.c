#include "auto/prelude.h"

extern s32 func_002810A0(void *);

void func_001E31A8(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x260) != 0) {
        func_002810A0(arg0 + 0x250);
    }
}
