#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00275748(void *, void *, s32, s32, s32, s32, s32);

s32 func_00384DA8(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    u8 sp[120] __attribute__((aligned(16)));

    *(s16 *)(sp + 0) = 0;
    *(void * *)(sp + 60) = arg3;
    *(s16 *)(sp + 64) = 0;
    *(void * *)(sp + 124) = arg4;
    return func_00275748(arg1, arg2, (s32) ((arg3 != NULL) ? arg3 : sp), (s32) ((arg4 != NULL) ? arg4 : (sp + 64)), 0, 0, arg0);
}
