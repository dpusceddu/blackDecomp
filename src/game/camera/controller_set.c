#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai_manager.h"
// Partial controller and GCC dispatch views; unused spans remain UNVERIFIED.
typedef struct Recovered_ControllerDispatch {
    u8 unk_0[8];
    s16 unk_8;
    u16 unk_A;
    void (*unk_C)(void*);
} Recovered_ControllerDispatch;
typedef struct Recovered_ControllerSlot {
    u8 unk_0[0x78];
    u8 unk_78;
    u8 unk_79[0xB];
    Recovered_ControllerDispatch* unk_84;
    u8 unk_88[0x468];
} Recovered_ControllerSlot;
typedef struct Recovered_ControllerSet {
    u8 unk_0;
    u8 unk_1[0x1F];
    Recovered_ControllerSlot unk_20[8];
} Recovered_ControllerSet;
typedef struct Recovered_ControllerState {
    u8 unk_0[0x15C];
    u8 unk_15C;
} Recovered_ControllerState;
typedef char ControllerStride[sizeof(Recovered_ControllerSlot) == 0x4F0 ? 1 : -1];
typedef char ControllerSetStart[(u32) & ((Recovered_ControllerSet*)0)->unk_20 == 0x20 ? 1 : -1];
typedef struct Recovered_ChildDispatch {
    u8 unk_0[8];
    s16 unk_8;
    u16 unk_A;
    void (*unk_C)(void*);
    // UNVERIFIED: the configuration draft alone consumes this dispatch entry.
    s16 unk_10;
    u16 unk_12;
    void (*unk_14)(void*, void*);
} Recovered_ChildDispatch;
typedef struct Recovered_ControllerChild {
    u8 unk_0[0x4C];
    Recovered_ChildDispatch* unk_4C;
} Recovered_ControllerChild;
typedef struct Recovered_ControllerLifecycle {
    u8 unk_0[0x490];
    Recovered_ControllerChild* unk_490[9];
    s32 unk_4B4;
    // UNVERIFIED: the remaining fields are consumed only by the configuration draft.
    s32 unk_4B8[9];
    s32 unk_4DC;
    u8 unk_4E0[8];
    s32 unk_4E8;
} Recovered_ControllerLifecycle;
extern void func_0013EC10(void*, s32);
extern void func_0013EC38(void*, void*);
extern void func_00173690(void*);
extern Recovered_ManagedSlot* func_00135550(Recovered_ManagedActor*);
extern s32 func_00185C58(void*);

extern u8 D_0040D9A3;
extern Recovered_ControllerState* D_0040F504 __attribute__((section(".bss")));
extern void* D_0040F0E0 __attribute__((section(".bss")));
extern void func_00103918(void*, s32);
extern s32 func_00140F88(Recovered_ControllerSlot*);
void func_0011C930(Recovered_ControllerSet* self) {
    if (self->unk_0 && D_0040D9A3) {
        if (D_0040F504->unk_15C) {
            func_00103918(D_0040F0E0, 0);
            self->unk_0 = 0;
        }
    } else {
        Recovered_ControllerSlot* controller = self->unk_20;
        s32 count = 7;
        do {
            if (controller->unk_78) {
                Recovered_ControllerDispatch* dispatch = controller->unk_84;
                dispatch->unk_C((u8*)controller + dispatch->unk_8);
            }
            count--;
            controller++;
        } while (count >= 0);
    }
}
s32 func_0011C9C8(Recovered_ControllerSet* self) {
    Recovered_ControllerSlot* controller = self->unk_20;
    s32 count = 7;
    do {
        count--;
        func_00140F88(controller);
        controller++;
    } while (count >= 0);
    self->unk_0 = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/controller_set", func_0011CA20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/controller_set", func_0011CA28);

void func_00140AD0(Recovered_ControllerLifecycle* self) {
    s32 count = 8;
    Recovered_ControllerChild** table;
    func_0013EC10(self, 2);
    table = self->unk_490;
    {
        Recovered_ControllerChild** clear = table + 8;
        do { *clear-- = NULL; } while (--count >= 0);
    }
    self->unk_490[0] = (Recovered_ControllerChild*)((u8*)self + 0xF0);
    self->unk_490[1] = (Recovered_ControllerChild*)((u8*)self + 0x150);
    self->unk_490[2] = (Recovered_ControllerChild*)((u8*)self + 0x1B0);
    self->unk_490[4] = (Recovered_ControllerChild*)((u8*)self + 0x210);
    self->unk_490[3] = (Recovered_ControllerChild*)((u8*)self + 0x2A0);
    self->unk_490[5] = (Recovered_ControllerChild*)((u8*)self + 0x340);
    self->unk_490[6] = (Recovered_ControllerChild*)((u8*)self + 0x390);
    self->unk_490[7] = (Recovered_ControllerChild*)((u8*)self + 0x3E0);
    self->unk_490[8] = (Recovered_ControllerChild*)((u8*)self + 0x430);
    {
        Recovered_ControllerChild** child = table;
        count = 8;
        do {
            Recovered_ControllerChild* current = *child++;
            count--;
            current->unk_4C->unk_C((u8*)current + current->unk_4C->unk_8);
        } while (count >= 0);
    }
    self->unk_4B4 = -1;
}
#ifdef NON_MATCHING
// Unmatched: dispatch pointer and callback occupy exchanged registers (4 instructions).
s32 func_00140BB8(Recovered_ControllerLifecycle* self, Recovered_ManagedActor* owner) {
    s32* pending;
    s32 count;
    s32 empty = -1;
    func_0013EC38(self, owner);
    pending = self->unk_4B8;
    count = 8;
    do {
        Recovered_ControllerChild* child = *(Recovered_ControllerChild**)((u8*)pending - 0x28);
        s16 adjust = child->unk_4C->unk_10;
        void (*callback)(void*, void*) = child->unk_4C->unk_14;
        count--;
        callback((u8*)child + adjust, self);
        *pending++ = empty;
    } while (count >= 0);
    self->unk_4B4 = -1;
    func_00173690(self->unk_4E0);
    self->unk_4DC = 0;
    if (func_00135550(owner) == NULL)
        self->unk_4E8 = 0;
    else {
        s32 mode = func_00135550(owner)->unk_80;
        if (mode == 1) {
            if (func_00185C58(func_00135550(owner)->events))
                self->unk_4E8 = mode;
            else
                self->unk_4E8 = 2;
        } else
            self->unk_4E8 = 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/controller_set", func_00140BB8);
#endif
