#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193990();
extern s32 func_00198908(void *);
extern s32 func_00189208(void *);
extern s32 func_00198968(void *, s128);
extern s128 *func_001893A0(void *);

s32 func_00198BB0(s32 arg0) {
    return func_00193990(arg0, 0);
}

// Unmatched: 00198BD0: boolean result register copy.
#ifdef NON_MATCHING
s32 func_00198BD0(void **action) {
    u8 result = 0;
    if (func_00198908(action)) {
        if (func_00189208((s8 *) *action + 0x150)) {
            result = func_00198968(action, *func_001893A0((s8 *) *action + 0x150)) != 0;
        }
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0_198bb0", func_00198BD0);
