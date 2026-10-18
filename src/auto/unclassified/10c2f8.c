#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0010B2A8(void *);
extern void * D_0040F4F0;
extern s32 func_0010B238(void *);
extern s32 func_0010B270(void *);
extern s32 func_0010B2C0(void *, s32);
extern s32 func_0010B2D8(void *);

void func_0010C2F8(s32 arg0) {
    switch (arg0) {
    case 1:
        func_0010B2A8(D_0040F4F0);
        return;
    case 3:
        func_0010B238(D_0040F4F0);
        return;
    case 4:
        func_0010B270(D_0040F4F0);
        return;
    case 5:
        func_0010B2C0(D_0040F4F0, 0);
        return;
    case 9:
        func_0010B2D8(D_0040F4F0);
        /* fallthrough */
    default:
        return;
    }
}
