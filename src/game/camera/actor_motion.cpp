#include "include_asm.h"

#include "game/camera/motion.hpp"

extern "C" {
void *func_0015D248(void *, int, int);
extern void *D_0040F4E0;
}

namespace ActorParts {

Ps2Math::VU0::Matrix4 ActorMotion::GetWorldMatrix()
{
    Ps2Math::VU0::Matrix4 result;
    if (Field_00C4() != 2) {
        result = GetLocalMatrix();
        if (Field_02A4()) {
            void *entity = func_0015D248(D_0040F4E0, *(signed char *)Field_02A4(), 0);
            Game::Vec offset = *(Game::Vec *)((char *)entity + 0x80);
            result.basis[3] = Game::Add3(result.basis[3],
                Ps2Math::VU0::TransformDirection(offset, result.basis));
        }
    }
    return result;
}
// Unmatched: 00132610 shape initialization retains four scheduling differences.
// Unmatched: 00132D98 movement update needs the original VU trigonometric/motion helpers.
// Unmatched: 001334E0 transform update needs verified angle-axis matrix composition.
// Unmatched: 00133BA0 draw update retains short iterator and scalar allocation differences.
// Unmatched: 00133FA8 hit dispatch retains container/notification ABI and control-flow differences.
// Unmatched: 001347B8 impact dispatch retains inline control-flow/allocation differences.
// Unmatched: 00134990 hit damage retains dead-argument and allocation differences.
// Unmatched: 00134C98 directional damage needs the original multi-result normalization helper.
}
