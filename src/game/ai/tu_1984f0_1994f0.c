#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_001984F0(void*);
extern void func_00198568(void*);
extern u8 func_00193A08(void*);
extern s128 func_00189048(void*);
extern s32 func_00180B70(void*, s128);
extern void func_00193990(void*, u8);
extern s32 func_001829E8(void*);
extern u8 func_001829A8(void*);
extern s32 func_00176F00(void*);
extern void func_0017E428(void*, s128);
extern void func_0017DB98(void*, s128);
extern u8 func_00182410(void*, s128, u8, u8);
extern void func_00181F48(void*, s32, s32, f32, f32);
extern s32 func_00198908(void*);

u8 func_001994F0(void **arg0) {
    return M2C_FIELD(M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), void **, 0x7C), u8 *, 0x3AA);
}

void func_00199508(u8** self) {
    s128 position;
    func_001984F0(self);
    if (!func_00193A08(self)) {
        position = func_00189048(*self + 0x150);
        if (func_00180B70(*self + 0xB30, position)) {
            if (func_001829E8(*self + 0x810)) goto busy;
            if (func_001829A8(*self + 0x810)) goto proceed;
busy:
            func_00193990(self, 0);
            return;
proceed:
            if ((u8)func_00176F00(*self + 0x1FCC)) {
                u8* owner = *self;
                func_0017E428(owner + 0x650, func_00189048(owner + 0x150));
                owner = *self;
                func_0017DB98(owner + 0x650, func_00189048(owner + 0x150));
                func_00182410(*self + 0x810, position, 0, 0);
            }
        } else {
            func_00193990(self, 0);
        }
    }
}
void func_00199628(u8** self) {
    s128 position;
    func_00198568(self);
    position = func_00189048(*self + 0x150);
    func_00182410(*self + 0x810, position, 0, 0);
    func_00181F48(*self + 0xC80, 0, 0x1B, 0.0f, 2.0f);
}
#ifdef NON_MATCHING
// Unmatched: predicate-result lifetime removes one native register copy.
s32 func_00199690(u8** self) {
    s32 result = 0;
    s128 position = func_00189048(*self + 0x150);
    if (func_00198908(self)) result = func_00180B70(*self + 0xB30, position) != 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0_1994f0", func_00199690);
#endif
