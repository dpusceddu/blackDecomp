#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/camera/selection_pool.h"
#include "game/actor/vector_math.h"
#include "ps2/vu0_math.h"

extern s32 func_00107D20();

extern void* D_0040F4D0;
extern const f32 D_003F49BC;
extern const f32 D_003F49C0;
void func_001398E0(Recovered_SelectionPool*, Recovered_SelectionMember*);
Recovered_SelectionMember* func_00139940(Recovered_SelectionPool*);
f32 func_00139A70(Recovered_SelectionPool*, Recovered_SelectionMember*);

static inline Recovered_SelectionMember** SelectionSlot(Recovered_SelectionPool* self, s32 index) {
    return (Recovered_SelectionMember**)((u32)self->members + (index * 4));
}

void func_00139780(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_3;
    s32 var_5;

    M2C_FIELD(arg0, s32 *, 0xC) = func_00107D20(arg1 * 4);
    var_5 = 0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    if (arg1 > 0) {
        do {
            temp_3 = var_5 * 4;
            var_5 += 1;
            M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 0) = 0;
        } while (var_5 < arg1);
    }
    M2C_FIELD(arg0, s32 *, 0) = arg2;
}

s32 SelectionPool_Clear(Recovered_SelectionPool* self) {
    s32 i = 0;
    self->count = 0;
    while (i < self->capacity) {
        self->members[i] = NULL;
        i++;
    }
    return 1;
}

s32 SelectionPool_Add(Recovered_SelectionPool* self, Recovered_SelectionMember* member) {
    s32 i;
    for (i = 0; i < self->capacity; i++) {
        if (self->members[i] == NULL) {
            if (member->pool != NULL) func_001398E0(member->pool, member);
            member->pool = self;
            self->members[i] = member;
            self->count++;
            return 1;
        }
    }
    return 0;
}

void SelectionPool_Remove(Recovered_SelectionPool* self, Recovered_SelectionMember* member) {
    s32 i;
    for (i = 0; i < self->capacity; i++) {
        if (self->members[i] == member) {
            member->pool = NULL;
            self->members[i] = NULL;
            self->count--;
            return;
        }
    }
}

Recovered_SelectionMember* SelectionPool_First(Recovered_SelectionPool* self) {
    s32 i;
    for (i = 0; i < self->capacity; i++) {
        if (self->members[i] != NULL) return self->members[i];
    }
    return NULL;
}

#ifdef NON_MATCHING
// Unmatched: final slot-address destination and operand order differ.
Recovered_SelectionMember* func_00139980(Recovered_SelectionPool* self) {
    f32 best = D_003F49BC;
    s32 bestIndex = -1;
    s32 i;
    if (self->flags == 0) return func_00139940(self);
    for (i = 0; i < self->capacity; i++) {
        Recovered_SelectionMember* member = self->members[i];
        if (member != NULL && (!(self->flags & 4) || member->active)) {
            f32 score = func_00139A70(self, member);
            if (best < score) {
                best = score;
                bestIndex = i;
            }
        }
    }
    {
        Recovered_SelectionMember* result;
        if (bestIndex != -1) {
            result = *SelectionSlot(self, bestIndex);
        } else {
            result = NULL;
        }
        return result;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_00139980);
#endif

f32 SelectionPool_Score(Recovered_SelectionPool* self, Recovered_SelectionMember* member) {
    f32 distanceScore = 0.0f;
    f32 ageScore = 0.0f;
    f32 score;
    f32 facing;
    if (self->flags & 2) distanceScore = __ee_max_s(1.0f - 50.0f / member->distance, -1.0f);
    if (self->flags & 1) {
        f32 elapsed = M2C_FIELD(D_0040F4D0, f32*, 0x20) - member->lastUse;
        ageScore = __ee_min_s(elapsed / 120.0f, 1.0f);
        if (elapsed < 0.1f) return D_003F49C0;
    }
    {
        BkVectorPS2 delta = BkVuSubXYZ(M2C_FIELD(D_0040F4D0, s128*, 0xD0), member->position);
        BkVectorPS2 weighted = BkMultiplyPS2(delta, M2C_FIELD(D_0040F4D0, s128*, 0xC0));
        score = distanceScore + ageScore;
        facing = BkSumPS2(weighted);
    }
    if (facing > 0.0f) score += 2.0f;
    return score;
}

#ifdef NON_MATCHING
const f32 D_003F49BC = -3.402823466e+38f;
#endif
const f32 D_003F49C0 = -3.402823466e+38f;
