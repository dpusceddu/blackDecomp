// Declarations of the Kynapse source module "lookups" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_LOOKUPS_HPP
#define BLACK_KYNAPSE_MODULE_LOOKUPS_HPP
#include "kynapse/compat.hpp"

// Kynapse lookups and sweeps over owned object arrays and lists.
#include "kynapse/alloc.hpp"

extern "C" int __cdecl _stricmp(const char*, const char*);
extern void (*memoryRelease)(void*);

namespace Kaim {

struct ClassInfo {
    unsigned char unknown00[0x10c];
    ClassInfo* parent;
};

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void operator delete(void* block) { memoryRelease(block); }
};

// Array of objects searched by class (an object matches when its class or an ancestor is `wanted`).
struct ClassRegistryA {
    unsigned char unknown00[0x0c];
    struct ObjectA {
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        virtual ClassInfo* GetClassInfo();          // slot 4
    }** items;
    int count;

    ObjectA* FindByClass(ClassInfo* wanted);
};



struct ClassRegistryB {
    unsigned char unknown00[0x20];
    struct ObjectB {
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        virtual void Slot4();
        virtual ClassInfo* GetClassInfo();          // slot 5
    }** items;
    unsigned int count;

    ObjectB* FindByClass(ClassInfo* wanted);
};



// Two arrays of components notified in turn.
struct ComponentSweep {
    unsigned char unknown00[4];
    struct Component {
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
    }** secondary;
    int secondaryCount;
    Component** primary;
    int primaryCount;

    void Sweep();
};



// Component host: a linked list of components plus an array of sub-hosts.
struct ListedComponent {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
};
struct ComponentNode {
    unsigned char unknown00[4];
    ListedComponent* component;
    unsigned char unknown08[4];
    ComponentNode* next;
};
struct ComponentList {
    unsigned char unknown00[8];
    ComponentNode* head;
};
struct SubHost {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
};
struct ComponentHost {
    unsigned char unknown00[0x14];
    ComponentList* list;
    unsigned char unknown18[8];
    SubHost** subHosts;
    unsigned int subHostCount;

    void Sweep();
};



struct NamedItem {
    unsigned char unknown00[4];
    const char* name;
};
struct NamedNode {
    unsigned char unknown00[4];
    NamedItem* item;
    unsigned char unknown08[4];
    NamedNode* next;
};
struct NamedList {
    unsigned char unknown00[8];
    NamedNode* head;
};
struct NamedHost {
    unsigned char unknown00[0x14];
    NamedList* list;

    NamedItem* FindByName(const char* name);
};



// Object holding one tag value.
struct Tagged : ObjectBase {
    int tag;
    Tagged(int value) : tag(value) {}
};

Tagged* MakeTagged(int value);


struct ReleasableEngine : ObjectBase {
    unsigned char unknown04[0x28];
    int slot;
};
extern ReleasableEngine** gEngineSlots;
extern ReleasableEngine* gEngine;


bool Kaim_DestroyEngine(ReleasableEngine* engine);


struct TableKey {
    int unknown0;
    int index;
    int (*resolver)();
};
struct ResolvedTable {
    unsigned char unknown00[0x0c];
    int* table;
    unsigned char unknown10[4];
    int current;

    bool Install(const TableKey* key);
};




}  // namespace Kaim

#endif
