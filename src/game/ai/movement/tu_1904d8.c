#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai/movement_views.h"
#include "game/ai/actor_slot_values.h"


#ifdef NON_MATCHING

static inline s128 Movement_WidenPoint(f32 x, f32 y, f32 z) {
    s128 pair;
    s128 result;
    __asm__("pextlw tmpv, zsrc, xsrc" : "=r tmpv"(pair) : "r xsrc"(x), "r zsrc"(z));
    __asm__("pextlw resv, ysrc, tmpv" : "=r resv"(result) : "r ysrc"(y), "r tmpv"(pair));
    return result;
}

extern Recovered_MovementGoal* func_001809F0(void*);
extern s128 func_00180A00(void*);
#endif

extern s32 func_0018E488();
extern s32 func_0018E5E0(Recovered_MovementObserver*, s128);
extern s32 func_0018E680(Recovered_MovementObserver*, s128, void*);
extern Recovered_AIManager* D_0040F4D4;
extern void func_00189720(void*, void*);
extern void func_00189700(void*, void*);
extern void func_0018E338(Recovered_MovementObserver*);
extern s32 func_00180BC0(void*);
extern void func_0016ABA8(void*, s32, u8, void*);
extern s32 func_00176F00(void*);
extern void func_00190958(Recovered_MovementObserver*);
extern u8* D_0040F4D0;
extern s32 func_0018D698(s32, M2C_UNK);

void func_001904D8(Recovered_MovementObserver* self) {
    u8* params;
    func_0018E338(self);
    params = M2C_FIELD(self->unk_00, u8**, 0x30);
    if (!self->unk_18 && M2C_FIELD(params, u8*, 0x30)) {
        s32 ready = func_00180BC0((u8*)self->unk_04 + 0xB30);
        self->unk_18 = ready;
        if ((u8)ready) {
            u8* context = self->unk_04;
            func_0016ABA8(context + 0x1F90, M2C_FIELD(params, s32*, 0x20),
                          M2C_FIELD(params, u8*, 0x30), M2C_FIELD(context, void**, 0x7C));
        }
    }
    if (self->unk_14 && (u8)func_00176F00((u8*)self->unk_04 + 0x1FCC)) {
        func_00190958(self);
    }
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_1904d8", func_00190580);

void func_00190730(void *arg0) {
    func_0018E488();
    func_0018D698(M2C_FIELD(arg0, s32 *, 4) + 0xD10, 0);
}

#ifdef NON_MATCHING
// Unmatched: point construction stack spill and scalar scheduling differ.
s128 func_00190768(Recovered_MovementObserver* self) {
    if (func_001809F0((u8*)self->unk_04 + 0xB30)) {
        Recovered_MovementGoal* goal = func_001809F0((u8*)self->unk_04 + 0xB30);
        s128 point = Movement_WidenPoint(goal->x, goal->y, goal->z);
        return point;
    }
    return func_00180A00((u8*)self->unk_04 + 0xB30);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_1904d8", func_00190768);
#ifdef NON_MATCHING
// Unmatched: boolean result lifetime removes one native register copy.
s32 func_001907E0(Recovered_MovementObserver* self, s128 position) {
    s32 result = 0;
    if (func_0018E5E0(self, position)) {
        u8 inside = func_0018E680(self, position, self->unk_14) == 0;
        result = inside;
    }
    return result;
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_1904d8", func_001907E0);
s32 func_00190840(Recovered_MovementObserver* self, s32 index) {
    s32 result;
    if (self->unk_14) {
        Recovered_ActorSlotTable* table = (Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8);
        Recovered_ActorSlot* slot = ActorSlotTable_GetEntry(table, index);
        result = func_0018E680(self, *func_00178D30(slot), self->unk_14);
    } else {
        result = 1;
    }
    return result;
}
void func_001908A0(Recovered_MovementObserver* self, void* candidate) {
    u8* context = self->unk_04;
    u32 mask = 1u << M2C_FIELD(candidate, s32*, 0x380);
    void* actor = M2C_FIELD(context, void**, 0x7C);
    if (M2C_FIELD(candidate, s32*, 0x3A4) != M2C_FIELD(actor, s32*, 0x3A4) &&
        M2C_FIELD(candidate, s32*, 0x38C) == 0) {
        s32 bitSet = (M2C_FIELD(context, u32*, 0x274) & mask) == mask;
        s32 result = func_0018E680(self, M2C_FIELD(candidate, s128*, 0xA0), self->unk_14);
        if (result != bitSet) {
            if (bitSet) {
                func_00189720((u8*)self->unk_04 + 0x150, candidate);
            } else {
                func_00189700((u8*)self->unk_04 + 0x150, candidate);
            }
        }
    }
}
#ifdef NON_MATCHING
// Unmatched: two slot-index lifetimes and register allocation differ.
void func_00190958(Recovered_MovementObserver* self) {
    s32 count;
    s32 offset = 0;
    s32 slotOffset = 0x2B00;
    func_001908A0(self, D_0040F4D0 + 0x30);
    count = 15;
    do {
        u8* manager = (u8*)D_0040F4D4;
        u8* entry = manager + offset;
        void* slot = manager + slotOffset;
        count--;
        slotOffset += sizeof(Recovered_ManagedSlot);
        if (M2C_FIELD(entry, u8*, 0x2B78) && slot != self->unk_04) {
            func_001908A0(self, M2C_FIELD(entry, void**, 0x2B7C));
        }
        offset += sizeof(Recovered_ManagedSlot);
    } while (count >= 0);
}
#endif
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/movement/tu_1904d8", func_00190958);
