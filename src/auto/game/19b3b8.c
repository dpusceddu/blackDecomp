#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00193980();
extern s32 func_0019B6D8();

s32 func_0019B3B8(s32 arg0) {
    void **temp_16;

    temp_16 = arg0;
    func_00193980();
    M2C_FIELD(M2C_FIELD(*temp_16, void **, 0x694), s8 *, 0x35) = 1;
    return func_0019B6D8((s32) temp_16);
}
