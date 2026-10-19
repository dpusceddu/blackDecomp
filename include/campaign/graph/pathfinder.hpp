// PS2 CPathFinder class view. RTTI supplies the service hierarchy; exact imported
// callers verify selected offsets. Base-field ownership and unused signatures remain UNVERIFIED.
#ifndef BLACK_CAMPAIGN_GRAPH_PATHFINDER_HPP
#define BLACK_CAMPAIGN_GRAPH_PATHFINDER_HPP
#include "kynapse/compat.hpp"
#include "campaign/graph/tables.hpp"
#include "classes/kynapse/Kaim_CPathFinder.hpp"
namespace Kaim {
struct ChildBuffers {unsigned char unknown00[12];const char*first;unsigned char unknown10[16];unsigned int count;const char*GetSecond() const __asm__("func_002E3920");const char*GetValue() const __asm__("func_002E3918");ChildBuffers*GetChild(unsigned int) const __asm__("func_002E33E0");ChildBuffers*FindBySecond(const char*) const __asm__("func_002E31E0");const char*FindThirdBySecond(const char*) const __asm__("func_002E3330");};
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
    Vec3f(){} Vec3f(float a,float b,float c):x(a),y(b),z(c){}
    Vec3f(const Vec3f&v):x(v.x),y(v.y),z(v.z){}
    Vec3f operator+(const Vec3f&v)const{return Vec3f(x+v.x,y+v.y,z+v.z);}
    Vec3f operator-(const Vec3f&v)const{return Vec3f(x-v.x,y-v.y,z-v.z);}
    Vec3f operator*(float n)const{return Vec3f(n*x,n*y,n*z);}
    Vec3f operator/(float n)const{return Vec3f(x/n,y/n,z/n);}
    Vec3f Cross(const Vec3f&v)const{return Vec3f(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x);}
    float Dot(const Vec3f&v)const{return x*v.x+y*v.y+z*v.z;}
    float DistanceTo(const Vec3f&v)const{float dz=z-v.z,dx=x-v.x,dy=y-v.y;return sqrtf(dz*dz+dx*dx+dy*dy);}
    float DistanceFrom(const Vec3f&v)const{float dz=v.z-z,dx=v.x-x,dy=v.y-y;return sqrtf(dz*dz+dx*dx+dy*dy);}
    float Squared()const __asm__("func_00389140");
    float HorizontalSquared()const __asm__("func_00393810");
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
    virtual bool NameToId(const char* name, unsigned int* id);      // slot 6
    virtual bool Convert(RouteRequest* request, int graphId, unsigned int* ordinal);   // slot 7
};

struct Heuristic {
    virtual void Slot0();
    virtual bool Estimate(Actor* actor, void* start, void* goal, void* cost);   // slot 1
};

