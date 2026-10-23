#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

void * func_00370DA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5, void *arg6) {
    s32 temp_18;
    void *temp_16;
    void *temp_16_2;
    void *temp_17;
    void *temp_2;

    temp_2 = ((void *(*)()) arg0)();
    temp_16_2 = M2C_FIELD(temp_2, void **, 4);
    temp_16 = temp_16_2 + 0x10;
    temp_17 = temp_2 + M2C_FIELD(temp_16_2, s16 *, 0x10);
    temp_18 = ((s32 (*)()) arg1)();
    return M2C_FIELD(temp_16, void *(**)(void *, s32, s32, s32, s32, void *), 4)(temp_17, temp_18, arg2, arg3, ((s32 (*)()) arg4)(), arg5);
}
