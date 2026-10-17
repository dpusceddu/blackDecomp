// Declarations of the Game source module "ai_movement_helpers" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_GAME_MODULE_AI_MOVEMENT_HELPERS_HPP
#define BLACK_GAME_MODULE_AI_MOVEMENT_HELPERS_HPP

#include "game/ai_movement.hpp"

// Shared motion helpers of the movement modes: stall recovery, route projection, continuing to the
// formation goal and completing a route destination. In the original these sit together
// (0x1a62e0-0x1a6550), apart from the mode methods that call them.
// Unmatched: callee contract (this in EAX) is reproduced only in the /GL context; hidden-pointer goal point and spilled speed differ.
namespace BlackGame {




// Unmatched: vector projection returns through a private contract; 196 vs 102 bytes.



// Publishes "no motion" first; when the actor strays from its route segment it escalates through
// a recovery timer and finally asks the mode to recover.
// Unmatched: inlined timer, grace and off-route expansions differ in register assignment.



// The alternate request has finished: accept (or just classify) it, optionally keep walking
// toward the mode's target, and publish the pending destination to the controller.
// Unmatched: Xbox takes the mode in EAX; PS2 vector moves are VU0 macro code.
void CompleteDestination(RouteMode* mode, bool resumeMotion);

}

#endif
