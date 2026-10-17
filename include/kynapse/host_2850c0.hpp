// Declarations of the Kynapse source module "host_2850c0" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_HOST_2850C0_HPP
#define BLACK_KYNAPSE_MODULE_HOST_2850C0_HPP
#include "kynapse/compat.hpp"

// Component host with vtable 0x2850c0: a list host (see node_lists.cpp) that also owns an array
// of sub-objects and a listener hook.

#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

// Caller passes a listener receiver in ECX; the callee accesses global arrays.
struct ListenerRegistry {
    void Notify(void* subject, void* owner);
};

namespace Kaim {

struct ListHostBase {
    unsigned char unknown04[0x5c];
    ListHostBase(int first, int second);
    virtual ~ListHostBase();
};

struct Bag;
// A property slot: an index into its bag's value array, or the bag's primary value.
struct Slot {
    int index;
    Bag* bag;
    void SetValue(void* value);
};
struct Bag {
    unsigned char unknown00[0x50];
    void** values;
    unsigned char unknown54[8];
    Slot primary;
    unsigned char unknown64[0x30];
    void* primaryValue;
};

static __forceinline void* GetSlotValue(Slot* slot)
{
    Bag* bag = slot->bag;
    if (slot == &bag->primary)
        return bag->primaryValue;
    if (bag->values)
        return bag->values[slot->index];
    return 0;
}

static __forceinline bool HasSlotValue(Slot* slot)
{
    return GetSlotValue(slot) != 0;
}



static __forceinline void SetSlotValue(Slot* slot, void* value)
{
    slot->SetValue(value);
}

// The same store expanded in place.
static __forceinline void StoreSlotValue(Slot* slot, void* value)
{
    Bag* bag = slot->bag;
    if (slot == &bag->primary)
        bag->primaryValue = value;
    else if (bag->values)
        bag->values[slot->index] = value;
}

// The same arrangement for float properties.
struct FloatBag;
struct FloatSlot {
    int index;
    FloatBag* bag;
    void SetValue(float value);
};
struct FloatBag {
    unsigned char unknown00[0x48];
    float* values;
    unsigned char unknown4c[0x10];
    FloatSlot primary;
    unsigned char unknown64[0x28];
    float primaryValue;
};



struct Element {
    Element() : id(0), slot(0), previous(0) {}
    static __forceinline void* operator new[](unsigned int size) { return KaimAllocate(size); }
    virtual ~Element();
    int id;
    Slot* slot;
    void* previous;
};

struct ClassInfo {
    unsigned char unknown00[0x10c];
    ClassInfo* parent;
};
extern ClassInfo gSensorClass;
extern ClassInfo gListenerClass;
struct ChildBuffers {
    const char* FindThirdBySecond(const char* second) const;
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
    bool HasId(int id);
};
struct Engine {
    TypeRegistry* FindByClass(ClassInfo* wanted);
};
extern Engine* gEngine;
extern ClassInfo gTypeRegistryClass;

struct Host2850C0 : ListHostBase {
    Element* elements;                     // 0x60 (array)
    unsigned int elementCount;
    ListenerRegistry* listeners;
    unsigned int capacity;

    Host2850C0(int first, int second);
    virtual bool Init(ChildBuffers* config);                       // slot 1 (0x5add0)
    virtual void Slot2();
    virtual ClassInfo* GetClassInfo();                            // slot 3
    virtual void Slot4();
    virtual void Slot5(); virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void Slot9(); virtual void Slot10(); virtual void Slot11(); virtual void Slot12();
    virtual void Slot13(); virtual void Slot14();
    virtual void OnRecord(int id, Slot* slot);   // slot 15 (0x3c)
    virtual void Slot16();
    virtual void OnType(int id);           // slot 17 (0x44)
    virtual void OnRelease(int id, Slot* slot);   // slot 18 (0x48)

    void Replay();
    void Notify(void* owner);
    bool Claim(int id, Slot* slot);
    bool Release(int id, Slot* slot);
    virtual ~Host2850C0();                 // 0x5a9d0 (deleting destructor 0x5ad80)
    static void operator delete(void* block) { memoryRelease(block); }
};






// Unmatched: slot/loop registers differ; separate guards and an explicit element cursor were worse (142 bytes).



// Unmatched: slot-chain scans and register lifetimes differ; repeated owner read and separate guards were worse (306 vs 354 bytes).
// Gives a slot back: the slot's value goes back to the host that held it before this one.








// Unmatched: transcribed from the decompilation.
// Reads the number of elements the host can link ("LinkedEdgeMax"), allocates them and looks up the
// listener registry; true when the host's class is derived from the sensor class.


}  // namespace Kaim

#endif
