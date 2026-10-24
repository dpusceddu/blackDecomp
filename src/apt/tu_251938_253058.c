#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_002530E8();
extern s32 func_0035C544();

s32 func_00253058(s32 arg0, s32 arg1) {
    s32 temp_16;
    u16 temp_17;

    temp_17 = M2C_FIELD(M2C_FIELD(arg1, u32 *, 0), u16 *, 2);
    func_002530E8(arg0, (s32) temp_17);
    temp_16 = M2C_FIELD(arg0, u32 *, 0) + 8;
    func_0035C544(temp_16, (s32) (M2C_FIELD(arg1, u32 *, 0) + 8), (s32) temp_17);
    M2C_FIELD((temp_16 + temp_17), s8 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), u16 *, 2) = temp_17;
    M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), u16 *, 6) = (u16) M2C_FIELD(M2C_FIELD(arg1, u32 *, 0), u16 *, 6);
    return arg0;
}
