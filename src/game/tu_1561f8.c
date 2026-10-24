#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00382348(void *, s32);
extern M2C_UNK D_00414D68;

s32 func_001561F8(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_00382348(&D_00414D68, 0x02B9D6F8);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0xD8) = 0;
    M2C_FIELD(arg0, s32 *, 0xDC) = 0;
    M2C_FIELD(arg0, s32 *, 0xE0) = 0;
    M2C_FIELD(arg0, s8 *, 0x105) = 0;
    M2C_FIELD(arg0, s8 *, 0x106) = 0;
    M2C_FIELD(arg0, s8 *, 0x107) = 0;
    M2C_FIELD(arg0, s8 *, 0x108) = 0;
    M2C_FIELD(arg0, s8 *, 0x109) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 0;
    M2C_FIELD(arg0, s8 *, 0x10A) = 0;
    M2C_FIELD(arg0, s8 *, 0x10B) = 0;
    M2C_FIELD(arg0, s8 *, 0x10C) = 0;
    M2C_FIELD(arg0, s8 *, 0x10D) = 0;
    M2C_FIELD(arg0, s8 *, 0x100) = 0;
    M2C_FIELD(arg0, s8 *, 0x101) = 0;
    M2C_FIELD(arg0, s8 *, 0x102) = 0;
    M2C_FIELD(arg0, s32 *, 0xF0) = 0;
    return temp_v0;
}
