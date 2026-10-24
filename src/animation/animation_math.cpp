#include "include_asm.h"

#include "ps2/vu0_quaternion.hpp"

// Partial PS2 animation transform views, not recovered original class identities.
struct Transform { BkVuVector rotation, position; };

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343FC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00343FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00344008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00344020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00344050);

extern "C" Transform *func_003440B8(Transform *out, const Transform *a, const Transform *b)
{
    BlackPS2::AnimationMath::Multiply(&out->rotation, &a->rotation, &b->rotation);
    BlackPS2::AnimationMath::Add(&out->position, &a->position, &b->position);
    return out;
}
