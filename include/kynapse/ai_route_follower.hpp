// Declarations of the Kynapse source module "ai_route_follower" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_AI_ROUTE_FOLLOWER_HPP
#define BLACK_KYNAPSE_MODULE_AI_ROUTE_FOLLOWER_HPP
#include "kynapse/compat.hpp"

// Route following: an actor walks along a navigation graph, resolving the nodes of route requests,
// predicting and generating moves, and testing the ground ahead.

struct RouteSource;
struct NavigationGraph {
    struct NodeRecord { int id; unsigned char unknown04[0x10]; };
    unsigned char unknown00[0x0c];
    unsigned int nodeCapacity;
    unsigned char unknown10[8];
    NodeRecord* nodes;
    unsigned char unknown1c[0x0c];
    unsigned int edgeCapacity;
    unsigned char unknown2c[8];
    struct EdgeRef* edges;                                 // 0x34 (8 bytes each)
    unsigned char unknown38[0x1c];
    void* costPolicy;
    void* heuristic;
    // PS2 ResolveRequestNode checks capacity+0x0c, 20-byte nodes+0x18 and id==-1.
    void* NodeAt(unsigned int ordinal)
    {
        if (ordinal >= nodeCapacity) return 0;
        NodeRecord* node = &nodes[ordinal];
        return node->id == -1 ? 0 : node;
    }
    bool FindRoute(struct RouteBlock* route, void* start, void* goal, struct Actor* actor);
    unsigned int AdvanceTimed(struct RouteBlock* route, void* start, void* goal, struct Actor* actor,
                              unsigned int* samples, float* mean, float* deviation, float deviationScale,
                              float budget, unsigned int restart);
};

