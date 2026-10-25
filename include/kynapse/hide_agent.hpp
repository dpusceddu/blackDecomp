// Inferred hide-behaviour names; layouts are checked against the PS2 accesses.
#ifndef BLACK_KYNAPSE_HIDE_AGENT_HPP
#define BLACK_KYNAPSE_HIDE_AGENT_HPP

#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);

extern "C" {
    int func_00360838(const char *, const char *);
    long func_0035E730(const char *);
    int func_0035E750(const char *);
    float func_00291C68(long);
}
namespace HideViews {
    struct ObjectBase {
        virtual ~ObjectBase();
    };

    struct Vec3 {
        float x, y, z;
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
    extern float gNow __asm__("D_003C958C");

    struct ChildBuffers {
        const char* GetSecond() const __asm__("func_002E3920");
        const char* GetValue() const __asm__("func_002E3918");
    };

    struct ActionBank {
        virtual void Slot0();
        virtual void Select(void* other);
        void ClearActivation() __asm__("func_002DFBF8");
    };

    struct NameTable {
        int FindName(const char* name) __asm__("func_002E93B8");
    };
    NameTable* GetNameTables() __asm__("func_002E91C0");

    struct ParameterTables {
        bool Consume(int index, void* user) __asm__("func_002E8AB8");
        void Accumulate(int index, void* user) __asm__("func_002E9978");
    };

    struct Actor {
        unsigned char unknown00[0x30];
        Vec3 position;
        void* GetAuthoredProperty(const void* key) __asm__("func_002E4CE0");
    };
    struct VectorProperty {
        unsigned char unknown00[4];
        Vec3 value;
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
        virtual bool Rate(float* distance, const void* from, const void* to);
        virtual void Slot8();
        virtual void Slot9();
        virtual bool IsActive();
    };

    struct Candidate;
    struct NodeGraph {
        unsigned char unknown00[0x0c];
        unsigned int capacity;
        unsigned char unknown10[4];
        unsigned int count;
        Candidate* items;
    };
    struct Context {
        unsigned char unknown00[0x14];
        Actor* actor;
    };
    struct ClassInfo;
    struct ClassRegistryA {
        void* FindByClass(ClassInfo* wanted) __asm__("func_002E1C58");
    };
    struct Component;
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
    struct ItemList {
        void* IdByName(const char* name) __asm__("func_002F2F58");
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
    struct ClassRegistryB {
        void* FindByClass(ClassInfo* wanted) __asm__("func_002EC058");
    };

    extern ClassInfo gTargetClass __asm__("D_004512B0");
    extern ClassInfo gPerceptionClass __asm__("D_00455E18");
    extern ClassInfo gTypeListClass __asm__("D_00452158");
    extern ClassInfo gLookupClass __asm__("D_00450FD8");
    extern const unsigned char gKeyPosition __asm__("D_0044FD38");
    extern const unsigned char gTextTag;

    void* Kaim_AllocateTagged(unsigned int size, const void* tag);
    bool __cdecl Kaim_CallHook(const Vec3* from, const Vec3* to, Actor* actor, int flag) __asm__("func_002E27D0");
    void* __cdecl NavigationGraph_FindNearestNode(NodeGraph* graph, const Vec3* point, Actor* actor, float radius,
    unsigned int outgoing, unsigned int incoming) __asm__("func_002FB9D0");
    void* __cdecl NavigationGraph_QueryNode(const Vec3* point, Actor* actor, float radius, NodeGraph* graph,
    unsigned int outgoing, unsigned int incoming) __asm__("func_002FBC20");

    struct Behavior : ObjectBase {
        virtual ~Behavior();
        virtual bool Init(ChildBuffers* config) __asm__("func_002D3F10");
        bool ConfigureAll(ChildBuffers* config) __asm__("func_002E0018");
        ActionBank* bank;
        Context* context;
    };

    struct Candidate {
        int id;
        Vec3 position;
        unsigned char unknown10[4];
    };

