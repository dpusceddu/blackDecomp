#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s64 func_00365E00(s32 *, s32, s32, s32);
extern s64 func_00365F20(s32 *, s32, void *, s32);

s32 func_0035D8B0(void *arg0, void *arg1, s32 arg2) {
    if (M2C_FIELD(arg0, u16 *, 0xC) & 0x100) {
        func_00365E00(M2C_FIELD(arg0, s32 **, 0x54), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 2);
    }
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) & 0xEFFF);
    return (s32) ((s64) (func_00365F20(M2C_FIELD(arg0, s32 **, 0x54), (s32) M2C_FIELD(arg0, s16 *, 0xE), arg1, arg2) << 0x20) >> 0x20);
}
