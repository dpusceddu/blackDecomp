#include "auto/prelude.h"

void func_001C4F08(void *arg0, u32 arg1) {
    M2C_FIELD(arg0, u32 *, 0xD5F0) = arg1;
    if (arg1 < (u32) M2C_FIELD(arg0, u32 *, 0xD5F4)) {
        M2C_FIELD(arg0, u32 *, 0xD5F4) = arg1;
    }
}
