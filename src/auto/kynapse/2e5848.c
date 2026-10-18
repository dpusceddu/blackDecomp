#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_002E5358();
extern M2C_UNK D_003E9BB0;

s32 func_002E5848(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002E5358(arg0, arg1);
    M2C_FIELD(arg0, s32 *, 0x10) = arg2;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) arg3;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9BB0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    return arg0;
}
