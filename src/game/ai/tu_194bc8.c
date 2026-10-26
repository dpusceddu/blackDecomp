#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_00193988();
extern void func_00193980(void);
extern s32 func_00185F00(void *);
extern u8 func_00182410(void *, s128, u8, u8);
extern s32 func_00185F10(s32);
extern void func_00194C60(void **);
extern void func_00193990(RecoveredAIActionHeader *, u8);
extern s32 func_00188F10(void *);
extern s32 func_00187960(void *, s32);
extern void *func_00181F48(void *, s32, s32, f32, f32);
extern void func_00184238(void *, void *);

void func_00194BC8(RecoveredAIActionHeader *action) {
    s128 position;
    func_00193980();
    if (func_00185F00((u8 *) action->brain + 0x90) == 0) {
        func_00193990(action, 0);
        return;
    }
    position = *(s128 *) func_00185F10((s32) action->brain + 0x90);
    func_00182410((u8 *) action->brain + 0x810, position, 0, 0);
    func_00194C60((void **) action);
}
void func_00194C40(void) {
    func_00193988();
}

// Unmatched: 00194C60: mode dispatch and command call scheduling.
#ifdef NON_MATCHING
void func_00194C60(void **action) {
    s32 mode = 2;
    s32 command;
    if (func_00188F10((u8 *) *action + 0x150)) {
        mode = func_00187960((u8 *) *action + 0x90, 0);
    }
    if (mode != 1) {
        if (mode < 2) {
            if (mode != 0) goto other;
            command = 0xC;
            goto play;
        }
        goto other;
    }
    func_00184238((u8 *) *action + 0x6F0, (void *) 1);
    command = 0x1C;
play:
    func_00181F48((u8 *) *action + 0xC80, 0, command, 0.0f, 1.0f);
    return;
other:
    func_00181F48((u8 *) *action + 0xC80, 0, 0xF, 0.0f, 1.0f);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_194bc8", func_00194C60);
