#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_00193988();
extern s32 func_00188F10(void *);
extern f32 func_00189310(void *);
extern u8 func_00188350(void *);
extern void func_00193990(RecoveredAIActionHeader *, u8);
extern void func_0017DB98(void *, s128);
extern s128 func_00189048(void *);

void func_001940C8(void) {
    func_00193988();
}

void func_001940E8(RecoveredAIActionHeader *action) {
    if (!func_00188F10((u8 *) action->brain + 0x150)) goto failed;
    if (func_00189310((u8 *) action->brain + 0x150) > 3.0f) goto failed;
    if (func_00188350((u8 *) action->brain + 0x290) == 0) goto active;
failed:
    func_00193990(action, 0);
    return;
active:
    if (M2C_FIELD(action->brain, u8 *, 0x291)) {
        func_00193990(action, 1);
        return;
    }
    {
        s128 position = func_00189048((u8 *) action->brain + 0x150);
        func_0017DB98((u8 *) action->brain + 0x650, position);
    }
}
