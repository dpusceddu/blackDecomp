#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern void * func_001AFD80();
extern void * D_0040F4D0;
extern void func_00153310();
extern s32 func_001AFDA8();

void func_001529D0(void *arg0) {
    void *temp_16;
    void *temp_16_2;
    void *temp_2;

    temp_16 = arg0 + 0x1A0;
    temp_2 = func_001AFD80(temp_16, M2C_FIELD(arg0, s32 *, 0x118));
    if ((temp_2 != NULL) && (M2C_FIELD(temp_2, u16 *, 0x58) & 0x2000)) {
        M2C_FIELD(arg0, s8 *, 0x1C0) = 1;
        temp_16_2 = D_0040F4D0 + 0x5ACC;
        func_00153310(temp_16_2, M2C_FIELD(arg0, s32 *, 0x118), func_001AFDA8(temp_16) & 0xFF, arg0 + 0x70);
    }
}
