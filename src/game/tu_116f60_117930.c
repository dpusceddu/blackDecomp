#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_001179B8();

s32 func_00117930(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x50) = 0;
    func_001179B8(arg0, arg1);
    M2C_FIELD(arg1, f32 *, 0) = 45.0f;
    return 1;
}
