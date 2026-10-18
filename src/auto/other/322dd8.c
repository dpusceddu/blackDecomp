#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00322E00();

s32 func_00322DD8(s32 arg0) {
    u8 sp[8] __attribute__((aligned(16)));
    func_00322E00(arg0, 0, (s32) sp);
    return *(s32 *)(sp + 0);
}