struct ParameterTables {
    void Store(int index, Actor* user) __asm__("func_002E9868");
    void Restart(int,Actor*) __asm__("func_002E9868");
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
struct CPathFinder;
struct MoveRecord;
typedef bool (__cdecl *StopFn)(CPathFinder* follower);
typedef void (__cdecl *SubgoalFn)(CPathFinder* follower);
typedef bool (__cdecl *GuardFn)(CPathFinder* follower, const float* point);
typedef unsigned int (__cdecl *MoveFn)(CPathFinder* follower, float* output, const float* point);
typedef void* (__cdecl *CollectNodeFn)(CPathFinder* follower, const float* point, unsigned int outgoing,
                                       unsigned int incoming);

bool Kaim_TestSegment(const float* from, const float* to, void* actor, int mode, float radius);

void* __cdecl NavigationGraph_FindNearestNode(NavigationGraph* graph, const float* point, Actor* actor,
                                              float radius, unsigned int outgoing, unsigned int incoming);
unsigned int __cdecl NavigationGraph_FindNearestNodeSimple(NavigationGraph* graph, const float* point,
                                                           unsigned int outgoing, unsigned int incoming);
int __cdecl NavigationGraph_QueryNode(const float* point, Actor* actor, float radius, NavigationGraph* graph,
                                      unsigned int outgoing, unsigned int incoming);

struct MovePolicy : CObject {
    virtual ~MovePolicy();
    virtual void Slot1();
    virtual void Apply(const float* point, float* output);   // slot 2
    virtual bool Configure(ChildBuffers*);
    virtual void Update();                                   // slot 4
    virtual void Reset();                                    // slot 5
};

struct NavigationGraph;
struct AgentObject : CObject {
    virtual ~AgentObject();
    virtual void Slot1();
    virtual void SetGraph(NavigationGraph* graph);           // slot 2
};
struct ServiceObject : CObject {
    virtual ~ServiceObject();
    virtual void Slot1();
    virtual void Slot2();
    virtual void SetGraph(NavigationGraph* graph);           // slot 3
};

struct ClassInfoHandle;
struct NamedGraph : CObject {
    virtual ~NamedGraph();
    char name[0x80];
    NavigationGraph* graph;
};
struct GraphRegistry {
    unsigned char unknown00[4];
    NamedGraph** items;
    unsigned int count;
    int IdByName(const char* name);
    inline const char*NameOfGraph(NavigationGraph*g){for(unsigned int i=0;i<count;++i)if(items[i]->graph==g)return items[i]->name;return 0;}

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
    MoveRecord& operator=(const MoveRecord& other) {speed=other.speed;direction[0]=other.direction[0];direction[1]=other.direction[1];direction[2]=other.direction[2];extra[0]=other.extra[0];extra[1]=other.extra[1];extra[2]=other.extra[2];flagA=other.flagA;flagB=other.flagB;return *this;}
};

struct RouteSource {
    virtual ~RouteSource();
    virtual const void* GetType();                         // slot 1
};

struct RouteBlock : CObject {
 unsigned int slots,count;unsigned int *nodeIds,*edgeIds;Vec3f *points;WaypointGuard **guards;unsigned int capacity;int state;float length;
 RouteBlock() __asm__("func_002FB558");virtual ~RouteBlock();
 void Clear(){count=0;length=0.0f;}
 unsigned int FindNearestPoint(const float*);void SetMaxPathSize(long);
};
struct RouteTable {
    bool Build(unsigned int start, unsigned int goal, RouteBlock* route);
};

struct SpeedTable { unsigned char unknown00[4]; float speed; };            // speed at 0x04
struct RadiusHolder { unsigned char unknown00[4]; float radius; };         // radius at 0x04
struct HeightFlag { unsigned char unknown00[4]; unsigned char enabled; };  // flag at 0x04

// SN GCC2.95 puts the vptr of an unbased data class at its end. The original
// follower inherits a polymorphic base, so controller starts at 0x04.
struct CBaseService : CObject {};
struct CBrainService : CBaseService {};
struct IPathFinder : CBrainService {IPathFinder(void*) __asm__("func_002E4F58");virtual ~IPathFinder();};
// Linked ResolveRequestNode and callback matches verify the leading base and used PS2 fields.
struct CPathFinder : IPathFinder {
struct CConstraintInfo : CObject {
 unsigned int samples;float mean,deviation,scale;
 CConstraintInfo():samples(0),mean(0.0005f),deviation(0),scale(0.2f){}
 virtual ~CConstraintInfo();
 static void*operator new[](unsigned n){return Allocate(n);}static void operator delete[](void*p){D_003C87E0(p);}
};
 typedef CConstraintInfo SearchRecord;

    Controller* controller;
    void* world;
    ServiceObject** serviceList;
    unsigned int serviceCount;
    RouteSource* source;
    AgentObject** agentList;
    unsigned int unknown1c;
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
    unsigned int graphId;
    RouteBlock route;
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
    Vec3f lateralDelta;
    Vec3f target;
    Vec3f pendingTarget;
    Vec3f previous;
    Vec3f position;
    Vec3f waypointPosition;
    Vec3f predicted;
    MoveRecord cachedMove;                                 // 0x118 (0x1e bytes, padded)
    void* startNode;
    void* goalNode;
    unsigned int waypoint;
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
    unsigned char unknown199[3];
    Vec3f lastProbe;
    float segmentLength;
    SearchRecord* records;
    MovePolicy* policy;
    bool movable;
    bool restartSearch;

    CPathFinder(void*);virtual ~CPathFinder();
    virtual unsigned char Initialize(ChildBuffers*);virtual bool Configure(ChildBuffers*);virtual void Reset();virtual void* GetClassInfo();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7(); virtual void* GetCostPolicy();
    virtual bool InstallService(const void* type); virtual bool IsComplete(); virtual float RemainingDistance();virtual bool SetGraphByName(const char*);
    virtual bool SetGraph(NavigationGraph*); virtual void SetGraphType(const void* type);
    virtual Heuristic* GetHeuristic();                     // slot 15
    virtual void Stop();                                   // slot 16
    virtual bool Bind1(); virtual bool Bind2(); virtual bool Bind3(); virtual bool Bind4();
    virtual bool Bind5(); virtual bool __cdecl Deliver(MoveRecord* move); virtual bool Slot23();   // slot 22 delivers a move

