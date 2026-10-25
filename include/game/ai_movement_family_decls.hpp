// Declarations of the Game source module "ai_movement_family" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_GAME_MODULE_AI_MOVEMENT_FAMILY_HPP
#define BLACK_GAME_MODULE_AI_MOVEMENT_FAMILY_HPP

#include "game/ai_movement.hpp"

namespace Game {

// Unmatched: ordinary build keeps the stack argument and x87 result; exact in the separate-file /GL context.
float FamilySpeed(const FamilyRef* family);

}

#endif