    struct Component {
        virtual void Slot0();
        virtual void Slot1();
        virtual ClassInfo* GetClassInfo();
    };

    struct ZeroedBase : ObjectBase {
        virtual ~ZeroedBase() {
        }
        int field04, field08, field0c, field10, field14, field18, field1c, field20;
        ZeroedBase() __asm__("func_002E7360");
    };
    struct VectorController : ZeroedBase {
        int axisX, axisY, axisZ;
        int component0;
        int extra;
        VectorController(const int* source, int value);
        __forceinline VectorController(const int* source, int value, bool expanded)
        : axisX(source[1]), axisY(source[2]), axisZ(source[3]), component0(source[0]), extra(value) {
        }
        virtual ~VectorController() {
        }
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

    extern ClassInfo gSectionClass __asm__("D_00451658");

    struct PerceptionRecord {
        unsigned char unknown00[0x11];
        bool hidden;
    };
    struct Perception {
        PerceptionRecord* GetRecord(Actor* actor) __asm__("func_00310120");
    };

    struct HideAgent : Behavior {
        void* perception;
        TargetEntity* provider;
        Vec3 destination;
        int rank;
        int currentId;
        int computeName;
        float nextTime;
        int checkName;
        bool active;
        bool allHidden;
        VectorProperty* offsetProperty;
        unsigned char mode;
        unsigned char unknown3d[3];
        Actor** dangerous;
        void** nodes;
        unsigned int dangerousCount;
        unsigned int maxDangerous;
        NodeGraph* graph;
        union {
            struct {
                bool found;
                bool fresh;
            };
            unsigned short visibilityState;
        };
        unsigned char unknown56[2];
        int stage;
        float farLimit;
        float nearLimit;
        float bestScore;
        bool hasBest;
        unsigned char unknown69[3];
        LookupService* lookup;
        unsigned int graphSlot;
        void* currentNode;
        float maxDeltaHeight;
        NodeGraph* section;

        virtual bool Init(ChildBuffers* config) __asm__("func_002D3F10");
        virtual bool Configure(ChildBuffers* entry) __asm__("func_002D3D38");
        virtual void Slot3();
        virtual void Slot4();
        virtual void Slot5();
        virtual bool Update() __asm__("func_002D42C8");
        virtual bool Prepare();
        virtual bool Validate();
        virtual bool Evaluate(const Candidate* candidate, const Vec3* offset, float* score, bool* handled,
        bool* proceed) __asm__("func_002D4B68");
        virtual void Reset() __asm__("func_002D5398");

        bool Consider(const Candidate* candidate, const Vec3* offset, bool* handled) __asm__("func_002D5248");
        bool Test(const Candidate* candidate, const Vec3* offset, bool* seen) __asm__("func_002D49A8");
        bool SetGraph(void* id) __asm__("func_002D4148");
        void Scan(const Vec3* offset) __asm__("func_002D4720");
        int AddDangerous(Actor *) __asm__("func_002D5328");
        bool Search() __asm__("func_002D4520");
    };

}

#define HIDE_OFFSET(member, offset) typedef char HideAgent_##member##_offset[(unsigned int)&((HideViews::HideAgent *)0)->member == offset ? 1 : -1]
HIDE_OFFSET(provider, 0x10);
HIDE_OFFSET(destination, 0x14);
HIDE_OFFSET(dangerous, 0x40);
HIDE_OFFSET(nodes, 0x44);
HIDE_OFFSET(dangerousCount, 0x48);
HIDE_OFFSET(maxDangerous, 0x4C);
HIDE_OFFSET(visibilityState, 0x54);
HIDE_OFFSET(farLimit, 0x5C);
HIDE_OFFSET(nearLimit, 0x60);
HIDE_OFFSET(graphSlot, 0x70);
#undef HIDE_OFFSET
typedef char HideAgent_extent[sizeof(HideViews::HideAgent) == 0x80 ? 1 : -1];
#endif
