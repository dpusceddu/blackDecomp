#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00311278(s32, void *);
extern s32 func_00311498(void *, void *);

s32 func_00311248(void *arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(void * *)(sp + 0) = arg0;
    *(s32 *)(sp + 4) = 0;
    func_00311278((s32) func_00311498, sp);
    return *(s32 *)(sp + 4);
}
