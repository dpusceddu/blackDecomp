// Declarations of the Kynapse source module "tracker" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_TRACKER_HPP
#define BLACK_KYNAPSE_MODULE_TRACKER_HPP
#include "kynapse/compat.hpp"

// Tracker: keeps a bounded list of tracked objects, mirrors the object types of the world's
// type registry onto them, and listens for objects of its class being added and removed.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);
extern "C" int __cdecl atoi(const char*);

namespace Kaim {
struct ChildBuffers {
    const char* GetSecond() const;
    const char* GetValue() const;
};
}
using Kaim::ChildBuffers;

extern void (*memoryRelease)(void*);

struct ClassInfo {
    unsigned char unknown00[0x10c];
    ClassInfo* parent;
};

struct Tracked {
    virtual ~Tracked();
    virtual void Slot1();
    virtual void Slot2();
    virtual ClassInfo* GetClassInfo();   // slot 3
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Notify(int typeId);     // slot 13
    virtual void Slot14();
    virtual void Slot15();
    virtual void Detach();               // slot 16
};

struct TypeEntry {
    unsigned char unknown00[0x84];
    int typeId;
    bool mirrored;
};

struct TypeRegistry {
    unsigned char unknown00[4];
    TypeEntry** entries;
    unsigned int count;
};

struct EntityObject {
    TypeRegistry* FindByClass(ClassInfo* wanted);
};
int Entity_ApplyA(EntityObject* entity, int first, int second);
int Entity_ApplyB(EntityObject* entity, int first, int second);
int Entity_ApplyC(EntityObject* entity, int first, int second);
int Entity_ApplyD(EntityObject* entity, int first, int second);

extern EntityObject* gEngine;
extern ClassInfo gTypeRegistryClass;
extern ClassInfo gTrackedClass;

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Tracker;
void TrackerOnAdded(Tracked* object, Tracker* tracker);
void TrackerOnRemoved(Tracked* object, Tracker* tracker);

// Global listener table shared by trackers: functions, user data, filter owners.
typedef void (*ListenerFunction)(void* subject, void* data);
extern ListenerFunction* gListenerFunctions;
extern void** gListenerData;
extern void** gListenerOwners;
extern unsigned int gListenerCapacity;
extern unsigned int gListenerCount;

struct Tracker : ObjectBase {
    Tracked** items;
    unsigned int count;
    TypeRegistry* registry;
    unsigned int capacity;
    ObjectBase* extras;                  // 0x14 (array)
    int unknown18;

    Tracker();
    bool ConfigureAll(ChildBuffers* config);   // 0x54bf0 (shared base routine)
    bool Init(ChildBuffers* config);
    virtual void Slot1();
    virtual bool Configure(ChildBuffers* config);   // 0x594e0 (slot 2)
    bool Add(Tracked* object);
    bool Remove(Tracked* object);
    virtual __declspec(noinline) ~Tracker();  // 0x59b20 (deleting destructor 0x59c30)
};








void TrackerOnAdded(Tracked* object, Tracker* tracker);



void TrackerOnRemoved(Tracked* object, Tracker* tracker);





// Unmatched: data/function/owner comparison order improves the loop; array-base/count registers still differ (128 vs 128 bytes, 32 differing).
void __stdcall Kaim_RemoveListener(ListenerFunction function, void* data, void* owner);



void __stdcall Kaim_NotifyListeners(void* subject, void* owner);






#endif
