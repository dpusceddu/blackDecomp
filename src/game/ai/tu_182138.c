#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00182158(void *);
extern s32 func_0017E5A8(s32);
extern s32 func_001829A8();
extern void func_00182550(void *, s32);
extern void func_00182A10(void *, f32);
extern u8 func_00182668(void *, s128, u32);
extern void func_00173640(f32 *, f32);
extern void func_0017E5B8(s32, s32, f32, f32);
extern void func_00182A60(void *);

void func_00182138(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x36) = 0;
    func_00182158((void *) arg0);
}

void func_00182158(void *controller) {
    s32 current;
    void *action;
    void *vtable;
    M2C_FIELD(controller, f32 *, 0x24) = 0.0f;
    current = M2C_FIELD(controller, s32 *, 0x40);
    M2C_FIELD(controller, f32 *, 0x20) = 0.0f;
    if (current == 0) {
        f32 value = M2C_FIELD(controller, f32 *, 0x24);
        M2C_FIELD(controller, u8 *, 0x38) = 0;
        M2C_FIELD(controller, u8 *, 0x37) = 0;
        func_0017E5B8(M2C_FIELD(controller, s32 *, 0x310) + 0x650, 1, value, value);
        return;
    }
    action = M2C_FIELD((s32) controller + (current << 2), void **, 0x44);
    vtable = M2C_FIELD(action, void **, 0x80);
    M2C_FIELD(vtable, void (**)(void *), 0x14)(
        (s8 *) action + M2C_FIELD(vtable, s16 *, 0x10));
    M2C_FIELD(controller, s32 *, 0x30) = M2C_FIELD(action, s32 *, 0x30);
    if (func_001829A8(controller)) {
        if (M2C_FIELD(controller, u8 *, 0x34)) {
            f32 second = M2C_FIELD(action, f32 *, 4);
            f32 first;
            M2C_FIELD(controller, f32 *, 0x24) = second;
            first = M2C_FIELD(action, f32 *, 0);
            M2C_FIELD(controller, f32 *, 0x20) = first;
            func_0017E5B8(M2C_FIELD(controller, s32 *, 0x310) + 0x650,
                           M2C_FIELD(action, u8 *, 8), first, second);
            if (M2C_FIELD(controller, f32 *, 0x24) > 0.0f) {
                func_00182A60(controller);
            }
        }
    } else {
        func_00173640((f32 *) ((s8 *) controller + 0x2C), 1.0f);
        func_00182550(controller, M2C_FIELD(controller, s32 *, 0x30));
    }
    M2C_FIELD(controller, u8 *, 0x38) = M2C_FIELD(controller, u8 *, 0x37);
    M2C_FIELD(controller, u8 *, 0x37) = 0;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182270);

void func_00182318(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x34) = arg1;
}

#include "ps2/recovered_types.h"
extern s32 func_00182608(void *, s128, s32, f32);
extern f32 func_0018DA40(void *);

s32 func_00182320(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, func_0018DA40(M2C_FIELD(arg0, void **, 0x310) + 0xC94));
}

#include "ps2/recovered_types.h"
extern s32 func_00182608(void *, s128, s32, f32);
extern f32 func_0018DA88(void *);

s32 func_00182380(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, 1.55f);
}

s32 func_001823B0(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x310), s8 *, 0x6D4) = 0;
    return func_00182608(arg0, arg1, arg2, func_0018DA88(M2C_FIELD(arg0, void **, 0x310) + 0xC94));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182508);

s32 func_00182510(void *arg0) {
    func_0017E5A8(M2C_FIELD(arg0, s32 *, 0x310) + 0x650);
    M2C_FIELD(arg0, s8 *, 0x37) = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182548);
void func_00182550(void *controller, s32 mode) {
    s32 current = M2C_FIELD(controller, s32 *, 0x40);
    if (current != 0) {
        void *action = M2C_FIELD((s32) controller + (current << 2), void **, 0x44);
        void *vtable = M2C_FIELD(action, void **, 0x80);
        M2C_FIELD(vtable, void (**)(void *), 0x44)(
            (s8 *) action + M2C_FIELD(vtable, s16 *, 0x40));
        M2C_FIELD(controller, s32 *, 0x40) = 0;
    }
    M2C_FIELD(controller, s32 *, 0x30) = mode;
}

void func_001825B0(void *arg0) {
    if (func_001829A8(arg0) != 0) {
        func_00182550(arg0, 0);
    } else {
        func_00182550(arg0, M2C_FIELD(arg0, s32 *, 0x30));
    }
    func_00182318(arg0, 0);
}

s32 func_00182608(void *controller, s128 position, s32 mode, f32 speed) {
    func_00182A10(controller, speed);
    func_00182318(controller, 1);
    return func_00182668(controller, position, mode != 0 ? 2 : 1);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182668);
s32 func_001828C0(void *controller, s128 position) {
    void *action;
    void *vtable;
    if (M2C_FIELD(controller, u8 *, 0x35) == 0 &&
        !((M2C_FIELD(M2C_FIELD(controller, void **, 0x310), u8 *, 0xD60) >> 4) & 1)) {
        func_00173640((f32 *) ((s8 *) controller + 0x2C), 1.0f);
        func_00182550(controller, 3);
        return 0;
    }
    if (M2C_FIELD(controller, s32 *, 0x40) != 1) {
        return 0;
    }
    M2C_FIELD(controller, s128 *, 0x10) = position;
    action = M2C_FIELD(controller, void **, 0x48);
    vtable = M2C_FIELD(action, void **, 0x80);
    M2C_FIELD(vtable, void (**)(void *, s128), 0x24)(
        (s8 *) action + M2C_FIELD(vtable, s16 *, 0x20), position);
    return 1;
}

s32 func_00182960(s32 arg0) {
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_182138", func_00182968);

s32 func_001829A0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}
