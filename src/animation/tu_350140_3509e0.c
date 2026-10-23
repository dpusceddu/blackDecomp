#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_003504C8(s32 *, void *, s32, f32);

s32 func_003509E0(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2) {
    u8 sp[56] __attribute__((aligned(16)));

    *(s32 *)(sp + 20) = arg1;
    *(s32 *)(sp + 36) = arg2;
    *(s32 *)(sp + 0) = M2C_FIELD(arg0, s32 *, 0x10);
    *(f32 *)(sp + 8) = M2C_FIELD(arg0, f32 *, 0x1C) + 1.0f;
    *(s32 *)(sp + 12) = -3;
    *(f32 *)(sp + 28) = fparg1;
    *(f32 *)(sp + 32) = fparg2;
    *(s32 *)(sp + 40) = arg3;
    *(s32 *)(sp + 4) = 0;
    *(s32 *)(sp + 16) = 0;
    *(f32 *)(sp + 24) = fparg0;
    *(s32 *)(sp + 44) = 0;
    *(s32 *)(sp + 48) = 0;
    return func_003504C8(arg0, sp, 0, fparg0);
}
