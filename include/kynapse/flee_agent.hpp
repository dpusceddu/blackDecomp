// Inferred flee-behaviour names; PS2 offsets are checked against the TU accesses.
#ifndef BLACK_KYNAPSE_FLEE_AGENT_HPP
#define BLACK_KYNAPSE_FLEE_AGENT_HPP

#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*) __asm__("func_00360838");

extern KaimAllocator *gKaimAllocator __asm__("D_003C87E8");
extern void (*gKaimAllocateHook)(void *, unsigned int, unsigned int) __asm__("D_003C87EC");
extern "C" {
    int func_00360838(const char *, const char *);
    long func_0035E730(const char *);
    int func_0035E750(const char *);
    float func_00291C68(long);
}
namespace FleeRecovery {
    struct ObjectBase {
        virtual ~ObjectBase();
    };

    struct Vec3 {
        float x, y, z;
        Vec3() {
        }
        Vec3(float a, float b, float c) : x(a), y(b), z(c) {
        }
        float SquaredLength() const __asm__("func_00389140");
        Vec3& operator=(const Vec3& other)
       {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }
    };
    extern Vec3 gOrigin __asm__("D_004514F8");
    static const float kDefaultFloat = 0.0f;
    static const float kOne = 1.0f;
    extern float gNow __asm__("D_003C958C");
    extern bool (*gVisibilityHook)(const Vec3* from, const Vec3* to, void* actor, int flag);

    struct ChildBuffers {
        const char* GetSecond() const __asm__("func_002E3920");
        const char* GetValue() const __asm__("func_002E3918");
    };

    struct ActionBank {
        virtual void Slot0();
        virtual void Select(void* other);
        void ClearActivation() __asm__("func_002DFBF8");
    };

    struct NameTable4 {
        int FindName(const char* name) __asm__("func_002E9438");
    };
    struct NameTable8 {
        int FindName(const char* name) __asm__("func_002E93B8");
    };
    struct ParameterTables {
        bool Raise(int index, void* user) __asm__("func_002E96F8");
        bool Consume(int index, void* user) __asm__("func_002E8AB8");
        void Accumulate(int index, void* user) __asm__("func_002E9978");
    };
    ParameterTables* GetNameTables() __asm__("func_002E91C0");

    struct Actor {
        unsigned char unknown00[0x30];
        Vec3 position;
        unsigned char unknown3c[0x0c];
        Vec3 extent;
        void* GetAuthoredProperty(const void* key);
    };
    struct VectorProperty {
        unsigned char unknown00[4];
        Vec3 value;
    };
    struct FloatProperty {
        unsigned char unknown00[8];
        float value;
    };

    struct Engine {
        unsigned char unknown00[0x0c];
        float unit;
    };
    extern Engine* gEngine __asm__("D_003C9ED4");

    struct EntityInterfaceBase {
        virtual void Slot0();
    };
    struct TargetEntity : EntityInterfaceBase {
        unsigned char unknown04[4];
        void* id;
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        virtual void Slot4();
        virtual bool QueryTransform(void* data);
        virtual bool Query(void* data);
        virtual void Slot7();
        virtual void Slot8();
        virtual void Slot9();
        virtual bool IsActive();
    };
    struct PerceptionRecord {
        unsigned char unknown00[0x11];
        bool hidden;
    };
    struct Perception {
        PerceptionRecord* GetRecord(Actor* actor) __asm__("func_00310120");
    };

    struct Context {
        unsigned char unknown00[0x14];
        Actor* actor;
    };
    struct ClassInfo;
    struct ClassRegistryA {
        void* FindByClass(ClassInfo* wanted) __asm__("func_002E1C58");
    };
    struct ClassRegistryB {
        void* FindByClass(ClassInfo* wanted) __asm__("func_002EC058");
    };
    struct ItemList {
        void* IdByName(const char* name) __asm__("func_002F2F58");
    };
    struct Component {
        virtual void Slot0();
        virtual void Slot1();
        virtual ClassInfo* GetClassInfo();
    };
    struct TypeEntry {
        unsigned char unknown00[4];
        unsigned char key[0x80];
        int id;
        unsigned char unknown88[4];
        Component* components[32];
        unsigned int componentCount;
    };
    struct TypeList {
        unsigned char unknown00[4];
        TypeEntry** entries;
        unsigned int count;
    };
    struct LookupService {
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        virtual void Slot4();
        virtual void Slot5();
        virtual bool Lookup(const void* key, unsigned int* slot);
    };

    struct NodeGraph;
    struct GraphNode {
        unsigned int id;
        Vec3 position;
        NodeGraph* graph;
    };
    struct GraphEdge {
        int index;
        NodeGraph* graph;
    };
    struct NodeGraph {
        unsigned char unknown00[0x18];
        GraphNode* nodes;
        unsigned char unknown1c[0x1c];
        int* edgeEnd;
        int* edgeStart;
        unsigned char unknown40[0x1c];
        GraphEdge syntheticEdge;
        GraphNode syntheticEnd;
        GraphNode syntheticStart;
    };

