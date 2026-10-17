// Declarations of the Game source module "ai_route_service" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_GAME_MODULE_AI_ROUTE_SERVICE_HPP
#define BLACK_GAME_MODULE_AI_ROUTE_SERVICE_HPP

#include "game/ai_movement.hpp"

// Route-service entry points the movement modes call: queueing a navigation request, releasing and
// accepting a finished route, the route follower hand-off and the live retarget. The graph search
// stages (AdvanceRouteRequest and its handlers), the Kynapse follower itself and the vector math
// helpers stay external. Evidence per function is in the README of this directory; each function
// names its Xbox and PS2 address.
namespace BlackGame {
// Marker for "no point" (three floats), PS2 0x4514f8 (set at run time).
extern const Point3 gUnsetPoint;
// The brain whose route the follower is currently advancing (PS2 0x3bcf24).
extern Brain* gFollowedBrain;
// Guard raised while the follower runs: a byte store on the Xbox (0x2d687d), a call on the PS2.
void SetFollowBusy(int busy);
struct PointerBank;
extern PointerBank gSpeedBank;       // PS2 0x44f9f0
extern PointerBank gHeadingBank;     // PS2 0x44f7c0
PointerBankItem* GetBankItem(ActionBankOwner* owner, PointerBank* bank);
void ClearActivation(ActionBankOwner* owner);
void BeginSegment(RouteFollower* follower);
// Kynapse follower callbacks installed by SetRoutePolicy.
void AcceptActorSegment();
void AdvanceSubgoal();
void AdvanceActorSubgoal();
void CheckSegmentCorridor();
void GenerateMove();
void GenerateAvoidanceMove();
void GenerateSteeringMove();
// Hooks the PS2 build keeps out of line; the Xbox build has no code for them.
bool AcceptAvoidance(RouteMode* mode, unsigned* heading, float* speed);
void FinishFollow(RouteMode* mode);

static inline void Clear3(Point3& to) { to.x = 0; to.y = 0; to.z = 0; }
static inline bool Negligible3(float dx, float dy, float dz)
{
    return (*(unsigned*)&dx & 0x7f800000) < 0x37800001 && (*(unsigned*)&dy & 0x7f800000) < 0x37800001 &&
           (*(unsigned*)&dz & 0x7f800000) < 0x37800001;
}
static inline void LiftInto(Point3& out, PositionArg point)
{
    Vec lifted = Add3(point, Load(gRouteLift));
    Point3 raised;
    raised.x = X(lifted);
    raised.y = Y(lifted);
    raised.z = Z(lifted);
    Assign(out, raised);
}
Point3* RoutePointAddress(const RouteRequest* request, int index);



// Unmatched: PS2 vector subtraction is VU0 macro code; the Xbox passes the result through EAX.
PositionResult RoutePointAt(const RouteRequest* request, int index);



// Unmatched: private register contract (request in EAX, destination view in EDX).
void BorrowStorage(const RouteRequest* request, RouteStorage* into);



// Unmatched: PS2 distance is VU0 macro code (vsqrt); the Xbox returns it in XMM0.
float EndpointDistance(const RouteRequest* request);



// Unmatched: PS2 vector subtraction is VU0 macro code.
void SetEndpoint(RouteRequest* request, PositionArg point);



// Publishes the endpoints (and their lifted copies), clears the request's route storage and
// queues it for the navigation service.
// Unmatched: PS2 vector addition is VU0 macro code; the Xbox takes request/endpoints in EDX/EAX/EDI.
void SubmitRouteRequest(RouteRequest* request, PositionArg from, PositionArg to, Byte reuse);



// Unmatched: PS2 vector subtraction is VU0 macro code.
void SubmitRouteFromNode(RouteRequest* request, RouteNode* node, PositionArg to, Byte reuse);



// True once the follower is on the last point and it is exactly the authored endpoint.
// Unmatched: mode in EAX; the Xbox compares in a different operand order.
bool IsAtFinalRoutePoint(const RouteMode* mode);



// Resets the follower's route state and releases both requests.
// Unmatched: mode in ESI and request release expanded inline; 667 vs 657 bytes.
void ReleaseMovementRoute(RouteMode* mode);



// Hands a finished request to the follower: a direct segment publishes the tracked segment, a
// graph route installs its ordered storage, endpoints, node identities and cursor, then the
// replaced request is retired and the mode enters phase 4.
// Unmatched: Xbox takes mode/request in ESI/EDI; PS2 vector loads are VU0 macro code.
void AcceptCompletedRoute(RouteMode* mode, RouteRequest* request);



// Moves the pending alternate request to a new destination, restarting it from the active
// request's end node when it can no longer be updated in place.
// Unmatched: Xbox takes the mode in EDI and the point in ECX; PS2 vector moves are VU0 macro code.
bool RetargetLive(RouteMode* mode, PositionArg point);



// Installs the Kynapse follower callbacks of a policy: 0 ordinary subgoal progression, 1 and 2
// actor arrival progression, 2 adds dynamic avoidance; other values publish the admission
// callback only.
// Unmatched: mode in EAX, policy in ECX; branch layout differs from the PS2 and Xbox tails.
void SetRoutePolicy(RouteMode* mode, int policy);



// Runs the follower toward the active request's endpoint and reacts to what it reports:
// interruption recovers the mode, a stuck follower abandons the route, reaching the end
// completes the destination. A direct segment instead walks straight to the target with
// obstruction probes. Always yields (returns false) after one step.
// Unmatched: Xbox takes the mode in EAX and calls the follower with x87 results; PS2 vector math.
bool FollowCurrentDestination(RouteMode* mode);


// PS2 0x192560 and 0x192568: placeholders for policy the Xbox build compiles away.
bool AcceptAvoidance(RouteMode*, unsigned*, float*);

void FinishFollow(RouteMode*);

}

#endif
