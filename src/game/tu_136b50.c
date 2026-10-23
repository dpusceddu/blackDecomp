#include "auto/prelude.h"

extern s32 func_00135B60();
extern s32 func_0035C544(s32, s32, s32);

s32 func_00136B50(void *arg0) {
    void *temp_2;

    temp_2 = func_00135B60();
    func_0035C544(M2C_FIELD(arg0, s32 *, 0x354), M2C_FIELD(temp_2, s32 *, 0x38), M2C_FIELD(temp_2, s32 *, 0x3C));
    func_0035C544(M2C_FIELD(arg0, s32 *, 0x358), M2C_FIELD(temp_2, s32 *, 0x40), M2C_FIELD(temp_2, s32 *, 0x44));
    M2C_FIELD(arg0, s64 *, 0x370) = 0;
    return 1;
}