    extern ClassInfo gTargetClass __asm__("D_004512B0");
    extern ClassInfo gPerceptionClass __asm__("D_00455E18");
    extern ClassInfo gTypeListClass __asm__("D_00452158");
    extern ClassInfo gLookupClass __asm__("D_00450FD8");
    extern ClassInfo gSectionClass __asm__("D_00451658");
    extern const unsigned char gKeyPosition;
    extern const unsigned char gKeyRadius;
    extern const unsigned char gKeyExtent;
    extern const unsigned char gTextTag;

    void* __cdecl ArrayAllocate(unsigned int size);
    void* Kaim_AllocateTagged(unsigned int size, const void* tag);
    GraphNode* __cdecl Kaim_FindNearestNodeSimple(NodeGraph* graph, const Vec3* point, bool needOutgoing,
    bool needIncoming) __asm__("func_002FB6D8");
    GraphNode* __cdecl NavigationGraph_QueryNode(const Vec3* point, Actor* actor, float radius, NodeGraph* graph,
    unsigned int outgoing, unsigned int incoming) __asm__("func_002FBC20");
    bool InCone(const Vec3* point, const Vec3* origin, const Vec3* axis, float angle, float range);

    struct Behavior : ObjectBase {
        Behavior(Context *) __asm__("func_002DFF10");
        virtual ~Behavior();
        virtual bool Init(ChildBuffers* config) __asm__("func_002D1918");
        bool ConfigureAll(ChildBuffers* config) __asm__("func_002E0018");
        ActionBank* bank;
        Context* context;
    };

    struct ZeroedBase : ObjectBase {
        virtual ~ZeroedBase() {
        }
        int field04, field08, field0c, field10, field14, field18, field1c, field20;
        ZeroedBase() __asm__("func_002E7360");
    };
    struct FollowQuery : ZeroedBase {
        int axisX, axisY, axisZ;
        int component0;
        int extra;
        __forceinline FollowQuery(const int* source, int component, int value)
        : axisX(source[0]), axisY(source[1]), axisZ(source[2]), component0(component), extra(value) {
        }
        virtual ~FollowQuery() {
        }
    };

    struct PointCell {
        Vec3 value;
        PointCell() {
        }
        static void* operator new[](unsigned int size) {
            return KaimAllocate(size);
        }
    };

    struct FleeVisitor;

    struct FleeAgent : Behavior {
        FleeAgent(Context *) __asm__("func_002D2D48");
        TargetEntity* provider;
        NodeGraph* graph;
        Perception* perception;
        int unknown18;
        Vec3* points;
        unsigned int pointCount;
        unsigned int maxPoints;
        Actor** entities;
        unsigned int entityCount;
        unsigned int maxEntities;
        Vec3 destination;
        int pathId;
        int pathFlag;
        bool initialized;
        unsigned char unknown49[3];
        Vec3 lastQuery;
        float requery;
        GraphNode* node;
        int dangerName;
        float nextTime;
        float interval;
        int computeName;
        bool danger;
        bool valid;
        unsigned char unknown72[2];
        int pathLength;
        bool stopWhenHidden;
        unsigned char unknown79[3];
        unsigned int graphSlot;
        NodeGraph* section;
        float maxDeltaHeight;

        virtual bool Init(ChildBuffers* config) __asm__("func_002D1918");
        virtual bool Configure(ChildBuffers* entry) __asm__("func_002D16B8");
        virtual void Slot3();
        virtual void Slot4();
        virtual void Slot5();
        virtual bool Update() __asm__("func_002D1D48");
        virtual bool Prepare();
        virtual bool Validate();
        virtual float Rate(void* node, int blocked, float sum, int depth) __asm__("func_002D2F80");
        int AddPoint(const Vec3 *) __asm__("func_002D2E90");
        int AddEntity(Actor *) __asm__("func_002D2F00");

        bool ComputeDestination() __asm__("func_002D2098");
        bool SetGraph(void* id) __asm__("func_002D1BC8");
        float ScorePath(GraphNode** result, GraphNode* from, int depth, int maxDepth, int blocked, float sum) __asm__("func_002D23B0");
    };

    struct VisitorBase {
        virtual ~VisitorBase() {
        }
    };
    struct FleeVisitor : VisitorBase {
        virtual ~FleeVisitor() {
        }
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        bool EnumerateOutgoingEdges(GraphNode* node);
        virtual bool OnEdge(GraphEdge* edge) __asm__("func_002D2A60");
        GraphNode* node;
        Vec3* points;
        int pointCount;
        Actor** entities;
        int entityCount;
        int depth;
        int maxDepth;
        float best;
        GraphNode* bestNode;
        float sum;
        int blocked;
        FleeAgent* agent;
    };

}

#define FLEE_OFFSET(member, offset) typedef char FleeAgent_##member##_offset[(unsigned int)&((FleeRecovery::FleeAgent *)0)->member == offset ? 1 : -1]
FLEE_OFFSET(points, 0x1C);
FLEE_OFFSET(pointCount, 0x20);
FLEE_OFFSET(maxPoints, 0x24);
FLEE_OFFSET(entities, 0x28);
FLEE_OFFSET(entityCount, 0x2C);
FLEE_OFFSET(maxEntities, 0x30);
FLEE_OFFSET(destination, 0x34);
FLEE_OFFSET(pathId, 0x40);
FLEE_OFFSET(graphSlot, 0x7C);
#undef FLEE_OFFSET
typedef char FleeAgent_extent[sizeof(FleeRecovery::FleeAgent) == 0x88 ? 1 : -1];
#endif
