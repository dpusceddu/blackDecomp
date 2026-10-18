#ifndef BLACK_ROUTE_LIFETIME_HPP
#define BLACK_ROUTE_LIFETIME_HPP
#include "kynapse/alloc.hpp"
// Guarded model: complete type not verified by a linked matching function.
extern void (*memoryRelease)(void*);

void* ArrayAllocate(unsigned int size);

struct Tolerance {
    virtual ~Tolerance();
    int unknown04;
    float epsilon;
    int unknown0c;
    float ratio;
    Tolerance();
    static void* operator new[](unsigned int size) { return ArrayAllocate(size); }
};

namespace Kaim {

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Actor {};
struct Controller {
    unsigned char unknown00[0x14];
    Actor* actor;
};

struct Collection;
struct TreeOwner : ObjectBase {
    Controller* controller;
    ObjectBase* child;
    ObjectBase** items;
    unsigned int count;
    TreeOwner(Collection* collection);
    virtual ~TreeOwner();
};

struct BufferQuad {
    unsigned char bytes[0x28];
    BufferQuad();
    ~BufferQuad();
};

struct ClassInfo;
struct ListenerRegistry {
    void Remove(void (__cdecl *function)(float, void*), void* data, Actor* owner);
};
struct EntityObject {
    ListenerRegistry* FindByClass(ClassInfo* wanted);
};
extern EntityObject* gEngine;
extern ClassInfo gListenerClass;
void __cdecl Kaim_ApplyToTarget(float value, void* target);

struct Tracked : ObjectBase {};

struct Vec3Fields {
    float x, y, z;
    Vec3Fields& operator=(const Vec3Fields& other) { x=other.x; y=other.y; z=other.z; return *this; }
};
extern Vec3Fields gOrigin;

// A counter whose first construction clears it (the function-local static of the constructor).
struct OwnedCounter {
    int value;
    static bool resetPending;
    OwnedCounter()
    {
        if (resetPending)
            value = 0;
        resetPending = false;
    }
    ~OwnedCounter() { value = 0; }
};


struct RouteFollowerShell : TreeOwner {
    unsigned char unknown14[4];
    Tracked** owned;
    int ownedHead;
    unsigned int ownedCount;
    unsigned char unknown24[0x48];
    BufferQuad queue;
    unsigned char unknown94[0x1c];
    bool activated;
    bool searchOk;
    bool hold;
    bool paused;
    unsigned char unknownb4[0x1c];
    Vec3Fields target;
    Vec3Fields lastTarget;
    Vec3Fields previous;
    unsigned char unknownf4[0x44];
    void* startNode;
    void* goalNode;
    int waypoint;
    int turnState;
    Vec3Fields savedTarget;
    void* savedStart;
    void* savedGoal;
    unsigned char unknown15c[0x20];
    void* routeTable;
    void* looseGraph;
    unsigned char unknown184[0x18];
    Vec3Fields lastPosition;
    float segmentLength;
    Tolerance* perProperty;
    Tracked* policy;
    unsigned char unknown1b4;
    bool restartSearch;

    RouteFollowerShell(Collection* collection);
    virtual ~RouteFollowerShell();
};


}
#endif
