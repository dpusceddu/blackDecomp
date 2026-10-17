// Declarations of the Game source module "ai_route_stages" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_GAME_MODULE_AI_ROUTE_STAGES_HPP
#define BLACK_GAME_MODULE_AI_ROUTE_STAGES_HPP

#include "game/ai_movement.hpp"

// The staged route search behind a RouteRequest: AdvanceRouteRequest steps a request through its
// kind (see RouteRequest) and each stage returns whether the caller should step again at once.
// Stages 2-4 pick endpoint graph nodes (a local probe first, then node searches around the two
// endpoints), 5 runs the timed graph search, 6-8 trim the found route against the endpoints and
// 9/10 are the finished states. JoinCompletedRoute splices a freshly finished route onto the one
// a mode is following. Evidence per function is in the README of this directory; each function
// names its Xbox and PS2 address. On the Xbox the stages are LTCG-private functions (request in
// EDI/ESI/EBX); the PS2 passes the request as an ordinary argument.
namespace BlackGame {
// The PS2 re-reads the manager pointer after every store through a request, as it would for a
// member of an aggregate rather than a plain global pointer; the handle reproduces that (it sits
// at the address of gActionManager).
struct ManagerHandle { ActionManager* manager; };
extern ManagerHandle gManager;                    // PS2 0x40f4d4
static inline ActionManager* Manager() { return gManager.manager; }
// Navigation service entry points the stages call.
void ResetSearchStatistics();                     // PS2 0x174110
void RemoveFirstPoint(RouteRequest* request);     // PS2 0x17a9f8
// The graph searches (PS2 0x2ee078 / 0x2ed530, Xbox 0x5c0f0 / 0x5bb10): an untimed search that returns
// whether a route was found, and the time-sliced search that returns 0 failed, 1 found, 2 paused. The
// authored budget is 2 and the deviation scale 5.
int FindRoute(NodeGraph* graph, RouteStorage* route, RouteNode* start, RouteNode* goal, ActorMovement* context);
int AdvanceTimed(NodeGraph* graph, RouteStorage* route, RouteNode* start, RouteNode* goal, ActorMovement* context,
                 unsigned int* samples, float* mean, float* deviation, float deviationScale, float budget,
                 unsigned int restart);
int AdvancePathSearch(RouteStorage* storage, RouteNode* start, RouteNode* goal, ActorMovement* movement);
// True when a straight probe between the two points is clear for the controller (PS2 0x182bc8,
// Xbox 0x1af250).
bool CheckLocalRoute(Controller* controller, PositionArg from, PositionArg to);
// Connectivity query between two nodes for a model family (PS2 0x28b638, Xbox 0xb3ed0).
BLACK_STDCALL_BOOL TestFamilyRoute(NodeConnectivity* connectivity, RouteNode* from, RouteNode* to,
                                   long family, unsigned int mask);
void AppendNode(RouteRequest* request, RouteNode* node);                 // PS2 0x17ab40, Xbox 0x18ed60
void RemoveLoops(RouteRequest* request, int last, int first);            // PS2 0x17af20, Xbox 0x187ce0
void* ActorModel(Actor* actor);
long ModelKind(void* model);
// The model of an actor, and its kind (the model family the connectivity query is made for).
typedef void* ModelRef;
static inline ModelRef ModelOf(Actor* actor) { return ActorModel(actor); }
static inline long FamilyOf(ModelRef model) { return ModelKind(model); }
// Point of the route as the stages compare it: lowered by the route lift.
static inline Vec UnliftedPoint(const Point3& point) { return Sub3(WidenVec(point), Load(gRouteLift)); }

// PS2 0x17a980; the Xbox build expands it.


// PS2 0x17a990; the Xbox build expands it.
// Drops the final route point and terminates the link list there.


// PS2 0x179fd0; the Xbox compiler removes the empty loop.
// Empty in the shipped build: it walks the found nodes (a debug check whose body was compiled out).
// Unmatched: the assembler's loop padding gives one nop more than the original (7 vs 6 loop words).



// Probe geometry (Xbox 0x2ad3f0 / 0x2ad400 / 0x2af570, PS2 0x414e00 / 0x414e10 / 0x4432c0): the clearance
// volume sits 1.1 above the endpoints; the occlusion segment starts 0.3 above the target
// (up * 0.6 * 0.5) and drops 0.6.
extern const Vector4 gProbeRaise;
extern const Vector4 gProbeDrop;
extern const Vector4 gUpVector;
// Collision queries the probe makes: a swept volume between two points, and an occlusion segment
// (PS2 0x175fa0 and 0x175f50).
int IsVolumeBlocked(ProbeWorld* world, PositionArg a, PositionArg b, int mask, float radius);
bool IsSegmentOccluded(ProbeWorld* world, PositionArg start, PositionArg end, int mask, Actor* ignore, int flags);

// Whether a straight local route between the two points is clear for the controller's actor: a
// near-zero route always is, one beyond 20 m never is, otherwise the swept volume must be free and
// the segment just above the target must not be occluded.
// Unmatched: Xbox from in EAX and to in ESI with the controller on the stack (reproduced only under
// /GL; the collision callees keep private contracts); PS2 vector math.
bool CheckLocalRoute(Controller* controller, PositionArg from, PositionArg to);


// Node search stages. The candidates around the origin are collected once (PS2 0x17b530, Xbox 0x18ebe0),
// then tested one per step against the collision world; the first that has room becomes the result.
void CollectCandidates(NodeSearch* search, PositionArg origin);
NodeGraph* GraphAt(ActionManager* manager, int level);     // PS2 0x179668
static inline NodeGraph* SearchGraph() { return GraphAt(Manager(), 1); }

// A candidate node is usable when a swept volume of radius 0.35 from the lifted search origin to the
// node point is free.
// Unmatched: Xbox private register contract and the volume query's private callee contract.


// Steps the node search: the first call gathers the candidates (none: done without a node); each
// call then tests the next one. Finished (true) with the first usable node, or with the nearest
// candidate when none was usable.
// Unmatched: Xbox search in ESI and private callee contracts; PS2 candidate/graph helpers.


// Statuses of the searches (0 failed, 1 found, 2 paused) as the table the originals map through
// (PS2 0x3f6250).
extern const int gSearchStatus[3];
extern unsigned int gSearchSteps;    // PS2 0x3bcf08
extern float gSearchTime;            // PS2 0x3bcf0c
extern float gSearchBudget;          // PS2 0x3bcf10
extern Byte gSearchRestart;          // PS2 0x40d9c4: global pointer relative in the original (not reproduced)

// One step of the graph search for a request's route: a restart clears the route first; identical
// endpoints use the untimed search, any other pair the time-sliced one (a restart is consumed once the
// timed step ran). Results map through the status table.
// Unmatched: Xbox route in EAX, start in ESI, goal in ECX and context in EDI (private contract); PS2
// reaches the restart flag through the global pointer (small data), which -G0 builds cannot select.
int AdvancePathSearch(RouteStorage* storage, RouteNode* start, RouteNode* goal, ActorMovement* movement);


// Stage 1: only the head of the queue may start searching. A reusable request goes straight to
// the local probe; otherwise the node search starts at the origin, or at the destination when the
// start node is already known.
// Unmatched (Xbox only): the request arrives in EDX and the contract is reproduced under /GL, but the
// original pushes EBX before the head comparison while the optimizer shrink-wraps it into the
// "start" path (reading the flag first moves the push but hoists the load, 24 bytes).
bool BeginQueuedRoute(RouteRequest* request);


// Stage 2: endpoints that are close (under 2 m of height, under 10 m planar) are probed directly;
// a clear probe finishes the request as a direct segment, otherwise the origin node search starts.
// Failing the probe yields (returns false) and every other path steps again at once.
// Unmatched: Xbox request in EDI and packed-vector locals; PS2 vector math.
bool TryDirectRoute(RouteRequest* request);


// Stage 3: waits for the node search at the origin; a node ends the stage by starting the search
// at the destination, none fails the request (result 1).
// Unmatched: Xbox request in EDI (private contract).
bool CollectRouteStart(RouteRequest* request);


// Stage 4: waits for the destination node, tests the two nodes for connectivity for the actor's
// model family and then hands the request to the timed search with the owner's graph and policies.
// Unmatched: Xbox request in EDI (private contract).
bool CollectRouteGoal(RouteRequest* request);


// Stage 5: advances the timed graph search. Found: validate and trim next; failed: result 1; paused
// searches accumulate frame time and fail with result 3 after 5 seconds. Only success steps again.
// Unmatched: Xbox request in EBX (private contract).
bool RunTimedRouteSearch(RouteRequest* request);


// Stage 6: when the first unconsumed route point coincides with the origin (within 0.1 per axis,
// against the unlifted point) it is skipped; always continues to the end compression.
// Unmatched: Xbox request in ESI with packed-vector temporaries; PS2 vector math.
bool CompressRouteStart(RouteRequest* request);


// Stage 7: probes the controller's local route from the origin to the next stored point (unlifted);
// finishes the request, and consumes that point when the probe is clear.
// Unmatched: Xbox request in EDI with packed-vector temporaries; PS2 vector math.
bool CheckFinalRouteLeg(RouteRequest* request);


// Stage 8: drops the final point when it coincides with the destination (within 0.1 per axis), then
// either runs the final leg check while unconsumed points remain or finishes.
// Unmatched: Xbox request in ESI with packed-vector temporaries; PS2 vector math.
bool CompressRouteEnd(RouteRequest* request);


// Steps a request through its stage; false means wait until the next update. Kinds 0, 9 and 10
// have nothing to do.
// Unmatched: Xbox request in EAX and the stages are private callees (reproduced only under /GL).
bool AdvanceRouteRequest(RouteRequest* request);


// Drops route points the follower already passed (keeping at least two) and republishes the
// follower's current waypoint.
// Unmatched: Xbox mode in ESI (private contract).
void TrimConsumedRoutePoints(RouteMode* mode);


// The PS2 loop below keeps the deleted-slot marker in a register (xor) instead of folding it into
// the comparison, as it would for a variable initialized before the loop.
static inline RouteNode* NodeWith(const RouteRequest* request, unsigned int ordinal, unsigned int deleted)
{
    unsigned int id = request->storage->nodeIds[ordinal];
    NodeGraph* graph = request->storage->graph;
    if (id >= graph->nodeCount) return 0;
    RouteNode* node = &graph->nodes[id];
    return node->id == deleted ? 0 : node;
}

// Splices the freshly finished route of `next` onto the route the mode is following when both
// meet at the same graph node: consumed points go, the nodes of the new route are appended (within
// 50 points), loops are removed and the follower's endpoints, storage and the mode's distance are
// republished.
// Unmatched: Xbox mode in EBX (private contract); PS2 vector math.
void JoinCompletedRoute(RouteMode* mode, RouteRequest* next);

}

#endif
