// Ported from an unpublished companion project, PS2 branches only.
#ifndef BLACK_GAME_AI_MOVEMENT_HPP
#define BLACK_GAME_AI_MOVEMENT_HPP

// Movement modes selected by the Controller (ai_action.hpp, which also owns the shared vector,
// brain, clock and manager layouts). Three concrete modes share one data
// base: RouteMode asks the navigation service for routes, DirectMode walks straight to a point and
// FormationMode follows the brain's formation goal. Layouts are partial; unknown ranges stay
// explicit. Xbox offsets below include the 0x10-byte prefix MSVC puts before the 16-byte aligned
// data base (vptr and padding); GNU stores the data base first and the vptr after it, so every
// data-base offset is 0x10 smaller on the PS2 while derived members keep their offsets.
#include "game/ai_action.hpp"
#include "game/ai_vector.hpp"

namespace Game {
// Vector values (Position4, PositionArg, ...) are shared with the Controller; see ai_action.hpp.

// Scalar square root: SN has no builtin in this configuration (sqrt.s), MSVC uses sqrtss.
static inline float SquareRoot(float value)
{ float result; __asm__("sqrt.s %0,%1" : "=f"(result) : "f"(value)); return result; }
// "Is this squared distance zero?" The PS2 build tests the exponent field instead of comparing.
static inline bool IsNegligible(float value)
{ return (*(unsigned*)&value & 0x7f800000) < 0x37800001; }
static inline float SquaredDistance3(const Vector4& a, const Position4& b)
{
    float dx = a.x - PX(b), dy = a.y - PY(b), dz = a.z - PZ(b);
    return dx * dx + dy * dy + dz * dz;
}

static inline PositionResult AsResult(const Position4& p)
{
    return Load(p);
}
// The PS2 copies the controller's vectors as aligned quadwords, the Xbox as four words.
static inline void CopyVector(Vector4& to, const Vector4& from)
{
    *(long long*)&to = *(const long long*)&from;
}
static inline Position4 Widen(const Point3& p)
{
    Position4 v;
    PX(v) = p.x; PY(v) = p.y; PZ(v) = p.z; PW(v) = 0;
    return v;
}

// A navigation graph node as the route service hands it out. `id` is -1 in a deleted slot.
struct RouteNode { unsigned int id; Point3 position; int graph; };
// The navigation graph a route search runs on, with the policies the searcher consults (installed
// from the owner's NavigationAgent before the timed search starts).
struct NodeGraph {
    Byte unknown00[0xc];
    unsigned int nodeCount;      // 0x0c
    Byte unknown10[8];
    RouteNode* nodes;            // 0x18: nodeCount entries of 0x14 bytes
    Byte unknown1c[0x38];
    unsigned int heuristic;      // 0x54
    unsigned int cost;           // 0x58
};
// Ordered route points and search bookkeeping. A request owns one; the follower keeps a copy
// of everything but the leading word while it walks the route. The arrays run in parallel:
// node index, connecting edge (followed by a -1 terminator), point and per-point edge data.
struct RouteStorage {
    Byte unknown00[4];
    NodeGraph* graph;            // 0x04
    int count;                   // 0x08
    unsigned int* nodeIds;       // 0x0c
    unsigned int* links;         // 0x10
    Point3* points;              // 0x14
    int* edgeData;               // 0x18
    int unknown1c;
    Byte field20;                // cleared when a search restarts
    Byte unknown21[3];
    float field24;               // cleared when a search restarts
};
// A pending or finished navigation query. `kind` is the service phase: 1 queued, 2-8 searching
// stages (see AdvanceRouteRequest), 9 finished with a route, 10 finished without (`result` says
// why: 1 no route, 3 search timed out). The lifted endpoints sit above the authored points by the
// route height bias (gRouteLift).
struct RouteRequest {
    Brain* owner;                // 0x00
    RouteRequest* next;          // 0x04: queue link
    int kind;                    // 0x08
    int result;                  // 0x0c
    Position4 origin;            // 0x10
    Position4 destination;       // 0x20
    RouteNode* startNode;        // 0x30
    RouteNode* endNode;          // 0x34
    Point3 originLifted;         // 0x38
    Point3 destinationLifted;    // 0x44
    RouteStorage* storage;       // 0x50
    int firstPoint;              // 0x54: index of the first point still to walk
    Byte busy;                   // 0x58: set for a direct segment that needs no graph route
    Byte unknown59[3];
    float elapsed;               // 0x5c: time spent in a paused timed search
    Byte reuse;                  // 0x60
    Byte unknown61[0xf];
    void Clear();
    void Release();
    void Resubmit(PositionArg from);
    bool UpdateDestination(PositionArg point);
    int PointCount() const;
    void Pump();
    void SkipPoint();
    void DropFinalPoint();
    void ValidateRoute();
    RouteNode* NodeAt(unsigned int ordinal) const;
};
// The PS2 expands the node lookup inline; the Xbox keeps a standalone copy (ai_route_stages.cpp).
inline RouteNode* RouteRequest::NodeAt(unsigned int ordinal) const
{
    unsigned int id = storage->nodeIds[ordinal];
    NodeGraph* graph = storage->graph;
    if (id >= graph->nodeCount) return 0;
    RouteNode* node = &graph->nodes[id];
    return node->id == 0xffffffffu ? 0 : node;
}
// The brain's navigation agent: the graph its route searches run on and the cost and heuristic
// policy handles the timed search consults. Slot 0 is the (deleting) destructor on both platforms.
// The polymorphic interface is a separate base so the vptr stays at offset 0 under GNU.
struct NavigationAgentInterface {
    virtual void Unknown0(); virtual void Unknown1(); virtual void Unknown2(); virtual void Unknown3();
    virtual void Unknown4(); virtual void Unknown5(); virtual void Unknown6(); virtual void Unknown7();
    virtual unsigned int HeuristicPolicy();      // slot 8
    virtual void Unknown9(); virtual void Unknown10(); virtual void Unknown11(); virtual void Unknown12();
    virtual void Unknown13(); virtual void Unknown14();
    virtual unsigned int CostPolicy();           // slot 15
};
struct NavigationAgent : NavigationAgentInterface {
    Byte unknown04[0x60];
    NodeGraph* graph;                            // 0x64
};
struct ActionBankOwner;
typedef void (*FollowerCallback)();
struct PointerBankItem {
    Byte unknown00[4];
    Byte valid;
    Byte unknown05[3];
    union { float value; unsigned bits; };
};
// The route follower walks a request's points for the mode (its class belongs to the Kynapse
// navigation library; only the parts the movement modes touch are named). Virtual slots are
// numbered as on the Xbox.
struct GraphPoint { Byte unknown00[0x30]; Point3 position; };
struct RouteGraph { Byte unknown00[0x14]; GraphPoint* points; };
// The PS2 table has Advance one slot earlier (slot 5; the Xbox's slot 0 is probably the deleting
// destructor, which GNU does not place there) and one more unnamed slot after it.
struct RouteFollowerInterface {
    virtual void Unknown0(); virtual void Unknown1(); virtual void Unknown2();
    virtual void Unknown3(); virtual void Unknown4();
    virtual bool Advance(const Point3* destination);
    virtual void Unknown6();
    virtual void Unknown7(); virtual void Unknown8(); virtual void Unknown9();
    virtual Byte Status();
    virtual float RemainingDistance();
    virtual void Unknown12();
    virtual void Configure(RouteGraph* graph);
};
struct RouteFollower : RouteFollowerInterface {
    RouteGraph* graph;           // 0x04
    ActionBankOwner* owner;      // 0x08
    Byte unknown0c[0x60];
    RouteStorage storage;        // 0x6c
    Byte unknown94[8];
    FollowerCallback acceptSegment;         // 0x9c: policy callbacks (see SetRoutePolicy)
    FollowerCallback advance;               // 0xa0
    FollowerCallback checkCorridor;         // 0xa4
    FollowerCallback generateMove;          // 0xa8
    FollowerCallback generateSteering;      // 0xac
    Byte idle;                   // 0xb0
    Byte active;                 // 0xb1
    Byte unknownb2[2];
    Byte atFinalPoint;           // 0xb4
    Byte unknownb5[3];
    Point3 destination;          // 0xb8
    Point3 startPosition;        // 0xc4
    Point3 endPosition;          // 0xd0
    Point3 routeEnd;             // 0xdc
    Point3 waypoint;             // 0xe8
    Point3 graphOrigin;          // 0xf4
    Point3 point100;             // 0x100
    Point3 point10c;             // 0x10c
    int unknown118;
    Point3 drift;                // 0x11c
    Byte unknown128[0x10];
    RouteNode* startNode;        // 0x138
    RouteNode* endNode;          // 0x13c
    unsigned cursor;             // 0x140
    Byte unknown144[4];
    Point3 routeEndCopy;         // 0x148
    RouteNode* startNodeCopy;    // 0x154
    RouteNode* endNodeCopy;      // 0x158
    Byte unknown15c[0x3c];
    Byte avoiding;               // 0x198
    Byte unknown199[3];
    Point3 point19c;             // 0x19c
    float unknown1a8;
    Byte unknown1ac[9];
    Byte interrupted;            // 0x1b5
    Byte unknown1b6[2];
    Byte stuck;                  // 0x1b8
};
struct MovementModeData {
    float heading;           // 0x10: published turn angle in degrees
    float speed;             // 0x14: published speed
    Byte stopped;            // 0x18
    Byte unknown19[7];
    Position4 target;        // 0x20
    Position4 pending;       // 0x30
    int state;               // 0x40
    Brain* brain;            // 0x44
    Byte retargeted;         // 0x48
    Byte unknown49[3];
    float distance;          // 0x4c: straight-line distance to the target when it was set
    ActionTimer stallTimer;  // 0x50
    ActionTimer resumeTimer; // 0x54
    float horizontal;        // 0x58: planar actor-to-target distance
    float height;            // 0x5c: signed vertical offset
    Byte bound;              // 0x60
    Byte unknown61[0xf];
    Position4 from;          // 0x70
    Position4 to;            // 0x80
};

// Slots 0-7 belong to every mode; RouteMode adds Bind.
struct MovementModeBase : MovementModeData {
    virtual bool Reset() = 0;
    virtual void Update() = 0;
    virtual void Start(PositionArg point) = 0;
    virtual void Retarget(PositionArg point);
    virtual bool UpdateTarget(PositionArg point);
    virtual PositionResult GetTarget() const;
    virtual bool Recover();
    virtual void Stop();
    bool ResetBase();
    void BindBase(Brain* owner);
    void SetDestination(PositionArg point);
    void SetSegment(PositionArg start, PositionArg end);
    void UpdateDestinationDistances();
    void UpdateStallRecovery();
    bool IsOffRoute() const;
    bool MoveToRouteProjection();
};
// The original keeps these out of line in every caller, also under whole-program optimization.
#define BLACK_NOINLINE
struct DirectMode : MovementModeBase {
    virtual bool Reset();
    virtual void Update();
    virtual void Start(PositionArg point);
    virtual bool UpdateTarget(PositionArg point);
};
struct FormationMode : MovementModeBase {
    virtual bool Reset();
    virtual void Update();
    virtual void Start(PositionArg point);
    BLACK_NOINLINE void ContinueToGoal();
};
struct RouteMode : MovementModeBase {
    RouteFollower* follower;     // 0x90
    Byte resubmit;               // 0x94: alternate request pending cancellation
    Byte arrived;                // 0x95
    Byte unknown96[2];
    int lastRoute;               // 0x98
    Byte unknown9c[4];
    RouteRequest requests[2];    // 0xa0 and 0x110
    RouteRequest* active;        // 0x180
    RouteRequest* alternate;     // 0x184
    int policy;                  // 0x188
    virtual bool Reset();
    virtual void Update();
    virtual void Start(PositionArg point);
    virtual void Retarget(PositionArg point);
    virtual bool UpdateTarget(PositionArg point);
    virtual PositionResult GetTarget() const;
    virtual bool Recover();
    virtual void Stop();
    virtual void Bind(Brain* owner);
    bool StepPhase();
    bool ResolveCurrent();
    bool ResolveSubmitted();
};

int ClassifyRouteResult(const RouteRequest* request);
// Locomotion math and the formation goal (the vector helpers keep private register contracts).
PositionArg FormationGoalPoint(FormationGoal* formation);
float PlanarSegmentDistance(const MovementModeBase* mode, PositionArg start, PositionArg end);
PositionResult ProjectOntoSegment(const MovementModeBase* mode, PositionArg start, PositionArg end);
float SignedAngleDegrees(float dx, float dz);
// A request in these phases is still being searched (see RouteRequest::kind).
inline bool IsSearching(int kind) { return (unsigned)(kind - 2) < 4 || kind == 7 || kind == 8 || kind == 6; }

static inline void Assign(Point3& to, const Point3& from) { to.x = from.x; to.y = from.y; to.z = from.z; }
// The PS2 reaches a route point through an out-of-line address helper (ai_route_service.cpp); the
// Xbox indexes the array in place.
Point3* RoutePointAddress(const RouteRequest* request, int index);
static inline const Point3& RoutePoint(const RouteRequest* request, int index)
{ return *RoutePointAddress(request, index); }
// Shared with the route stages (ai_route_stages.cpp).
extern const Vector4 gRouteLift;      // PS2 0x414dc0: (0, 0.8, 0, 0)
// A route point lowered by the lift (the authored point the request was made for).
static inline Position4 Unlifted(const Point3& point)
{
    Position4 v;
    PX(v) = point.x - gRouteLift.x;
    PY(v) = point.y - gRouteLift.y;
    PZ(v) = point.z - gRouteLift.z;
    PW(v) = 0 - gRouteLift.w;
    return v;
}
// Route service (ai_route_service.cpp, ai_route_stages.cpp).
void ReleaseMovementRoute(RouteMode* mode);
void SubmitRouteRequest(RouteRequest* request, PositionArg from, PositionArg to, Byte reuse);
void SubmitRouteFromNode(RouteRequest* request, RouteNode* node, PositionArg to, Byte reuse);
bool AdvanceRouteRequest(RouteRequest* request);
bool FollowCurrentDestination(RouteMode* mode);
void AcceptCompletedRoute(RouteMode* mode, RouteRequest* request);
void JoinCompletedRoute(RouteMode* mode, RouteRequest* alternate);
void CompleteDestination(RouteMode* mode, bool resumeMotion);
bool IsAtFinalRoutePoint(const RouteMode* mode);
bool RetargetLive(RouteMode* mode, PositionArg point);
void SetRoutePolicy(RouteMode* mode, int policy);
PositionResult RoutePointAt(const RouteRequest* request, int index);
Point3* RoutePointAddress(const RouteRequest* request, int index);
void BorrowStorage(const RouteRequest* request, RouteStorage* into);
float EndpointDistance(const RouteRequest* request);
void SetEndpoint(RouteRequest* request, PositionArg point);
// Parameter order recovered from both platforms: floats take f12/f13 and the integer-class parameters
// follow a0..a2 on the PS2, while the Xbox pushes (speed, smoothArrival, tolerance) and keeps the mode
// and the point in registers.
bool RequestDestinationMotion(float maximumSpeed, MovementModeBase* mode, PositionArg point,
                              bool smoothArrival, float tolerance);
float FamilySpeed(const FamilyRef* family);
}
#endif