struct Vec3f {
    float x, y, z;
    void Set(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    Vec3f& operator=(const Vec3f& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

struct AuthoredValue {
    unsigned char unknown00[4];
    float value;
};

struct Actor {
    unsigned char unknown00[0x30];
    Vec3f position;
    AuthoredValue* GetAuthoredProperty(const void* key);
};

struct Controller {
    unsigned char unknown00[0x14];
    Actor* actor;
};

// A request for a route end point: a position, or an authored graph node.
struct RouteRequest {
    virtual ~RouteRequest();
    virtual const float* GetPoint();                       // slot 1
    virtual bool GetEndpoint(unsigned int* ordinal, int* graphId);   // slot 2
};

struct NodeConverter {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual bool NameToId(const char* name, int* id);      // slot 6
    virtual bool Convert(RouteRequest* request, int graphId, unsigned int* ordinal);   // slot 7
};

struct Heuristic {
    virtual void Slot0();
    virtual bool Estimate(Actor* actor, void* start, void* goal, void* cost);   // slot 1
};

struct ParameterTables {
    void Store(int index, Actor* user);
    void SelectUser(Actor* user);
    float Remaining(int index);
    bool Raise(int index, Actor* user);
    bool Consume(int index, Actor* user);
    void Accumulate(int index, Actor* user);
    int FindNameA(const char* name);
    int FindNameB(const char* name);
};
ParameterTables* GetNameTables();

struct WaypointGuard;
struct AIRouteFollower;
struct MoveRecord;
typedef bool (__cdecl *StopFn)(AIRouteFollower* follower);
typedef void (__cdecl *SubgoalFn)(AIRouteFollower* follower);
typedef bool (__cdecl *GuardFn)(AIRouteFollower* follower, const float* point);
typedef unsigned int (__cdecl *MoveFn)(AIRouteFollower* follower, float* output, const float* point);
typedef void* (__cdecl *CollectNodeFn)(AIRouteFollower* follower, const float* point, unsigned int outgoing,
                                       unsigned int incoming);

bool Kaim_TestSegment(const float* from, const float* to, void* actor, int mode, float radius);

void* __cdecl NavigationGraph_FindNearestNode(NavigationGraph* graph, const float* point, Actor* actor,
                                              float radius, unsigned int outgoing, unsigned int incoming);
unsigned int __cdecl NavigationGraph_FindNearestNodeSimple(NavigationGraph* graph, const float* point,
                                                           unsigned int outgoing, unsigned int incoming);
int __cdecl NavigationGraph_QueryNode(const float* point, Actor* actor, float radius, NavigationGraph* graph,
                                      unsigned int outgoing, unsigned int incoming);

struct MovePolicy {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Apply(const float* point, float* output);   // slot 2
    virtual void Slot3();
    virtual void Update();                                   // slot 4
    virtual void Reset();                                    // slot 5
};

struct NavigationGraph;
struct AgentObject {
    virtual ~AgentObject();
    virtual void Slot1();
    virtual void SetGraph(NavigationGraph* graph);           // slot 2
};
struct ServiceObject {
    virtual ~ServiceObject();
    virtual void Slot1();
    virtual void Slot2();
    virtual void SetGraph(NavigationGraph* graph);           // slot 3
};

struct ClassInfoHandle;
struct NamedGraph {
    virtual ~NamedGraph();
    char name[0x80];
    NavigationGraph* graph;
};
struct GraphRegistry {
    unsigned char unknown00[4];
    NamedGraph** items;
    unsigned int count;
    int IdByName(const char* name);
    void* Find(int typeId, ClassInfoHandle* wanted);
};
struct EngineHandle {
    GraphRegistry* FindByClass(ClassInfoHandle* wanted);
};
extern EngineHandle* gEngineHandle;
extern ClassInfoHandle gGraphRegistryClass;
extern ClassInfoHandle gRouteTableClass;
extern ClassInfoHandle gLooseGraphClass;

struct ControlChannel {
    unsigned char unknown00[4];
    bool dirty;
    unsigned char unknown05[3];
    float value;
    float second;
};

struct MoveRecord {
    float speed;
    float direction[3];
    float extra[3];
    bool flagA;
    bool flagB;
    MoveRecord& operator=(const MoveRecord& other);
};

struct RouteSource {
    virtual ~RouteSource();
    virtual const void* GetType();                         // slot 1
};

struct RouteBlock {
    unsigned char unknown00[8];
    unsigned int count;
    unsigned char unknown0c[0x18];
    float length;
    unsigned int FindNearestPoint(const float* point);
    void SetMaxPathSize(long size);
};
struct RouteTable {
    bool Build(unsigned int start, unsigned int goal, RouteBlock* route);
};

struct SearchRecord {
    unsigned char unknown00[4];
    unsigned int samples;
    float mean;
    float deviation;
    float scale;
};

struct SpeedTable { unsigned char unknown00[4]; float speed; };            // speed at 0x04
struct RadiusHolder { unsigned char unknown00[4]; float radius; };         // radius at 0x04
struct HeightFlag { unsigned char unknown00[4]; unsigned char enabled; };  // flag at 0x04

// SN GCC2.95 puts the vptr of an unbased data class at its end. The original
// follower inherits a polymorphic base, so controller starts at 0x04.
struct AIRouteFollowerBase { virtual void Slot0(); };
// Linked ResolveRequestNode and callback matches verify the leading base and used PS2 fields.
struct AIRouteFollower : AIRouteFollowerBase {
    Controller* controller;
    void* world;
    ServiceObject** serviceList;
    unsigned int serviceCount;
    RouteSource* source;
    AgentObject** agentList;
    unsigned char unknown1c[4];
    unsigned int agentCount;
    float distMinNewGoal;
    float heightRadiusA;
    float heightRadiusB;
    float arrivalRadius;
    float finalRadius;
    float radius;
    unsigned char unknown3c[4];
    float distSubgoalMax;
    float maxDeltaAngle;
    float maxYawSpeed;
    int unknown4cLimit;                                    // 0x4c (maximum look-ahead steps)
    float holeHeight;
    float corridorWidth;
    float widthRatio;
    float cpuPrudence;
    bool avoidCpuPeaks;
    bool updateTorsoRotate;
    bool yawSmoothing;
    unsigned char unknown63[1];
    NavigationGraph* graph;
    int graphId;
    unsigned char unknown6c[8];
    unsigned int pointCount;
    unsigned int* nodeIds;
    unsigned int* edgeIds;
    Vec3f* points;
    WaypointGuard** guards;
    unsigned int guardCapacity;
    unsigned char unknown8c[4];
    int guardCount;
    StopFn stopCondition;
    CollectNodeFn collectNode;
    GuardFn canGo;
    SubgoalFn nextSubgoal;
    GuardFn moveModeCheck;
    MoveFn simpleMove;
    MoveFn complexMove;
    bool activated;
    bool searchOk;
    bool hold;
    bool searchPaused;
    bool unknownB4;
    unsigned char unknownb5[3];
    Vec3f lastPoint;
    unsigned char unknownc4[0xc];
    Vec3f target;
    unsigned char unknownd4[0xc];
    Vec3f previous;
    Vec3f position;
    Vec3f waypointPosition;
    Vec3f predicted;
    MoveRecord cachedMove;                                 // 0x118 (0x1e bytes, padded)
    void* startNode;
    void* goalNode;
    int waypoint;
    int turnState;
    Vec3f savedTarget;
    void* savedStart;
    void* savedGoal;
    SpeedTable* speeds;
    RadiusHolder* radiusHolder;
    HeightFlag* heightFlag;
    ControlChannel* yawChannel;
    ControlChannel* turnChannel;
    ControlChannel* speedChannel;
    ControlChannel* speedChannelAlt;
    ControlChannel* verticalChannel;
    RouteTable* routeTable;
    NavigationGraph* looseGraph;
    NodeConverter* converter;
    int searchSlotIndex;
    int slotIndex;
    int goalSlotIndex;
    int turnSlotIndex;
    bool flag198;
    unsigned char unknown199[0xf];
    float segmentLength;
    SearchRecord* records;
    MovePolicy* policy;
    bool movable;
    bool restartSearch;

    virtual void Slot1(); virtual void Slot2(); virtual void Slot3(); virtual void Slot4();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7(); virtual void* GetCostPolicy();
    virtual void SetRouteType(const void* type); virtual bool IsComplete(); virtual void Slot11(); virtual void Slot12();
    virtual void Slot13(); virtual void SetGraphType(const void* type);
    virtual Heuristic* GetHeuristic();                     // slot 15
    virtual void Stop();                                   // slot 16
    virtual bool Bind1(); virtual bool Bind2(); virtual bool Bind3(); virtual bool Bind4();
    virtual bool Bind5(); virtual bool __cdecl Deliver(MoveRecord* move); virtual bool Slot23();   // slot 22 delivers a move

    void* ResolveRequestNode(RouteRequest* request);
    bool EstimateRequestCost(void* cost, RouteRequest* start, RouteRequest* goal);
    bool RefreshSearch(bool invalidateStart, bool* changed, RouteRequest* request);
    bool ConfigureAll(struct ChildBuffers* definition);
    bool FindNextMove(MoveRecord* move, RouteRequest* request);
    unsigned char Initialize(struct ChildBuffers* definition);
    __declspec(noinline) void PredictMove(const float* move);
    bool FollowPoint(const float* point, RouteRequest* request);
    bool FollowRequest(RouteRequest* request);
    bool FollowPointOnly(const float* point);
    bool IsDefaultCollector();
    void Reset();
    bool SetGraphByName(const char* name);
    bool SetGraph(NavigationGraph* newGraph);
    float RemainingDistance();
    void UpdateProgress();
};

void* __cdecl AIRouteFollower_CollectNode(AIRouteFollower* follower, const float* point,
                                          unsigned int outgoing, unsigned int incoming);
void* __cdecl AIRouteFollower_CollectNodeLoose(AIRouteFollower* follower, const float* point,
                                               unsigned int outgoing, unsigned int incoming);
unsigned char __cdecl AIRouteFollower_HasUnsupportedGround(AIRouteFollower* follower, const float* point);
unsigned int __cdecl AIRouteFollower_GenerateMove(AIRouteFollower* follower, float* move, const float* point);










bool __cdecl AIRouteFollower_TestSegment(AIRouteFollower* follower, const float* point);



bool __cdecl AIRouteFollower_ResetSegment(AIRouteFollower* follower, int* result);



void __cdecl AIRouteFollower_BeginSegment(AIRouteFollower* follower);

void* __cdecl AIRouteFollower_CollectNode(AIRouteFollower* follower, const float* point,
                                          unsigned int outgoing, unsigned int incoming);


void* __cdecl AIRouteFollower_CollectNodeLoose(AIRouteFollower* follower, const float* point,
                                               unsigned int outgoing, unsigned int incoming);





void* __cdecl AIRouteFollower_CollectNodeSimple(AIRouteFollower* follower, const float* point,
                                                unsigned int outgoing, unsigned int incoming);


static __forceinline void ResetChannel(ControlChannel* channel, int value, bool dirty)
{
    *(int*)&channel->value = value;
    channel->dirty = dirty;
}


// Unmatched: zero/channel-flag registers and actor-load hoisting differ; five copy/local variants did not improve it (229 vs 230 bytes).
// Clears the route, the pending search and the control channels.



unsigned char __cdecl AIRouteFollower_GenerateAvoidanceMove(AIRouteFollower* follower, float* output,
                                                            const float* point);



unsigned char __cdecl AIRouteFollower_AcceptActorSegment(AIRouteFollower* follower, const float* point);


struct ActionBank {
    void ClearActivation();
};


// Unmatched: transcribed from the disassembly.
// Follows a point: samples the actor position, publishes the requested end point, computes the next move
// and delivers it unless the route is complete or delivery was suppressed.






void __cdecl AIRouteFollower_BeginSegment(AIRouteFollower* follower);


static inline float Distance(const Vec3f* a, const Vec3f* b)
{
    float dz = a->z - b->z;
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return (float)sqrt(dz * dz + dx * dx + dy * dy);
}




extern const float kZeroFloat;



bool Kaim_Vec3Equal(const float* a, const float* b);


// Unmatched: the original reads the move components back from memory for each length (330 vs 354 bytes).
unsigned int __cdecl AIRouteFollower_GenerateMove(AIRouteFollower* owner, float* move, const float* point);


unsigned char __cdecl AIRouteFollower_SelectSteeringProbe(AIRouteFollower* follower, const float* from,
                                                          const float* to, float* output);


// Unmatched: normalized-component spill and retained overwritten zero stores differ; named aggregate was worse (182 vs 195 bytes).
unsigned char __cdecl AIRouteFollower_GenerateSteeringMove(AIRouteFollower* follower, float* output, const float* point);


struct TraceResult {
    virtual ~TraceResult() {}
    float fraction;
    unsigned char payload[0x18];
};
extern void (*gTraceHook)(const float* from, const float* to, Actor* actor, TraceResult* result, int mode);

struct WorldScale { unsigned char unknown00[0xc]; float unit; };
extern WorldScale* gWorldScale;


// Unmatched: float temporaries and the trace results are laid out differently (518 vs 577 bytes).
unsigned char __cdecl AIRouteFollower_SelectSteeringProbe(AIRouteFollower* follower, const float* from,
                                                          const float* to, float* output);


struct WaypointGuard {
    virtual ~WaypointGuard();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual bool Check(Actor* actor, const float* actorPosition, const float* point);   // slot 6
    virtual bool Evaluate(Actor* actor, const float* waypoint, void* world, bool* done, const float* probe);   // slot 7
    virtual bool IsBlocked(Actor* actor);                  // slot 8
    virtual bool CanContinue(Actor* actor);                // slot 9
};


unsigned char __cdecl AIRouteFollower_AdvanceSubgoal(AIRouteFollower* owner);


extern char gRouteTableType;


// Unmatched: persistent EBX zero remains absent; typed route-clear context did not change the 509 vs 501-byte body.


extern float gSideAxisX, gSideAxisY, gSideAxisZ;           // 0x297e90, 0x297e94, 0x297e98
extern int gGroundKey;
extern bool (*gGroundProbeHook)(const float* from, const float* to, Actor* actor, int mode);


// Unmatched: ground-probe aggregate lifetimes/frame differ; named travelled displacement worsened the 915-byte body.
unsigned char __cdecl AIRouteFollower_HasUnsupportedGround(AIRouteFollower* follower, const float* point);


float Vec3_DistanceSquared(const Vec3f* a, const Vec3f* b);
unsigned int AIRoute_FindExactPoint(RouteBlock* route, const float* point);


// Unmatched: PredictMove receiver/argument corrected and outlined; movement frame/branch scheduling differs (1947 vs 1936 bytes).


struct Vector3Value {
    float x, y, z;
};
Vector3Value Vector3_Normalize(const Vector3Value& v);
Vector3Value* Direction_Orientation(Vector3Value* output, const Vector3Value* direction);
float Degrees_WrapSigned(float degrees);
double AcosRadians(double value);
struct PointerBank {
    ControlChannel* GetItem();
};
extern PointerBank gTorsoBank;
extern int gTurnKey;
extern float gOriginX, gOriginY, gOriginZ;                 // 0x2b64f0, 0x2b64f4, 0x2b64f8
extern float gUpdateStep;
extern const float kRadiansPerDegree;


// Unmatched: pause channel offset and callback reloads corrected; yaw/speed branches and vector temporary lifetimes differ.
unsigned char __cdecl AIRouteFollower_PublishControls(AIRouteFollower* follower, MoveRecord* move);


struct ChildBuffers {
    ChildBuffers* FindBySecond(const char* name) const;
    const char* GetValue() const;
};
extern "C" int __cdecl _stricmp(const char*, const char*);

struct AvoidanceFactory {
    unsigned char unknown00[8];
    void* (__cdecl *create)(AIRouteFollower* follower);
};
AvoidanceFactory* AIAvoidance_FindClass(const char* name);
void* Kaim_AllocateTagged(unsigned int size);
void* AIAvoidance_Construct(void* where, AIRouteFollower* follower);

struct ListenerRegistry {};
void __stdcall Kaim_AddThirdCallback(void (__cdecl *function)(float, void*), void* data, Actor* owner);
struct ClassRegistry {
    NodeConverter* FindConverter(const void* wanted);
    ListenerRegistry* FindListeners(const void* wanted);   // same function
};
extern ClassRegistry* gClassRegistry;
extern char gRouteTypeKey;
extern char gGraphTypeKey;
extern char gConverterClass;
extern char gListenerClass2;
extern char gForwardKey, gHeightKey2, gHeightFlagKey;      // 0x2b3fb0, 0x2b3d80, 0x2b4aa0
extern PointerBank gBankA, gBankB, gBankC, gBankD, gBankE; // 0x2b3b50, 0x2b4528, 0x2b4870, 0x2b3c68, 0x2b5130
bool __cdecl Kaim_AlwaysTrue(AIRouteFollower*, const float*);
void __cdecl AIRouteFollower_OnActorEvent(float, void*);
bool __cdecl AIRouteFollower_IsAtGoal(AIRouteFollower* follower);


// Unmatched: missing defaults, capacity guard and stdcall listener registration corrected; initialization branch/scratch scheduling differs.


struct EdgeRef {
    int index;                                             // 0x00 (-1 marks a free slot)
    NavigationGraph* graph;
    float GetAuthoredLength() const;
};
float Vec3_Length(const Vec3f* a, const Vec3f* b);
Vec3f Vector3_SubtractValue(const Vec3f& a, const Vec3f& b);
const Vec3f* Vector3_CrossPtr(Vec3f* output, const Vec3f* a, const Vec3f* b);


// Unmatched: separate waypoint guards reduce the body to 407 vs 414 bytes; edge/vector scratch registers still differ.
unsigned char __cdecl AIRouteFollower_CheckSegmentCorridor(AIRouteFollower* follower, const float* point);



// Unmatched: transcribed from the decompilation.
// Selects the graph registered under a name and tells the agents and services about it.



// Unmatched: transcribed from the decompilation.


// The synthetic edge of the graph that probes are measured on: a segment set from two points, with its
// length stored where the cost policy reads it.
struct SegmentGraph {
    unsigned char unknown00[0x48];
    float* edgeLengths;
    unsigned char unknown4c[0x10];
    int syntheticIndex;
    SegmentGraph* syntheticOwner;
    unsigned char unknown64[4];
    Vec3f endPosition;
    unsigned char unknown74[8];
    Vec3f startPosition;
    unsigned char unknown88[4];
    float syntheticLength;
};

struct FloatSlot {
    void SetLength(float length);
};
float Vec3_Length(const Vec3f* a, const Vec3f* b);

struct SegmentPolicy {
    virtual ~SegmentPolicy();
    virtual void Slot1();
    virtual bool Cost(Actor* actor, void* edge, float* cost);   // slot 2
};

static __forceinline void SetProbeSegment(SegmentGraph* graph, const float* end, const float* start)
{
    graph->endPosition.x = end[0];
    graph->endPosition.y = end[1];
    graph->endPosition.z = end[2];
    graph->startPosition.x = start[0];
    graph->startPosition.y = start[1];
    graph->startPosition.z = start[2];
    float dz = graph->startPosition.z - graph->endPosition.z;
    float dx = graph->startPosition.x - graph->endPosition.x;
    float dy = graph->startPosition.y - graph->endPosition.y;
    float length = (float)sqrt(dz * dz + dx * dx + dy * dy);
    SegmentGraph* owner = graph->syntheticOwner;
    if (&graph->syntheticIndex == &owner->syntheticIndex)
        owner->syntheticLength = length;
    else if (owner->edgeLengths)
        owner->edgeLengths[graph->syntheticIndex] = length;
}


// Unmatched: original expands probe-segment helper; faithful force-inline expansion still differs in frame/scheduling (2086 vs 1837 bytes).
// Subgoal advance with look-ahead: starting at the nearest route point it keeps moving the subgoal along
// the route as long as the direct path to the next point is at most as expensive as going through the
// current one (up to a maximum number of steps), then settles on the furthest point reached.
unsigned int __cdecl AIRouteFollower_AdvanceSubgoalSmooth(AIRouteFollower* owner);


typedef char VerifiedRouteFollowerSize[sizeof(AIRouteFollower) == 0x1b8 ? 1 : -1];
typedef char VerifiedGraphNodeRecordSize[sizeof(NavigationGraph::NodeRecord) == 20 ? 1 : -1];
#endif
