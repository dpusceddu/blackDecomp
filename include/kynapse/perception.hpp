// Declarations of the Kynapse source module "perception" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_PERCEPTION_HPP
#define BLACK_KYNAPSE_MODULE_PERCEPTION_HPP
#include "kynapse/compat.hpp"

// The perception component: for every other entity it keeps a record (cone visibility, line of sight,
// hearing, relative group) that is refreshed lazily when a behavior asks for it. Pair data shared by
// all perceptions (distances, expiry times, line-of-sight flags) lives in global tables indexed by the
// triangular pair index.
#include "kynapse/alloc.hpp"
#include "kynapse/data_io.hpp"

#pragma intrinsic(memset)

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& other) : x(other.x), y(other.y), z(other.z) {}
    Vec3(float a,float b,float c) : x(a),y(b),z(c) {}
    Vec3& operator=(const Vec3& other)
    {
        x=other.x; y=other.y; z=other.z;
        return *this;
    }
};

// An authored vector property (three scalars from 0x04).
struct AuthoredVector {
    unsigned char unknown00[4];
    Vec3 value;
};

// An authored group property: the group id at 0x04.
struct AuthoredGroup {
    unsigned char unknown00[4];
    int group;
};

struct Entity {
    unsigned char unknown00[0x14];
    unsigned char* entry;                                     // 0x14 (its slot in the entity table)
    unsigned char unknown18[4];
    unsigned int flags;
    unsigned char unknown20[0x10];
    Vec3 position;
    unsigned char unknown3c[0xc];
    Vec3 direction;
    void* GetAuthoredProperty(const void* key);
};

// A slot of the entity table (0x14 bytes each).
struct EntityEntry {
    unsigned char unknown00[4];
    Entity* entity;
    unsigned char unknown08[4];
    EntityEntry* next;
    bool active;
};

// The PS2 iterator has a polymorphic root followed by its entry pointer.
struct EntityIteratorBase { virtual ~EntityIteratorBase() {} };

struct EntityEntryIterator : EntityIteratorBase {
    EntityEntry* entry;
    EntityEntryIterator() {}
    EntityEntryIterator(const EntityEntryIterator& other) : entry(other.entry) {}
    EntityEntryIterator& operator=(const EntityEntryIterator& other) {
        entry = other.entry;
        return *this;
    }
    EntityEntryIterator(EntityEntry* value) : entry(value) {}
};

struct EntityTable {
    unsigned char unknown00[4];
    EntityEntry* entries;
    EntityEntry* first;
    unsigned char unknown0c[0xc];
    unsigned int count;
    EntityEntryIterator Begin() { return EntityEntryIterator(first); }
    EntityEntryIterator GetEntry(unsigned int index) {
        if (index < count) return EntityEntryIterator(&entries[index]);
        return EntityEntryIterator(0);
    }
};

struct ClassHandle { unsigned char unknown00[0x10c]; unsigned int mask; };
extern ClassHandle gEntityManagerClass;
struct World {
    unsigned char unknown00[0x10];
    int maxEntities;
    EntityTable* table;
    void* FindByClass(ClassHandle* wanted);
};
extern World* gWorld;

struct Context {
    unsigned char unknown00[0x14];
    Entity* actor;
};

struct ChildBuffers;
struct NameTable8 {
    int FindName(const char* name);
};
struct ParameterTables {
    bool Consume(int index, void* user);
    void Accumulate(int index, void* user);
};
ParameterTables* GetNameTables();
NameTable8* GetNameTable8();                                  // 0x526a0 (the same lazily created object)

extern float gNow;
extern unsigned char* gPairFlags;
extern float* gPairDistances;
extern float* gPairExpiry;
extern float* gPairLineExpiry;
extern ClassHandle gSoundPoolClass;
extern int gKeyPosition;
extern int gKeyAxis;
extern int gKeyGroup;
extern int gKeyCone;

