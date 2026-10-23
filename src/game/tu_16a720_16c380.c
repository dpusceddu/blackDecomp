#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 D_003BCEE0;
extern u8 D_0040D9B8;
extern void * D_0040F0E0;
extern s32 D_0040EAFC;

void func_0016C380(s32 arg0) {
    D_003BCEE0 = -1;
    D_0040D9B8 = 0;
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020D) = 1;
    D_0040EAFC = 0;
}
