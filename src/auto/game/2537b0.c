#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00253E60();
extern s32 func_003608B8();

s32 func_002537B0(s32 arg0) {
    u16 temp_5;

    temp_5 = M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), u16 *, 2);
    func_00253E60(arg0, (s32) temp_5, 0, (s32) temp_5, 1, (s32) temp_5);
    func_003608B8((s32) (M2C_FIELD(arg0, u32 *, 0) + 8));
    return arg0;
}
