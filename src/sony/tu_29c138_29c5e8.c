#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0029C138();

s32 func_0029C5E8(u32 *arg0, s32 arg1) {
    if (arg1 == 1) {
        return ((u32) *arg0 >> 8) & 1;
    }
    func_0029C138();
    return 0;
}
