#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/recovered_types.h"

extern s32 func_00193980();
extern u8 func_00180BC0();
extern s32 func_00173690();
extern s32 func_00193988();
extern void func_00193990(RecoveredAIActionHeader *, u8);
extern void func_00193A28(RecoveredAIActionHeader *, u32, s32);
extern s32 func_001735E0(f32 *);
extern void func_00173640(f32 *, f32);
extern f32 AIManager_RandomRange(void *, f32, f32);
extern void *D_0040F4D4;
extern void *D_0040F4D0;
extern s128 func_001890D0(void *, f32);
extern u8 func_00182410(void *, s128, u8, u8);
extern void func_001825B0(void *);

void func_00193CC8(RecoveredAIActionHeader *arg0) {
    func_00193980();
    if (func_00180BC0(arg0->brain + 0xB30) == 0) {
        func_00193A28(arg0, 0xCU, 0);
    }
    func_00173690(&arg0->phase);
}

void func_00193D18(void) {
    func_00193988();
}

void func_00193D38(void) {

}

s32 func_00193D40(RecoveredAIActionHeader *action, s32 *event) {
    switch (*event) {
    case 5:
        func_00193A28(action, 0xC, 0);
        return 1;
    case 2:
        return 1;
    case 9:
        func_00193990(action, 1);
        return 0;
    case 6: {
        f32 *timer = (f32 *) ((u8 *) action + 8);
        if (func_001735E0(timer) == 0) {
            func_00173640(timer, AIManager_RandomRange(D_0040F4D4, 0.1f, 0.5f));
        }
        return 1;
    }
    default:
        return 0;
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_193cc8", func_00193E08);
// Unmatched: 00193FE8: clock-load register allocation and scheduling.
#ifdef NON_MATCHING
void func_00193FE8(RecoveredAIActionHeader *action, void *event) {
    f32 distance;
    s128 position;
    f32 elapsed;
    func_00193980();
    if (event != NULL && M2C_FIELD(event, s32 *, 0) == 1) {
        f32 radius = M2C_FIELD(event, f32 *, 8);
        distance = radius * radius;
    } else {
        distance = 5.0f;
    }
    M2C_FIELD(action, s32 *, 0x30) = 0;
    M2C_FIELD(action, f32 *, 8) = distance;
    elapsed = M2C_FIELD(D_0040F4D0, f32 *, 0x1C);
    position = func_001890D0((u8 *) action->brain + 0x150, elapsed * 8.0f);
    M2C_FIELD(action, s128 *, 0x10) = position;
    if ((func_00182410((u8 *) action->brain + 0x810, position, 0, 0) ^ 1) & 0xFF) {
        func_00193990(action, 0);
        return;
    }
    M2C_FIELD(M2C_FIELD(action->brain, void **, 0x694), u8 *, 0x30) = 0;
    func_001825B0((u8 *) action->brain + 0x810);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_193cc8", func_00193FE8);
