#include "auto/prelude.h"

extern void * func_0011D498();
extern s32 func_001A7188();

void func_0011D450(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(func_0011D498(), s8 *, 0x3AF) = 0;
    func_001A7188(M2C_FIELD(func_0011D498(arg0), s32 *, 0x330));
}
