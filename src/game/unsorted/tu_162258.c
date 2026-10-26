#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_binding.h"

extern Recovered_ActorBindingCatalogServices* D_0040F514;

extern s32 func_00160ED8();
extern void * func_00135550();
extern s32 func_0013D8B8();
extern s32 func_001791D8();
extern void * D_0040F4D4;
extern Recovered_BoundActor* ActorBinding_FindCandidate(Recovered_ActorBinding*);
extern void func_00162420(void*);
extern void func_00162310(void*);
extern s32 func_001790D0();
extern s32 func_0013D8A0();

void ActorBinding_UpdateCurrent(Recovered_ActorBinding* self) {
    Recovered_BoundActor* actor = self->current;
    if (!actor) {
        func_00162420(self);
        return;
    }
    if (actor->invalid || actor->generation != self->generation) {
        self->current = NULL;
        self->active = 0;
    }
}

s32 func_001622A8(void) {
    func_00160ED8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_162258", func_001622C8);

void func_001622D0(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x1C) != 0) {
        func_00162310(arg0);
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x1C) = 1U;
    func_00162420(arg0);
}

void func_00162310(void *arg0) {
    s32 temp_5;
    s64 *temp_4;

    M2C_FIELD(arg0, s8 *, 0x1C) = 0;
    temp_4 = M2C_FIELD(arg0, s64 **, 0x20);
    if ((temp_4 != NULL) && (M2C_FIELD(temp_4, s32 *, 0x37C) == M2C_FIELD(arg0, s32 *, 0x2C)) && (func_00135550(temp_4) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), s32 *, 0x80) == 1)) {
        func_0013D8B8(func_00135550(M2C_FIELD(arg0, s64 **, 0x20)), arg0);
    }
    temp_5 = M2C_FIELD(arg0, s32 *, 0x30);
    if (temp_5 != -1) {
        func_001791D8(D_0040F4D4 + 0xFA8, temp_5);
        M2C_FIELD(arg0, s32 *, 0x30) = -1;
    }
    M2C_FIELD(arg0, s64 **, 0x20) = NULL;
}

Recovered_BoundActor* ActorBinding_FindCandidate(Recovered_ActorBinding* self) {
    Recovered_BoundActorCatalog* catalog = &D_0040F514->catalog;
    s32 i = 0;
    if (catalog->count > 0) {
        Recovered_BoundActor** cursor = catalog->entries;
        s64 count = catalog->count;
        do {
            Recovered_BoundActor* actor = *cursor;
            if (actor && actor->key == self->descriptor->actorKey) { return actor; }
            ++i;
            ++cursor;
        } while (i < count);
    }
    return NULL;
}

void func_00162420(void *arg0) {
    s64 *temp_2;

    temp_2 = (s64*)ActorBinding_FindCandidate(arg0);
    M2C_FIELD(arg0, s64 **, 0x24) = temp_2;
    if ((temp_2 != NULL) && (func_00135550(temp_2) != NULL) && (M2C_FIELD(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), s32 *, 0x80) == 1)) {
        M2C_FIELD(arg0, s32 *, 0x30) = func_001790D0(D_0040F4D4 + 0xFA8, arg0);
        func_0013D8A0(func_00135550(M2C_FIELD(arg0, s64 **, 0x24)), arg0);
    }
}

void func_001624A0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x24);
    M2C_FIELD(arg0, void **, 0x20) = temp_3;
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_3, s32 *, 0x37C);
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), u16 *, 0x2C);
}

#ifdef NON_MATCHING
#include "ps2/vu0_math.h"
/* C adapter of the native XYZ packing recipe; the fourth lane is unspecified. */
static inline BkVuVector BindingMakeXYZ(float x, float y, float z) {
    BkVuVector temporary, result;
    __asm__("pextlw tmpv, zsrc, xsrc" : "=r tmpv"(temporary) : "r xsrc"(x), "r zsrc"(z));
    __asm__("pextlw outv, ysrc, tmpv" : "=r outv"(result) : "r ysrc"(y), "r tmpv"(temporary));
    return result;
}
static inline BkVuVector BindingAddXYZPreserveW(BkVuVector a, BkVuVector b) {
    __asm__("vadd.xyz av, av, bv" : "+j av"(a) : "j bv"(b));
    return a;
}

// Unmatched: native packed-vector temporary spill is absent, shortening the frame.
s128 ActorBinding_SamplePosition(Recovered_ActorBinding* self) {
    s128 position = self->descriptor->position;
    f32 x = AIManager_RandomRange(D_0040F4D4, -self->descriptor->radius, self->descriptor->radius);
    f32 y = AIManager_RandomRange(D_0040F4D4, -self->descriptor->radius, self->descriptor->radius);
    f32 z = AIManager_RandomRange(D_0040F4D4, -self->descriptor->radius, self->descriptor->radius);
    s128 offset = BindingMakeXYZ(x, y, z);
    return BindingAddXYZPreserveW(position, offset);
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_162258", func_001624C0);
#endif

s32 func_00162570(s32 arg0) {
    return arg0 + 0x40;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_162258", func_00162578);
void ActorBinding_DecrementBudget(Recovered_ActorBinding* self) {
    if (self->budget != -1 && --self->budget == 0) {
        Recovered_ActorBindingMethods* methods;
        func_00162310(self);
        methods = self->methods;
        methods->complete((u8*)self + methods->adjustment, self->pending);
    }
}