    void* ResolveRequestNode(RouteRequest* request);
    bool EstimateRequestCost(void* cost, RouteRequest* start, RouteRequest* goal);
    bool RefreshSearch(bool invalidateStart, bool* changed, RouteRequest* request);
    bool ConfigureAll(struct ChildBuffers* definition);
    bool FindNextMove(MoveRecord* move, RouteRequest* request);
    __declspec(noinline) void PredictMove(const float* move);
    bool FollowPoint(const float* point, RouteRequest* request);
    bool FollowRequest(RouteRequest* request);
    bool FollowPointOnly(const float* point);
    bool IsDefaultCollector();
    void UpdateProgress();
};

void* __cdecl CPathFinder_CollectNode(CPathFinder* follower, const float* point,
                                          unsigned int outgoing, unsigned int incoming);
void* __cdecl CPathFinder_CollectNodeLoose(CPathFinder* follower, const float* point,
                                               unsigned int outgoing, unsigned int incoming);
unsigned char __cdecl CPathFinder_HasUnsupportedGround(CPathFinder* follower, const float* point);
unsigned int __cdecl CPathFinder_GenerateMove(CPathFinder* follower, float* move, const float* point);

bool __cdecl CPathFinder_TestSegment(CPathFinder* follower, const float* point);

bool __cdecl CPathFinder_ResetSegment(CPathFinder* follower, int* result);

void __cdecl CPathFinder_BeginSegment(CPathFinder* follower);

void* __cdecl CPathFinder_CollectNode(CPathFinder* follower, const float* point,
                                          unsigned int outgoing, unsigned int incoming);

void* __cdecl CPathFinder_CollectNodeLoose(CPathFinder* follower, const float* point,
                                               unsigned int outgoing, unsigned int incoming);

void* __cdecl CPathFinder_CollectNodeSimple(CPathFinder* follower, const float* point,
                                                unsigned int outgoing, unsigned int incoming);

static __forceinline void ResetChannel(ControlChannel* channel, int value, bool dirty)
{
    *(int*)&channel->value = value;
    channel->dirty = dirty;
}

// Clears the route, the pending search and the control channels.

unsigned char __cdecl CPathFinder_GenerateAvoidanceMove(CPathFinder* follower, float* output,
                                                            const float* point);

unsigned char __cdecl CPathFinder_AcceptActorSegment(CPathFinder* follower, const float* point);

struct ActionBank {
    void ClearActivation();
};

// Follows a point: samples the actor position, publishes the requested end point, computes the next move
// and delivers it unless the route is complete or delivery was suppressed.

void __cdecl CPathFinder_BeginSegment(CPathFinder* follower);

static inline float Distance(const Vec3f* a, const Vec3f* b)
{
    float dz = a->z - b->z;
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    return sqrtf(dz * dz + dx * dx + dy * dy);
}

typedef CPathFinder::CConstraintInfo SearchRecord;
extern const float kZeroFloat;

inline bool Kaim_Vec3Equal(const float*a,const float*b){bool equal=false;if(a[0]==b[0] && a[1]==b[1] && a[2]==b[2])equal=true;return equal;}

unsigned int __cdecl CPathFinder_GenerateMove(CPathFinder* owner, float* move, const float* point);

unsigned char __cdecl CPathFinder_SelectSteeringProbe(CPathFinder* follower, const float* from,
                                                          const float* to, float* output);

unsigned char __cdecl CPathFinder_GenerateSteeringMove(CPathFinder* follower, float* output, const float* point);

struct TraceResult : CObject {
    virtual ~TraceResult() {}
    float fraction;
    unsigned char payload[0x18];
};
extern void (*gTraceHook)(const float* from, const float* to, Actor* actor, TraceResult* result, int mode);

struct WorldScale { unsigned char unknown00[0xc]; float unit; };
extern WorldScale* gWorldScale;

unsigned char __cdecl CPathFinder_SelectSteeringProbe(CPathFinder* follower, const float* from,
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

unsigned char __cdecl CPathFinder_AdvanceSubgoal(CPathFinder* owner);

extern char gRouteTableType;

extern float gSideAxisX, gSideAxisY, gSideAxisZ;           // 0x297e90, 0x297e94, 0x297e98
extern int gGroundKey;
extern bool (*gGroundProbeHook)(const float* from, const float* to, Actor* actor, int mode);

unsigned char __cdecl CPathFinder_HasUnsupportedGround(CPathFinder* follower, const float* point);

inline float Vec3_DistanceSquared(const Vec3f*a,const Vec3f*b){float dz=a->z-b->z,dx=a->x-b->x,dy=a->y-b->y;return dz*dz+dx*dx+dy*dy;}
unsigned int AIRoute_FindExactPoint(RouteBlock* route, const float* point);

typedef Vec3f Vector3Value;
extern "C" float func_00389140(const Vec3f*);
inline Vector3Value Vector3_Normalize(const Vector3Value& v)
{
 float length=sqrtf(func_00389140(&v));
 Vector3Value unit;unit.x=v.x/length;unit.y=v.y/length;unit.z=v.z/length;return unit;
}
Vector3Value* Direction_Orientation(Vector3Value* output, const Vector3Value* direction);
float Degrees_WrapSigned(float degrees);
float AcosRadians(float value);
struct PointerBank {
    ControlChannel* GetItem();
};
extern PointerBank gTorsoBank;
extern int gTurnKey;
extern float gOriginX, gOriginY, gOriginZ;                 // 0x2b64f0, 0x2b64f4, 0x2b64f8
extern float gUpdateStep;
extern const float kRadiansPerDegree;

unsigned char __cdecl CPathFinder_PublishControls(CPathFinder* follower, MoveRecord* move);

extern "C" int __cdecl _stricmp(const char*, const char*);

struct AvoidanceFactory {
    unsigned char unknown00[4];
    void* (__cdecl *create)(CPathFinder* follower);
};
AvoidanceFactory* AIAvoidance_FindClass(const char* name);
void* Kaim_AllocateTagged(unsigned int size);
void* AIAvoidance_Construct(void* where, CPathFinder* follower);
struct PathAvoidance : CObject {unsigned char unknown04[0xf8];PathAvoidance(CPathFinder*) __asm__("func_00306848");static void*operator new(unsigned n){return Allocate(n);}};

struct ListenerRegistry {void Add(void (*)(float,void*),void*,Actor*) __asm__("func_002F5348");};
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
extern "C" ControlChannel *func_002DFE08(void*,const void*);
extern PointerBank gBankA, gBankB, gBankC, gBankD, gBankE; // 0x2b3b50, 0x2b4528, 0x2b4870, 0x2b3c68, 0x2b5130
bool __cdecl Kaim_AlwaysTrue(CPathFinder*, const float*);
void __cdecl CPathFinder_OnActorEvent(float, void*);
unsigned char __cdecl CPathFinder_IsAtGoal(CPathFinder* follower);

struct EdgeRef {
    int index;                                             // 0x00 (-1 marks a free slot)
    NavigationGraph* graph;
    float GetAuthoredLength() const;
};
inline float Vec3_Length(const Vec3f*a,const Vec3f*b){return Distance(a,b);}
Vec3f Vector3_SubtractValue(const Vec3f& a, const Vec3f& b);
const Vec3f* Vector3_CrossPtr(Vec3f* output, const Vec3f* a, const Vec3f* b);

unsigned char __cdecl CPathFinder_CheckSegmentCorridor(CPathFinder* follower, const float* point);

// Selects the graph registered under a name and tells the agents and services about it.

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
    float length = sqrtf(dz * dz + dx * dx + dy * dy);
    SegmentGraph* owner = graph->syntheticOwner;
    if (&graph->syntheticIndex == &owner->syntheticIndex)
        owner->syntheticLength = length;
    else if (owner->edgeLengths)
        owner->edgeLengths[graph->syntheticIndex] = length;
}

// Subgoal advance with look-ahead: starting at the nearest route point it keeps moving the subgoal along
// the route as long as the direct path to the next point is at most as expensive as going through the
// current one (up to a maximum number of steps), then settles on the furthest point reached.
unsigned int __cdecl CPathFinder_AdvanceSubgoalSmooth(CPathFinder* owner);

typedef char VerifiedPathFinderSize[sizeof(CPathFinder) == 0x1b8 ? 1 : -1];
typedef char VerifiedRouteBlockSize[sizeof(RouteBlock) == 0x28 ? 1 : -1];
typedef char VerifiedConstraintInfoSize[sizeof(CPathFinder::CConstraintInfo) == 20 ? 1 : -1];
typedef char VerifiedGraphNodeRecordSize[sizeof(NavigationGraph::NodeRecord) == 20 ? 1 : -1];

}
#endif
