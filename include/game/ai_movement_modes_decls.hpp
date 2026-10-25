// Declarations of the Game source module "ai_movement_modes" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_GAME_MODULE_AI_MOVEMENT_MODES_HPP
#define BLACK_GAME_MODULE_AI_MOVEMENT_MODES_HPP

#include "game/ai_movement.hpp"

namespace Game {
// PS2 0x18b168; the Xbox build expands it (ai_movement.hpp) inside UpdateStallRecovery.

static inline float FrameDelta() { return gGameClock->frameDelta; }

// External locomotion and actor entry points (addresses live in the module JSON files). Their
// register contracts are private on the Xbox.
// The follower is looked up in the brain's class registry by its class key; the graph for the
// current level is the manager's entry `index`.
struct ClassRegistry;
struct ClassKey;
extern ClassKey gRouteFollowerClass;     // PS2 0x4548b8
RouteFollower* FindByClass(ClassRegistry* registry, ClassKey* key);
ClassRegistry* RegistryOf(Brain* owner); // PS2 0x13d3f0
// Distinct name from the NodeGraph view in ai_route_stages_decls.hpp.
RouteGraph* MovementGraphAt(ActionManager* manager, int index) __asm__("func_00179668");
RouteGraph* CheckedMovementGraphAt(ActionManager* manager, int index) __asm__("func_0016DD68");
void* ActorModel(Actor* actor);
long ModelKind(void* model);

static inline bool IsInVehicle(Actor* actor)
{
    return ModelKind(ActorModel(actor)) == 0x28;
}

// PS2 0x179c60; the Xbox build expands it inside RouteMode::Reset.


// PS2 0x179ef0; the Xbox build expands it (ai_movement.hpp) where requests are released.


// PS2 0x179ed0; the Xbox build expands it inside RouteMode::Recover.


// PS2 0x179cd0; the Xbox build expands it (ai_movement.hpp).


// PS2 0x179c88; the Xbox build expands the loop.


// PS2 0x191568


static inline void SetXYZ(Position4& p, float f) { PX(p) = f; PY(p) = f; PZ(p) = f; }

// PS2 0x191578; the Xbox build expands it inside every Reset.
// Both vectors are marked "unset" with -6666 in x, y and z; the PS2 builds that splat once in a
// register (two pextlw) and stores the quadword to both and to a dead stack copy.
// Unmatched: the Xbox fills three components of each vector.


// PS2 0x191b40; Xbox 0x1858c0 (owner in EAX), also expanded inside both Start functions.
// Unmatched: private EAX owner contract and packed-vector arguments.


// PS2 0x191b78; the Xbox build expands it (ai_movement.hpp) inside UpdateStallRecovery.



// Requests still being searched yield; a finished search is classified (and its route released
// when the service refused it), a completed route is accepted.
// Unmatched: mode in ESI and request expanded inline; ordinary build differs in register contract.


// PS2 0x192570; the Xbox build expands it inside RouteMode::Update.


// PS2 0x192a00; the Xbox build expands the dispatch inside RouteMode::Update.


















// Unmatched: private ESI/EAX contract and packed-vector argument copy.






// Unmatched: private register contract for the stored __m128 argument.



// Unmatched: private register contract for the stored __m128 argument.



// Maps what the navigation service answered to the next movement state.
// Unmatched: switch lowering and private register contract (request in EAX).
int ClassifyRouteResult(const RouteRequest* request);



// Unmatched: Xbox fills the vector members component by component; the PS2 splats a register.






// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.



// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.



// The four manager slots hold the actors that block a path; both comparisons are strict. A mover
// riding a vehicle or flagged unmovable never reports an obstruction.
// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.
BLACK_STDCALL_BOOL IsMovementObstructed(Controller* controller, PositionArg point, bool force);



// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.



// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.



// A finished route reports the point the follower is heading for, otherwise the request's
// destination (or the mode's own target when no finished route exists).
// Unmatched: hidden Vector4 return plus private EAX/ESI contract; follower call expanded.



// Unmatched: private register contract and inlined submit/release expansion.



// Unmatched: private register contract and inlined submit/release expansion.



// Unmatched: private register contract (mode in EDI, point in ECX).



// Unmatched: private register contract (mode in EDI) and inlined resubmit expansion.



// Planar distance to the point; the published speed follows the frame delta, capped, with a
// quadratic ease-out inside half a unit when arrival smoothing is requested.
// Unmatched: SIMD vector class on the Xbox, VU0 macro code on the PS2.
bool RequestDestinationMotion(float maximumSpeed, MovementModeBase* mode, PositionArg point,
                              bool smoothArrival, float tolerance);



// Unmatched: callee ContinueToGoal takes this in EAX; exact in the separate-file /GL context (link_group.py).



// Unmatched: private register contract for the target argument and inlined Start/vector copy.



// Reset intent, pump both requests, then run the state machine until a phase yields; the
// opportunistic motion request keeps the mover walking while a route is still being searched.
// Unmatched: inlined request pumps and step dispatch; private register contract.



// Unmatched: registry lookup and follower configuration are modeled by external helpers; component-wise fills.

}

#endif
