#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00175F50();
extern void * D_0040F4D4;

s32 func_00185318(s32 arg0, s32 arg1, s32 arg2) {
    return func_00175F50((s32) (D_0040F4D4 + 0xFA0), arg1, arg2, 0x221, M2C_FIELD(M2C_FIELD(arg0, u32 *, 0), s32 *, 0x7C), 1);
}
