#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001093C0(s32, void *, s32, s32, s32, void *, s32, s32);
extern s32 D_0040F4C4;

void func_00143F90(void *arg0, void *arg1, s32 arg2, void *arg3, s32 arg4) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x80);
    if (M2C_FIELD(temp_4, s32 *, 0x1C) == 9) {
        func_001093C0(D_0040F4C4, arg1, 6, M2C_FIELD(temp_4, s32 *, 0), arg2, arg3, arg4, 0x02000000);
    }
}
