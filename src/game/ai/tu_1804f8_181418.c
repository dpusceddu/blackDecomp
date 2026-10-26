#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00181C20();
extern s32 func_00176F00(s32);
extern void func_00181AD0(void *arg0, s32 arg1);
extern s32 func_00181D20();
extern void func_00181DA0(void *arg0);
extern void *func_00181A90(void *, s32);

void func_00181418(void *arg0) {
    func_00181C20(arg0);
    if (func_00176F00(M2C_FIELD(arg0, s32 *, 0x714) + 0x1FCC) & 0xFF) {
        func_00181AD0(arg0, 7);
    }
    func_00181D20(arg0);
    func_00181DA0(arg0);
}

void func_00181470(void *stack) {
    s32 count = M2C_FIELD(stack, s32 *, 0x4C0);
    if (count > 0) {
        do {
            void *action;
            void *vtable;
            count--;
            action = func_00181A90(stack, M2C_FIELD((s32) stack + (count << 2), s32 *, 0));
            vtable = M2C_FIELD(action, void **, 4);
            M2C_FIELD(vtable, void (**)(void *), 0x4C)(
                (s8 *) action + M2C_FIELD(vtable, s16 *, 0x48));
        } while (count > 0);
    }
}
void func_001814E8(void *stack) {
    s32 count = M2C_FIELD(stack, s32 *, 0x4C0);
    if (count > 0) {
        do {
            void *action;
            void *vtable;
            count--;
            action = func_00181A90(stack, M2C_FIELD((s32) stack + (count << 2), s32 *, 0));
            vtable = M2C_FIELD(action, void **, 4);
            M2C_FIELD(vtable, void (**)(void *), 0x54)(
                (s8 *) action + M2C_FIELD(vtable, s16 *, 0x50));
        } while (count > 0);
    }
}
void func_00181560(void *stack) {
    s32 count = M2C_FIELD(stack, s32 *, 0x4C0);
    if (count > 0) {
        do {
            void *action;
            void *vtable;
            count--;
            action = func_00181A90(stack, M2C_FIELD((s32) stack + (count << 2), s32 *, 0));
            vtable = M2C_FIELD(action, void **, 4);
            M2C_FIELD(vtable, void (**)(void *), 0x5C)(
                (s8 *) action + M2C_FIELD(vtable, s16 *, 0x58));
        } while (count > 0);
    }
}
