#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0018BFE8(void*, s32, s128, s32);

#include "game/movement_history.h"

extern void* D_0040F4D0;
extern s128 D_004432A0;
extern void func_0013DA60(void*);
extern void func_001855F8(Recovered_MovementHistory*, s128, s32, f32);
extern void func_00185538(Recovered_MovementHistory*, s32, s32, s128, s32);
extern s32 func_00185708(Recovered_MovementHistory*);
extern void func_00185798(Recovered_MovementHistory*);
extern void func_00185870(s32*, s32, s128, s32);
extern s32* func_00185CB0(s32*, s32, s32);
extern s32 func_00188F10(void*);
extern s32 func_0018AB08(void*);
extern void* func_00181EE8(void*);
extern s32 func_001735E0(f32*);
extern s32 func_00173610(f32*);

extern s32 func_00181B08();
extern s32 func_00173FB8(s32*, s32);

/* Opaque owner storage may alias the clock handle; retain its fresh read. */
void func_001854B8(void* self) {
    s128 point;
    if (M2C_FIELD(self, s32*, 0x64) >= 2) func_0013DA60(M2C_FIELD(self, void**, 0));
    point = D_004432A0;
    M2C_FIELD(self, f32*, 0x40) -= M2C_FIELD(D_0040F4D0, f32*, 0x1C);
    func_001855F8(self, point, 0, -M2C_FIELD(D_0040F4D0, f32*, 0x1C));
}

void func_00185530(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x68) = arg1;
}

void func_00185538(Recovered_MovementHistory* self, s32 state, s32 quiet, s128 point, s32 value) {
    s32 next, changed, increasing;
    self->amount = self->resetValues[state];
    func_00185798(self);
    next = func_00185708(self);
    changed = next != self->state;
    increasing = self->state < next;
    if (!quiet) func_00185CB0((s32*)self, self->state, next);
    self->state = next;
    if (!quiet && changed) func_00185870((s32*)self, increasing, point, value);
}
void func_001855F8(Recovered_MovementHistory* self, s128 point, s32 value, f32 delta) {
    s32 next, increasing, changed;
    self->amount += delta;
    func_00185798(self);
    next = func_00185708(self);
    increasing = self->state < next;
    changed = next != self->state;
    func_00185CB0((s32*)self, self->state, next);
    self->state = next;
    if (increasing) self->amount = self->resetValues[next];
    if (changed) func_00185870((s32*)self, increasing, point, value);
}
void func_001856B0(Recovered_MovementHistory* self, s32 requested) {
    s32 state = requested != 0;
    func_00185530(self, state);
    func_00185538(self, state, 1, D_004432A0, 0);
}
s32 func_00185708(Recovered_MovementHistory* self) {
    s32 next = 0;
    s32 state = 3;
    for (; state > 0; --state) {
        if (self->amount > self->thresholds[state - 1]) {
            next = state;
            break;
        }
    }
    if (self->state < next) self->amount = self->resetValues[next];
    M2C_FIELD(self->owner, u8*, 0x3A) = self->state != 0;
    return next;
}
void func_00185798(Recovered_MovementHistory* self) {
    s32 state = 0;
    if (func_00188F10((u8*)self->owner + 0x150)) state = 1;
    if (func_00188F10((u8*)self->owner + 0x150)) {
        if (func_0018AB08((u8*)self->owner + 0x150)) state = 2;
    }
    if (state < self->requestedState) {
        state = self->requestedState;
        if (state >= 2) self->requestedState = 1;
    }
    if (state < M2C_FIELD(func_00181EE8((u8*)self->owner + 0xEC0), s32*, 0x84))
        state = M2C_FIELD(func_00181EE8((u8*)self->owner + 0xEC0), s32*, 0x84);
    self->amount = __ee_min_s(__ee_max_s(self->amount, self->resetValues[state]), self->thresholds[3]);
}

void func_00185870(s32 *arg0, s32 increasing, s128 point, s32 value) {
    u8 sp[24];
    func_0018BFE8(sp, increasing, point, value);
    func_00181B08(*arg0 + 0xEC0, sp);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_001858A8);
#ifdef NON_MATCHING
#include "ps2/vu0_lowering.h"
// Unmatched: native vector transport and cache-loop allocation have not been matched.
s32 func_00185A70(Recovered_MovementHistory* self, s128 point, f32 minimumDistanceSquared, f32 afterTime) {
    s32 selected = -1;
    f32 closest = -1.0f;
    s32 i;
    BkVuVector one = BkVuOneX();
    for (i = 0; i < 5; ++i) {
        Recovered_MovementSample* sample = &self->samples[i];
        if (sample->id != -1 && (afterTime <= 0.0f || afterTime < sample->timestamp)) {
            BkVuVector delta = BkVuSubXYZ(sample->point, point);
            f32 distanceSquared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
            if (minimumDistanceSquared <= 0.0f || minimumDistanceSquared < distanceSquared) {
                if (selected == -1 || distanceSquared < closest) {
                    closest = distanceSquared;
                    selected = i;
                }
            }
        }
    }
    return selected == -1 ? -1 : self->samples[selected].id;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185A70);
#endif


s32 func_00185B50(Recovered_MovementHistory* self, s32 id) {
    s32 i;
    for (i = 0; i < 5; ++i) {
        if (self->samples[i].id == id) return self->samples[i].value;
    }
    return 0;
}
void func_00185B80(Recovered_MovementHistory* self, s32 id) {
    s32 i;
    for (i = 0; i < 5; ++i) {
        if (self->samples[i].id == id) self->samples[i].id = -1;
    }
}
#ifdef NON_MATCHING
// Unmatched: loop peeling and cursor/selection lifetimes differ.
s32 func_00185BA8(Recovered_MovementHistory* self) {
    f32 oldest = M2C_FIELD(D_0040F4D0, f32*, 0x20) + 1.0f;
    s32 selected = -1;
    s32 i;
    for (i = 0; i < 5; ++i) {
        if (self->samples[i].id == -1) {
            selected = i;
            break;
        }
        if (self->samples[i].timestamp <= oldest) {
            oldest = self->samples[i].timestamp;
            selected = i;
        }
    }
    self->nextSampleId += 1;
    self->samples[selected].id = self->nextSampleId;
    return selected;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_1854b8", func_00185BA8);
#endif

s32 func_00185C38(Recovered_MovementHistory* self, s32 id) {
    return func_00173FB8(&self->mask, id);
}

s32 func_00185C58(Recovered_MovementHistory* self) {
    s32 inactive = 0;
    if (!func_001735E0(&self->timer) || !func_00173610(&self->timer)) inactive = 1;
    return inactive;
}

#include "ps2/recovered_types.h"
extern s32 * func_00173640(f32 *, f32);
extern s32 func_00173690(f32 *);

s32 * func_00185CB0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 var_2;

    if (arg1 < 2) {
        var_2 = arg2 < 2;
        if (var_2 == 0) {
            var_2 = func_00173640((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)), 1.0f);
        }
    } else {
        var_2 = arg2 < 2;
        if (var_2 != 0) {
            var_2 = func_00173690((f32 *) ((s32 *) (((s8 *) arg0) + 0x114)));
        }
    }
    return (s32 *) var_2;
}
