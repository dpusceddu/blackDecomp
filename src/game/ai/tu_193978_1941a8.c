#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/action_views.h"
#include "game/actor_records.h"

extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_001825B0(void *);
extern void func_00193988(void);
extern void func_001880D8(void *);
extern void func_00173690(f32 *);
extern void func_00173640(f32 *, f32);


void func_001941A8(void **arg0) {
    func_00193980();
    func_00187FE0(*arg0 + 0x290, 0);
    M2C_FIELD(M2C_FIELD(*arg0, void **, 0x694), s8 *, 0x30) = 1;
    func_001825B0(*arg0 + 0x810);
}

void func_001941F8(void **state) {
    void *owner;
    u8 *movement;
    func_00193988();
    M2C_FIELD(M2C_FIELD(*state, void **, 0x694), s8 *, 0x30) = 0;
    owner = *state;
    movement = (u8 *) owner + 0x290;
    if (*movement != 0) {
        func_001880D8(movement);
    }
}
extern s32 func_00188F10(Recovered_ActorRecords*);
extern f32 func_00189310(Recovered_ActorRecords*);
extern u8 func_00188350(void*);
extern void func_00193990(void*, u8);
extern s32 func_00176F00(s32*);
extern s32 func_00173610(f32*);
extern s32 func_001944D8(void*);
extern s32 func_001945F0(s32);
extern s32 func_001829E8(void*);
extern u8 func_001829A8(void*);
extern s32 func_0016DFB0(void*, f32);
extern void* D_0040F4D4;
extern void func_00194888(void*);
extern void func_0017DB98(f32*, s128);
extern s128 func_00189048(Recovered_ActorRecords*);

void func_00194240(Recovered_ActionState* self) {
    f32* timer;
    s32 state;
    void* controller;

    if ((func_00188F10((Recovered_ActorRecords*)(((s8*)self->owner) + 0x150)) == 0) ||
        (func_00189310((Recovered_ActorRecords*)(((s8*)self->owner) + 0x150)) > 3.0f) ||
        (func_00188350((void*)(((s8*)self->owner) + 0x290)) != 0)) {
        func_00193990((void*)self, 0U);
        return;
    }
    if (M2C_FIELD(self->owner, u8*, 0x291) != 0) {
        func_00193990((void*)self, 1U);
    } else {
        state = self->unk_08;
        switch (state) {
            case 0:
                if (func_00176F00((s32*)((s8*)self->owner + 0x1FCC)) & 0xFF) {
                    timer = (f32*)((s8*)self + 0xC);
                    if (func_00173610(timer) && func_001944D8(self)) {
                        func_001945F0((s32)self);
                        func_00173640(timer, 1.0f);
                    }
                }
                break;
            case 1:
                if (func_001829E8((void*)(((s8*)self->owner) + 0x810)) != 0) {
                    self->unk_08 = 0;
                } else if (func_001829A8((void*)(((s8*)self->owner) + 0x810)) == 0) {
                    self->unk_08 = 0;
                }
                break;
            case 2:
            case 3:
                controller = M2C_FIELD(self->owner, void**, 0x7C);
                if (M2C_FIELD(controller, u8*, 0x3A9) == M2C_FIELD(controller, u8*, 0x3AA)) { self->unk_08 = 0; }
                break;
            case 4:
                if (func_00173610((f32*)(((s8*)self) + 0x10)) != 0) {
                    M2C_FIELD(self->owner, s8*, 0x38) = 0;
                    self->unk_08 = 0;
                    if (func_0016DFB0(D_0040F4D4, 0.25f) != 0) { func_00194888(self); }
                }
                break;
        }
        if (func_00188F10((Recovered_ActorRecords*)(((s8*)self->owner) + 0x150)) != 0) {
            s128 position = func_00189048((Recovered_ActorRecords*)(((s8*)self->owner) + 0x150));
            func_0017DB98((f32*)(((s8*)self->owner) + 0x650), position);
        }
        return;
    }
}
// Unmatched: 00194420: owner pointer register allocation.
#ifdef NON_MATCHING
void func_00194420(void **state) {
    func_00193980();
    func_00173690((f32 *) ((s8 *) state + 0x10));
    func_00173640((f32 *) ((s8 *) state + 0x0c), 0.0f);
    M2C_FIELD(state, s32 *, 8) = 0;
    func_00173690((f32 *) ((s8 *) state + 0x14));
    func_00187FE0(*state + 0x290, 0);
    M2C_FIELD(M2C_FIELD(*state, void **, 0x694), s8 *, 0x30) = 0;
    func_001825B0(*state + 0x810);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_1941a8", func_00194420);
#endif
void func_00194490(Recovered_ActionState *state) {
    void *owner;
    u8 *movement;
    func_00193988();
    M2C_FIELD(state->owner, s8 *, 0x38) = 0;
    owner = state->owner;
    movement = (u8 *) owner + 0x290;
    if (*movement != 0) {
        func_001880D8(movement);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_1941a8", func_001944D8);
