#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00275748(void *, void *, s32, s32, s32, s32, s32);

s32 func_00384CF0(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 sp[120] __attribute__((aligned(16)));

    *(s16 *)(sp + 0) = 0;
    *(void * *)(sp + 60) = arg2;
    *(s16 *)(sp + 64) = 0;
    *(void * *)(sp + 124) = arg3;
    return func_00275748(arg0, arg1, (s32) ((arg2 != NULL) ? arg2 : sp), (s32) ((arg3 != NULL) ? arg3 : (sp + 64)), 0, 0, -1);
}
