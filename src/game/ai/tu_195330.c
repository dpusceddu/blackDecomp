#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/action_views.h"

extern s32 func_00193980();
extern s128 * func_00185FE8();
extern s32 func_001954C0();
extern void *func_00195640();
extern s32 func_00193988();
extern s32 func_00193990();
extern u8 func_001829A8(void *);
extern s32 func_00185F18(void *);
extern s32 func_00188F10(void *);
extern s128 func_00189048(void *);
extern void func_0017E428(void *, s128);
extern s32 func_0018AB08(void *);
extern void func_00186E40(void *);
extern void func_001825B0(void *);
extern s32 func_00187960(void *, s32);
extern void *func_00181F48(void *, s32, s32, f32, f32);
extern void *func_00184238(void *, void *);

void func_00195330(Recovered_AIAction *action) {
    u8 *owner;
    if (!func_001829A8(action->owner + 0x810)) goto reset;
    if (func_00185F18(action->owner + 0x90)) {
        if (func_00188F10(action->owner + 0x150)) {
            owner = action->owner;
            func_0017E428(owner + 0x650, func_00189048(owner + 0x150));
        }
        if (func_001954C0(action)) {
            if (func_00188F10(action->owner + 0x150) && !func_0018AB08(action->owner + 0x150)) {
                func_00186E40(action->owner + 0x90);
                func_001825B0(action->owner + 0x810);
reset:
                func_00193990(action, 0);
            } else {
                func_001825B0(action->owner + 0x810);
                func_00193990(action, 1);
            }
        }
    } else {
        func_001825B0(action->owner + 0x810);
        func_00193990(action, 0);
    }
}

void func_00195438(void *arg0) {
    func_00193980();
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) *func_00185FE8(M2C_FIELD(arg0, s32 *, 0) + 0x90);
    func_001954C0(arg0);
    func_00195640(arg0);
}

void func_00195480(void) {
    func_00193988();
}

s32 func_001954A0(s32 arg0) {
    return func_00193990(arg0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195330", func_001954C0);
// Unmatched: 00195640: mode dispatch and command call scheduling.
#ifdef NON_MATCHING
void *func_00195640(Recovered_AIAction *action) {
    s32 mode = 2;
    if (func_00188F10(action->owner + 0x150)) {
        mode = func_00187960(action->owner + 0x90, 1);
    }
    switch (mode) {
    case 0:
        return func_00181F48(action->owner + 0xC80, 0, 0xC, 0.0f, 1.0f);
    case 1:
        func_00184238(action->owner + 0x6F0, (void *) 1);
        return func_00181F48(action->owner + 0xC80, 0, 0x1C, 0.0f, 1.0f);
    default:
        return func_00181F48(action->owner + 0xC80, 0, 0x19, 0.0f, 1.0f);
    }
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_195330", func_00195640);
