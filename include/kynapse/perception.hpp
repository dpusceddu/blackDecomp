// Declarations of the Kynapse source module "perception" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
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

// Compatible eight-byte result of the bounded-list accessor at 0x4f9b0.
struct EntityEntryIterator {
    void* rootVtable;
    EntityEntry* entry;
};

struct EntityTable {
    unsigned char unknown00[4];
    EntityEntry* entries;
    EntityEntry* first;
    unsigned char unknown0c[0xc];
    unsigned int count;
    void GetEntry(EntityEntryIterator* result, int index) {
        result->entry = (unsigned int)index < count ? &entries[index] : 0;
    }
};

struct ClassHandle;
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
extern unsigned int gPerceivableMask;
extern ClassHandle gSoundPoolClass;
extern int gKeyPosition;
extern int gKeyAxis;
extern int gKeyGroup;
extern int gKeyCone;

float __stdcall Kaim_GetPairValue(int a, int b);
unsigned char __stdcall Kaim_GetPairFlag(int a, int b);
float Vec3_Length(const Vec3* a, const Vec3* b);
bool Kaim_CallHook(const Vec3* from, const Vec3* to, Entity* ignore, int mode);
bool InCone(const Vec3* point, const Vec3* origin, const Vec3* axis, float angle, float range);
struct Perception;
int Entity_ApplyC(World* world, void (__cdecl *callback)(Entity*, Perception*), Perception* context);

struct SoundPool {
    bool Hears(Entity* listener, Entity* other);
};

// What the perception knows about one other entity (vtable 0x284cf4).
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
    void UpdatePair(int a, int b, bool lineCheck);
    bool Refresh(unsigned int index);
    PerceptionRecord* GetRecord(SlotUser* user);
};


// Forgets a removed entity: every tracked slot holding it is cleared and the perception marked dirty.
void __cdecl OnSubjectRemoved(Entity* subject, Perception* perception);



// Unmatched: transcribed from the disassembly.
// Allocates the records and (once) the shared pair tables, looks up the sound pool and the authored
// properties and registers for entity removal.



// Unmatched: transcribed from the decompilation.
// Clears the shared pair tables and every record.



// Unmatched: eight-byte iterator/global table corrected; authored-vector copy lifetimes enlarge the frame (508 vs 507 bytes).
// Refreshes the pair data of two entities: their distance, and (when asked) whether a line between their
// authored positions is free.



// Unmatched: vector aggregate copies restore spill intent; visibility/frame/register scheduling still differs (766 vs 810 bytes).
// Brings the record of one other entity up to date and returns true when something changed.



// The record of a user (the first record when no user is given), marking the perception as read.


#endif
