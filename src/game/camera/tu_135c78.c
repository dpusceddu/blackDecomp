#include "include_asm.h"
#include "game/actor/control_view.h"
#include "ps2/vu0_lowering.h"

extern void func_00143590(void*, s32, s32);
extern s128 func_0025D8E0(void*);
extern s128 func_00135D30(Recovered_ManagedActor*);

s32 func_00135C78(Recovered_ManagedActor* self, s32 index, s32 value, s32 flags) {
    func_00143590(Actor_IndexedControls(self)[index], value, flags & 0xFF);
    self->controlsChanged = 1;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_135c78", func_00135CC0);

s32 func_00135CC8(Recovered_ManagedActor* self) {
    BkVuVector axis = self->transform.unk_20;
    BkVuVector direction = func_00135D30(self);
    BkVuVector product = BkVuMulXYZ(axis, direction);
    BkVuVector one = BkVuOneX();
    return __ee_vu_read_x(BkVuSumXYZ(product, one)) < 0.0f;
}

#ifdef NON_MATCHING
/* The native exponent comparison classifies tiny squared lengths. */
static inline s32 ActorSquaredLengthIsTiny(f32 value) {
    u32 word;
    __asm__("mfc1 %0, %1" : "=r"(word) : "f"(value));
    return (word & 0x7F800000U) <= 0x37800000U;
}
static inline BkVuVector ActorScaleXYZPreserveW(BkVuVector value, BkVuVector scalar) {
    __asm__("vmulx.xyz valuev, valuev, scalarvx" : "+j valuev"(value) : "j scalarv"(scalar));
    return value;
}

static inline BkVuVector ActorFloatVector(f32 value) {
    s32 word;
    BkVuVector result;
    __asm__("mfc1 %0, %1" : "=r"(word) : "f"(value));
    __asm__("qmtc2.ni wordv, resultv" : "=j resultv"(result) : "r wordv"(word));
    return result;
}
static inline s128 ActorVectorWords(BkVuVector value) {
    s128 words;
    __asm__("qmfc2.ni wordsv, valuev" : "=r wordsv"(words) : "j valuev"(value));
    return words;
}
// Unmatched: exponent-guard temporaries occupy different GPRs.
s128 func_00135D30(Recovered_ManagedActor* self) {
    BkVuVector direction;
    if (((Recovered_ActorBodyState*)self->body)->vectorActive) {
        BkVuVector one;
        f32 squared;
        s32 nearZero;
        direction = func_0025D8E0(self->body);
        one = BkVuOneX();
        squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(direction, direction), one));
        nearZero = ActorSquaredLengthIsTiny(squared);
        if (!nearZero) {
            direction = ActorScaleXYZPreserveW(direction, ActorFloatVector(1.0f / __ee_sqrt_s(squared)));
        } else {
            direction = self->managedSlot->unk_50;
        }
    } else {
        direction = self->managedSlot->unk_50;
    }
    return ActorVectorWords(direction);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_135c78", func_00135D30);
#endif

static inline s32 ActorAllowsVectorEvent(Recovered_ManagedActor* self) {
    return self->invalid != 2;
}
void func_00135DD8(Recovered_ManagedActor* self, s32 kind, s128 payload, f32 weight) {
    if (ActorAllowsVectorEvent(self) && self->unk_C4 == 1) {
        Recovered_ManagedSlot* slot = self->managedSlot;
        if (slot != NULL) {
            struct Recovered_ManagedSlotDispatch* table = slot->dispatch84;
            table->vectorEvent((u8*)slot + table->vectorEventAdjustment, kind, payload, weight, 0);
        }
    }
}

void func_00135E28(Recovered_ManagedActor* self, s32 mode) {
    s32 current = self->unk_3A0;
    if (current != 3) {
        if ((u32)(mode - 2) < 2U) {
            self->unk_3A0 = 2;
            return;
        }
        if (current == 0 && mode == 1) self->unk_3A0 = mode;
    }
}

void func_00135E68(Recovered_ManagedActor* self, Recovered_ManagedActor* actor) {
    if (actor->unk_C4 == 2) self->unk_3A0 = 3;
    else if (actor->groupKey == 0) self->unk_3A0 = 1;
    else self->unk_3A0 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_135c78", func_00135EA0);

void func_00135EA8(Recovered_ManagedActor* self, f32 first, f32 second) {
    if (!self->unk_3B7) {
        self->unk_310 = first;
        self->unk_314 = second;
        self->unk_3B5 = 1;
        self->unk_3B4 = 0;
    }
}
