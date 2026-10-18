#include "auto/prelude.h"

#include "types_ghidra.h"
extern void * func_001E51E0();
extern s32 func_001E63B8();
extern void * D_0040F4D0;

s32 func_001E6650(void *arg0, s32 arg1, s64 arg2, s32 arg3) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s64 *)(sp + 0) = arg2;
    if ((M2C_FIELD(arg0, u8 *, 0x184) == 0) && (func_001E51E0(M2C_FIELD(arg0, void **, 0x16C), arg0 + 0x160, sp) != NULL)) {
        M2C_FIELD(arg0, s32 *, 0x168) = arg1;
        func_001E63B8(arg0, *(s64 *)(sp + 0), arg3);
        M2C_FIELD(arg0, s32 *, 0x180) = arg3;
        M2C_FIELD(arg0, s64 *, 0x178) = *(s64 *)(sp + 0);
        M2C_FIELD(arg0, u8 *, 0x184) = 1U;
        M2C_FIELD(arg0, f32 *, 0x174) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    }
    return 0;
}
