#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00193980();
extern s32 func_00187FE0();

s32 func_001963A8(s32 arg0) {
    void **temp_16;
    void *temp_2;

    temp_16 = arg0;
    func_00193980();
    func_00187FE0(*temp_16 + 0x290, 1);
    temp_2 = *temp_16;
    M2C_FIELD(M2C_FIELD(temp_2, void **, 0x694), s8 *, 0x30) = 0;
    return (s32) temp_2;
}