inline float Kaim_GetPairValue(int a, int b) {
    int index = a > b ? a * (a - 1) / 2 + b : b * (b - 1) / 2 + a;
    return gPairDistances[index];
}
inline unsigned char Kaim_GetPairFlag(int a, int b) {
    int index = a > b ? a * (a - 1) / 2 + b : b * (b - 1) / 2 + a;
    return gPairFlags[index];
}
float Vec3_Length(const Vec3* a, const Vec3* b);
bool Kaim_CallHook(const Vec3* from, const Vec3* to, Entity* ignore, int mode);
bool InCone(float angle, float range, const Vec3* point, const Vec3* origin, const Vec3* axis);
struct Perception;
int Entity_ApplyC(World* world, void (__cdecl *callback)(Entity*, Perception*), Perception* context);

struct SoundPool {
    bool Hears(Entity* listener, Entity* other);
};

// Records inherit the polymorphic root so the vptr precedes their data on PS2.
struct PerceptionRecordBase { virtual ~PerceptionRecordBase() {} };

struct PerceptionRecord : PerceptionRecordBase {
    virtual ~PerceptionRecord() {}
    float coneExpiry;
    float pairExpiry;
    float distance;
    bool inCone;
    bool blocked;
    bool heard;
    bool otherGroup;

    PerceptionRecord() {
        coneExpiry = 0;
        pairExpiry = 0;
        distance = 0;
        inCone = false;
        blocked = false;
        heard = false;
        otherGroup = false;
    }
    static void* operator new[](unsigned int size) { return KaimAllocate(size); }
};

// The entity manager the perception reads slots from.
struct EntityManager;

struct SlotUser {
    int GetIndex();
};

struct Perception {
    unsigned char unknown00[4];
    Context* context;
    float recordInterval;                                     // 0x08 (how long a record stays fresh)
    float pairInterval;                                       // 0x0c (how long pair data stays fresh)
    unsigned char unknown10[4];
    EntityManager* entities;
    Entity* tracked[6];                                       // 0x18 (entities this perception reacts to)
    PerceptionRecord* records;
    SoundPool* soundPool;
    AuthoredVector* originProperty;
    AuthoredVector* axisProperty;
    AuthoredGroup* groupProperty;
    AuthoredVector* coneProperty;                             // 0x44 (range at 0x04, angle at 0x08)
    bool dirtyCone;
    bool dirtyGroup;
    unsigned char unknown4a[2];
    int computeName;
    bool pendingCone;
    bool pendingGroup;
    bool pendingLine;

    bool ConfigureAll(ChildBuffers* config);
    bool Init(ChildBuffers* config);
    void Reset();
    void FindNearest();
    void ClearRequests();
    Entity* NearestVisible();
    Entity* NearestClear();
    Entity* NearestAny();
    Entity* NearestVisibleOtherGroup();
    Entity* NearestClearOtherGroup();
    Entity* NearestAnyOtherGroup();
    void UpdatePair(int a, int b, unsigned char lineCheck);
    bool Refresh(unsigned int index);
    PerceptionRecord* GetRecord(SlotUser* user);
};

// Clear tracked references when the entity table removes a subject.
void __cdecl OnSubjectRemoved(Entity* subject, Perception* perception);

typedef char assert_PerceptionRecord_size[(sizeof(PerceptionRecord) == 0x14) ? 1 : -1];
typedef char assert_PerceptionRecord_coneExpiry[((int)&((PerceptionRecord*)0)->coneExpiry == 4) ? 1 : -1];
typedef char assert_PerceptionRecord_flags[((int)&((PerceptionRecord*)0)->inCone == 0x10) ? 1 : -1];
typedef char assert_Perception_records[((int)&((Perception*)0)->records == 0x30) ? 1 : -1];
typedef char assert_Perception_requests[((int)&((Perception*)0)->pendingCone == 0x50) ? 1 : -1];
typedef char assert_EntityEntryIterator_size[(sizeof(EntityEntryIterator) == 8) ? 1 : -1];
typedef char assert_EntityEntryIterator_entry[((int)&((EntityEntryIterator*)0)->entry == 4) ? 1 : -1];

#endif
