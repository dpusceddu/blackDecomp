#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern void * D_0040E6C8;
extern s32 func_002AC568(void *);
extern void * D_0040E6CC;
extern void * D_0040E6C0;
extern s32 func_002C0D58(s32, void *, s32);

void func_002C65E0(void) {
    if (D_0040E6C8 != NULL) {
        func_002AC568(D_0040E6C8);
        D_0040E6C8 = NULL;
    }
    if (D_0040E6CC != NULL) {
        func_002AC568(D_0040E6CC);
        D_0040E6CC = NULL;
    }
}

s32 func_002C6620(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    s32 var_2;

    var_2 = 0;
    if (D_0040E6C0 != NULL) {
        *(s32 *)(sp + 4) = 0;
        *(s32 *)(sp + 0) = 0;
        *(s32 *)(sp + 8) = M2C_FIELD(D_0040E6C0, s32 *, 0xC);
        *(s32 *)(sp + 12) = M2C_FIELD(D_0040E6C0, s32 *, 0x10);
        var_2 = func_002C0D58(0, sp, arg2);
    }
    return var_2;
}
