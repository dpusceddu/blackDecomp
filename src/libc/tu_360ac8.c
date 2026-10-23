#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00360AF0();
extern void * D_003D6944;

s32 func_00360AC8(s32 arg0, s32 arg1) {
    return func_00360AF0(arg0, arg1, (s32) (D_003D6944 + 0x5C));
}
