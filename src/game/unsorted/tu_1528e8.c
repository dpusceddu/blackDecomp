#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0014C888();
extern s32 func_0014CDB8();

void func_001528E8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 0x11C) = arg1;
    M2C_FIELD(M2C_FIELD(arg1, void **, 0x40), void **, 0x84) = arg0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x120), s8 *, 0x60) = func_0014C888(arg1, M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x118), void **, 0x48), s64 *, 0x60));
}

void func_00152930(void *arg0, void *arg1, s64 arg2) {
    M2C_FIELD(arg0, void **, 0x11C) = arg1;
    func_0014CDB8(M2C_FIELD(arg0, void **, 0x120));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x120), s8 *, 0x60) = func_0014C888(M2C_FIELD(arg0, void **, 0x11C), arg2);
    M2C_FIELD(arg0, s8 *, 0x13D) = 1;
}
