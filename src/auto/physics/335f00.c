#include "auto/prelude.h"

void func_00335F00(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x3C);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x20);
}
