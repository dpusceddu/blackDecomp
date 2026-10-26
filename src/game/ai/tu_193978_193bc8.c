#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00193978();
extern s32 func_001735E0(f32 *);
extern s32 func_00173610(f32 *);
extern void func_00181F48(void *, s32, s32, f32, f32);
extern u8 func_0018D608(void *);
extern s32 func_00188F10(void *);
extern void func_0017E428(void *, s128);
extern s128 func_00189048(void *);

void func_00193BC8(void) {
    func_00193978();
}

void func_00193BE8(RecoveredAIActionHeader *action) {
    f32 *timer = (f32 *) ((u8 *) action + 8);
    if (func_001735E0(timer) && func_00173610(timer)) {
        func_00181F48((u8 *) action->brain + 0xC80, 0, 5, 0.0f, 1.0f);
    }
    if (func_0018D608((u8 *) action->brain + 0xD10)) {
        func_00181F48((u8 *) action->brain + 0xC80, 0, 5, 0.0f, 1.0f);
        func_00193990(action, 1);
        return;
    }
    if (func_00188F10((u8 *) action->brain + 0x150)) {
        s128 position = func_00189048((u8 *) action->brain + 0x150);
        func_0017E428((u8 *) action->brain + 0x650, position);
    }
}
