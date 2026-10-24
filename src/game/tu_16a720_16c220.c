#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern u8 D_0040D9B8;
extern void * D_0040F0E0;
extern s32 D_003BCEE0;
extern s32 * func_0035C544(s32 *, s32, s32);
extern void * D_0040F4D0;
extern s32 D_0040F4E0;

void func_0016C220(s32 arg0) {
    if (D_0040D9B8 != 0) {
        M2C_FIELD(D_0040F0E0, u8 *, 0x2020D) = (u8) D_003BCEE0;
    }
}

void func_0016C250(void *arg0, s32 arg1) {
    if (D_0040D9B8 != 0) {
        func_0035C544(M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x48) * 0x8C0) + D_0040F4D0), s32 **, 0x2C4), M2C_FIELD(arg0, s32 *, 0x50), (s32) M2C_FIELD(M2C_FIELD(D_0040F4E0, u32 *, 0), u8 *, 1));
    }
}
