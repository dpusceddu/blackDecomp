#include "include_asm.h"
#include "ps2/prelude.h"

void func_001CAD48(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(arg1, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x20) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
    M2C_FIELD(arg0, s128 *, 0x30) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
    M2C_FIELD(arg0, s128 *, 0x40) = (s128) M2C_FIELD(arg1, s128 *, 0x30);
}
