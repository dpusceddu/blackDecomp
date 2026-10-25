#ifndef BLACK_ACTOR_MOTION_HPP
#define BLACK_ACTOR_MOTION_HPP
#include "game/classes/UnknownVtable_003DCA78.hpp"
#include "ps2/matrix.hpp"

namespace ActorParts {
// Provisional owner name. The exact method verifies the C4 and 2A4 view
// accesses and the 64-byte matrix return ABI, not this class's complete layout.
struct ActorMotion : Unnamed::UnknownVtable_003DCA78 {
    Ps2Math::VU0::Matrix4 GetWorldMatrix();
    Ps2Math::VU0::Matrix4 GetLocalMatrix() __asm__("func_001357B8");
};
}
#endif
