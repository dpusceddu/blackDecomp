#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * func_00311398(void *, s32);
extern void * func_00311430(void *, void *, s32);
extern s32 D_0040E154;
extern s32 D_0040E150;

void * func_00313048(void *arg0, void *arg1, s32 arg2) {
    void *temp_2;

    temp_2 = func_00311398(func_00311430(arg0, arg1, arg2), 0);
    D_0040E154 = 0;
    D_0040E150 += 1;
    return temp_2;
}
