#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00274F80();

void * func_00271668(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    s32 temp_3;
    s32 temp_7;

    temp_7 = (s32) (((s32) arg2 > -1) ? arg2 : (arg2 + 3)) >> 2;
    temp_3 = (s32) (((s32) arg3 > -1) ? arg3 : (arg3 + 3)) >> 2;
    M2C_FIELD(arg0, void **, 0x14) = arg4;
    M2C_FIELD(arg0, void **, 0xC) = arg2;
    M2C_FIELD(arg0, void **, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = temp_7;
    M2C_FIELD(arg0, s32 *, 8) = temp_3;
    if (arg2 != (temp_7 * 4)) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_7 + 1);
    }
    if (arg3 != (temp_3 * 4)) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
    }
    M2C_FIELD(arg0, void **, 0) = func_00274F80(arg1, (void *) (((s32) M2C_FIELD(arg0, void **, 0xC) * (s32) M2C_FIELD(arg0, void **, 0x10)) << 0xA));
    return (void *)1;
}
