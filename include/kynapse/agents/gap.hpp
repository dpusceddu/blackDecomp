#ifndef BLACK_CONTEXT_BEHAVIORS_GAP_HPP
#define BLACK_CONTEXT_BEHAVIORS_GAP_HPP

#include "kynapse/agents/repulsor.hpp"

// Partial PS2 models. Exact stalled-progress and candidate-cost methods verify their
// accessed fields; unused layout, allocation and virtual signatures remain unverified.

namespace KaimAvoidance {
struct GapObject {
    virtual ~GapObject() {}
    static void* operator new(size_t n){return KaimAllocate(n);}
    static void operator delete(void* p){memoryRelease(p);}
    static void* operator new[](size_t n){return KaimAllocate(n);}
    static void operator delete[](void* p){memoryRelease(p);}
};

struct Interval : GapObject {
    float low;
    float high;
    float time;
    float lateralVelocity;
    float alignment;

    Interval() {}
    Interval(float lowLimit, float highLimit, float intervalTime,
             float intervalVelocity, float intervalAlignment)
        : low(lowLimit), high(highLimit), time(intervalTime),
          lateralVelocity(intervalVelocity), alignment(intervalAlignment) {}
};

struct IntervalNode : GapObject {
    Interval interval;
    IntervalNode* previous;
    IntervalNode* next;
    unsigned char active;
    unsigned char unknownPadding[3];

    IntervalNode();
    virtual ~IntervalNode();
};

struct IntervalIterator : GapObject {
    IntervalNode* node;

    IntervalIterator(IntervalNode* entry = 0) : node(entry) {}
    ~IntervalIterator() {}
};

struct IntervalPool : GapObject {
    IntervalNode* storage;
    IntervalNode* head;
    IntervalNode* tail;
    IntervalNode* freeHead;
    unsigned int activeCount;
    unsigned int capacity;

    virtual ~IntervalPool();
    IntervalPool(unsigned int count);
    void Clear();
    IntervalIterator Insert(const Interval& interval, IntervalIterator before);
    __forceinline void Retire(IntervalNode* node) {
        node->active=0;
        if (node==head) head=node->next;
        if (node==tail) tail=node->previous;
        if (node->previous) node->previous->next=node->next;
        if (node->next) node->next->previous=node->previous;
        node->next=freeHead; freeHead=node; --activeCount;
    }
};

struct Diagram : GapObject {
    IntervalPool* pool;
    float low;
    float high;
    float bestTime;

    virtual ~Diagram();
    Diagram(unsigned int count);
    void Reset(float low, float high, float time);
    unsigned char Merge(const Interval& interval);
    unsigned char FindSlowerInterval(float low, float high, float time,
        IntervalIterator from, IntervalIterator end, float* boundary, IntervalIterator* result);
    unsigned char FindFasterInterval(float low, float high, float time,
        IntervalIterator from, IntervalIterator end, float* boundary, IntervalIterator* result);

};

unsigned char SolveContactTimes(float a, float b, float c, float* first, float* last);
float PlanarDistanceSquared(const Vec3* a, const Vec3* b);

struct Candidate : GapObject {
    Interval* interval;
    Interval* frontier;
    float lateral;
    float forward;
    Vec3 target;
    float cost;
    Candidate() { interval=0;frontier=0;lateral=0;forward=0;CopyVector(&target,&zeroVector);cost=FLT_MAX; }
};
struct CandidateNode : GapObject {
    Candidate candidate;
    CandidateNode* previous;
    CandidateNode* next;
    unsigned char active;
    unsigned char unknownPadding[3];
    CandidateNode();
    virtual ~CandidateNode();
};
struct CandidateIterator : GapObject {
    CandidateNode* node;
    CandidateIterator(CandidateNode* p=0) : node(p) {}
    ~CandidateIterator() {}
};
struct CandidatePool : GapObject {
    CandidateNode* storage;
    CandidateNode* head;
    CandidateNode* tail;
    CandidateNode* freeHead;
    unsigned int activeCount;
    unsigned int capacity;
    CandidatePool(unsigned int count);
    virtual ~CandidatePool();
    void Clear();
    CandidateIterator Insert(const Candidate&, CandidateIterator before);
};
struct TrackedActor : GapObject {
    Entity* entity; int cellX, cellZ;
    TrackedActor();
    virtual ~TrackedActor() {}
};
struct TraceResult : GapObject {
    float fraction;
    // The route trace writes a 32-byte result; the remaining payload is not
    // interpreted by avoidance, but must belong to the caller's result object.
    unsigned char unresolvedPayload[24];
};
extern void (__cdecl *traceRoute)(const Vec3*,const Vec3*,Entity*,TraceResult*,unsigned int);

struct AvoidancePolicy : GapObject {
    RouteFollower* route;
    float width, radius, height;
    Vec3 target, orientation;
    unsigned char useOrientation;
    unsigned char unknown2d[3];
    union { unsigned int frameFlags; unsigned char frameMarker; };
    AvoidancePolicy() {}
    virtual const ClassDefinition* GetDefinition() = 0;
    virtual void GenerateMove(const Vec3* goal, Movement* move) = 0;
    virtual unsigned char Configure(const Property* property) = 0;
    virtual void ResetFrame() {}
    virtual void RefreshTrackedActors() {}
};
struct Avoidance : AvoidancePolicy {
    Vec3 position, goal;
    float goalDistance;
    Vec3 forward, side;
    float horizon, predictedSpeed, goalTime, earliestContact;
    float overlapCount, overlapWidth;
    Vec3 overlapCenter;
    unsigned int directionMode;
    float selectedSpeed;
    unsigned int selectionKind;
    Candidate selected;
    float previousSpeed, speedGraceDeadline, zeroGraceDeadline, retryDeadline;
    float stallEscapeDeadline, directionDeadline;
    Vec3 stallAnchor;
    float stallDistance, stallAnchorTime, stallThreshold, stallDelay;
    float diagramHalfWidth, candidateSpacing, slowSpeedFactor;

