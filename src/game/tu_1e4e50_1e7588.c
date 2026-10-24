#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001E6A40(void *, s32);
extern void * D_0040F510;

void func_001E7588(void *arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_5 != 0) {
        func_001E6A40(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), void **, 4), temp_5);
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}
