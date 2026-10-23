#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0031E0E0(s32, void *, s32, void *, s32);
extern s32 func_0031E5C8(s32, s32 *, void *);

s32 func_0031DF58(s32 arg0, void *arg1, void *arg2) {
    u8 sp[8] __attribute__((aligned(16)));

    *(void * *)(sp + 0) = arg1;
    *(void * *)(sp + 4) = arg2;
    func_0031E0E0(arg0, NULL, (s32) func_0031E5C8, sp, 1);
    return *(void * *)(sp + 4) != NULL;
}