    Avoidance(RouteFollower* source) __asm__("func_00306848");
    virtual ~Avoidance();
    virtual const ClassDefinition* GetDefinition();
    virtual void GenerateMove(const Vec3* point, Movement* move) __asm__("func_00307970");
    virtual unsigned char Configure(const Property* property);
    virtual void ResetFrame();
    virtual void RefreshTrackedActors();
    void SetStallDelay(float value);
    void SetDiagramWidth(float value);
    void SetSpacing(float value);
    void BeginUpdate(const Vec3* point) __asm__("func_00307480");
    unsigned char DetectStalledProgress() __asm__("func_00307FB0");
    unsigned char BuildNeighborDiagram() __asm__("func_003080B8");
    void PredictCellContacts(int x, int z, Entity* source) __asm__("func_00308360");
    unsigned char GenerateCandidates() __asm__("func_00309B10");
    void ScoreCandidate(Candidate*, const float* right, const float* middle, const float* left) __asm__("func_0030B988");
    void ScoreCandidates() __asm__("func_0030B038");
    unsigned char RankCandidates() __asm__("func_0030B270");
    unsigned char SelectCandidate() __asm__("func_00309580");
    void DefaultCandidate();
    __forceinline float RequestedSpeed() const { return route->requestedSpeed->value; }
};
unsigned char __cdecl SteeringQuadratic(float a,float b,float c,float* plusRoot,float* minusRoot);
void RefreshCells();
void CollectTrackedActors();
int __cdecl CompareTrackedCells(const void*,const void*);
void __cdecl OnActorCreated(Entity*,void* owner);
void __cdecl OnActorRemoved(Entity*,void* owner);
Avoidance* __cdecl CreateAvoidance(RouteFollower*);
ClassDefinition* __cdecl FindAvoidanceClass(const char*);

extern unsigned short avoidanceOwners;
extern unsigned char sharedInitialized, callbacksRegistered;
extern float avoidanceTime, trackingPeriod, nextTrackingUpdate;
extern unsigned int trackedCount;
extern Diagram* sharedDiagram;
extern CandidatePool* rawCandidates;
extern CandidatePool* rankedCandidates;
extern TrackedActor* trackedActors;

// These sizes and field positions agree with the PS2 constructor/destructor and
// candidate-list accesses. Padding is not initialized by the node constructors.
typedef char IntervalSize[(sizeof(Interval) == 24) ? 1 : -1];
typedef char IntervalNodeSize[(sizeof(IntervalNode) == 40) ? 1 : -1];
typedef char IntervalIteratorSize[(sizeof(IntervalIterator) == 8) ? 1 : -1];
typedef char IntervalPoolSize[(sizeof(IntervalPool) == 28) ? 1 : -1];
typedef char DiagramSize[(sizeof(Diagram) == 20) ? 1 : -1];
typedef char NodePreviousOffset[(offsetof(IntervalNode, previous) == 28) ? 1 : -1];
typedef char NodeNextOffset[(offsetof(IntervalNode, next) == 32) ? 1 : -1];
typedef char NodeActiveOffset[(offsetof(IntervalNode, active) == 36) ? 1 : -1];
typedef char CandidateSize[(sizeof(Candidate)==36)?1:-1];
typedef char CandidateNodeSize[(sizeof(CandidateNode)==52)?1:-1];
typedef char TrackedSize[(sizeof(TrackedActor)==16)?1:-1];
typedef char AvoidanceSize[(sizeof(Avoidance)==252)?1:-1];
typedef char TraceResultSize[(sizeof(TraceResult)==32)?1:-1];
typedef char SelectedOffset[(offsetof(Avoidance,selected)==152)?1:-1];

} // namespace KaimAvoidance

#endif
