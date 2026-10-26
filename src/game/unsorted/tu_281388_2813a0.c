#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/resource_pool.hpp"

extern s32 func_00281388();

void func_002813A0(void *arg0) {
    func_00281388();
    M2C_FIELD(arg0, s32 *, 0x10) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

#ifdef NON_MATCHING
// Unmatched: O1 float temporary allocation and load scheduling differ.
void FloatPairBlend_Update(Recovered_FloatPairBlend* blend, Recovered_FloatPair* output, float elapsed) {
    if (0.0f <= blend->remaining && 0.0f < blend->duration) {
        float remainingFraction = blend->remaining / blend->duration;
        Recovered_FloatPair* target = blend->target;
        float x = blend->value.x;
        float targetX = target->x;
        float fraction = 1.0f - remainingFraction;
        float y;
        x += (targetX - x) * fraction;
        output->x = x;
        x = target->y;
        y = blend->value.y;
        y += (x - y) * fraction;
        output->y = y;
        blend->remaining -= elapsed;
    } else if (blend->target) {
        *output = *blend->target;
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2813a0", func_002813D0);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2813a0", func_00281478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2813a0", func_00281620);
