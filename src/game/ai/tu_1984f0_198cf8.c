#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193990();
extern void func_001984F0(void *);
extern u8 func_00193A08(void *);
extern void func_0017E428(void *, s128);
extern s128 func_00189048(void *);
extern s32 func_001829E8(void *);
extern s32 func_001829A8(void *);
extern s32 func_00176F00(void *);
extern u8 func_00198E50(void *);
extern u8 func_00182410(void *, s128, u8, u8);

typedef struct {
    u8 *owner;
    u8 unk_04[12];
    s128 position;
    u8 moving;
} Recovered_ActionMove;

s32 func_00198CF8(s32 arg0) {
    return func_00193990(arg0, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1984f0_198cf8", func_00198D18);
void func_00198D40(Recovered_ActionMove *action) {
    u8 *owner;
    func_001984F0(action);
    if (func_00193A08(action) == 0) {
        owner = action->owner;
        func_0017E428(owner + 0x650, func_00189048(owner + 0x150));
        if (action->moving) {
            if (func_001829E8(action->owner + 0x810) != 0 ||
                func_001829A8(action->owner + 0x810) == 0) {
                func_00193990(action, 0);
            }
        } else if (func_00176F00(action->owner + 0x1FCC) & 0xFF) {
            action->moving = func_00198E50(action);
            if (!action->moving) {
                func_00193990(action, 0);
            } else {
                func_00182410(action->owner + 0x810, action->position, 0, 0);
            }
        }
    }
}
