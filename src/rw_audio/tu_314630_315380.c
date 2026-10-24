#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_0031E0E0(s32, void *, s32, void *, s32);
extern s32 func_00315718(s32, void *, void *);

void * func_00315380(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));

    *(s32 *)(sp + 0) = arg0;
    *(void * *)(sp + 4) = NULL;
    func_0031E0E0(0, NULL, (s32) func_00315718, sp, 1);
    return *(void * *)(sp + 4);
}
