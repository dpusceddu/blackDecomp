#include "ps2/vu0_quaternion.hpp"

// Partial PS2 animation transform views, not recovered original class identities.
struct Transform { BkVuVector rotation, position; };

extern "C" Transform *func_003440B8(Transform *out, const Transform *a, const Transform *b)
{
    BlackPS2::AnimationMath::Multiply(&out->rotation, &a->rotation, &b->rotation);
    BlackPS2::AnimationMath::Add(&out->position, &a->position, &b->position);
    return out;
}
