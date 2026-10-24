// World lifecycle and iterator views; field offsets follow PS2 consumers.
#ifndef BLACK_CONTEXT_BEHAVIORS_WORLD_HPP
#define BLACK_CONTEXT_BEHAVIORS_WORLD_HPP
#include "kynapse/alloc.hpp"
extern void (*memoryRelease)(void*);
extern "C" int func_00360838(const char*,const char*);
namespace KaimWorld {
struct ClassInfo {char name[0x108];ClassInfo* base;};

// Base of Kynapse objects: a vtable with a virtual destructor. Deleting
// destructors release through the engine allocator hook.
struct Object {
    Object() {}
    virtual ~Object() {}
    static void operator delete(void* p) { memoryRelease(p); }
    static void* operator new(unsigned int size) { return KaimAllocate((unsigned int)size); }
};

struct Vec3 {
    float x, y, z;
};

// Bounded doubly linked list over a preallocated node array, used for search
// queues, intervals and candidates. Nodes return to a free chain; addresses
// stay stable. Node layout: vtable, value, previous, next, active flag.
template <class T> struct ListNode : Object {
    T value;
    ListNode* previous;
    ListNode* next;
    unsigned char active;
};

template <class T> struct ListIterator : Object {
    ListNode<T>* node;
    ListIterator(ListNode<T>* entry = 0) : node(entry) {}
    virtual ~ListIterator() {}
    ListIterator(const ListIterator& other):node(other.node) {}
    ListIterator& operator=(const ListIterator& other){node=other.node;return *this;}
};

template <class T> struct List : Object {
    List(unsigned int capacity);   // defined where the list is built (see owned_arrays.cpp)

    ListNode<T>* storage;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* freeHead;
    unsigned int activeCount;
    unsigned int capacity;

    ListIterator<T> Begin() { return ListIterator<T>(head); }
    void Clear()
    {
        while (head != 0) {
            head->active = 0;
            ListNode<T>* next = head->next;
            head->next = freeHead;
            freeHead = head;
            head = next;
        }
        tail = 0;
        activeCount = 0;
    }

    void Remove(const ListIterator<T>& at)
    {
        ListNode<T>* node = at.node;
        node->active = 0;
        if (node == head) head = node->next;
        if (node == tail) tail = node->previous;
        if (node->previous) node->previous->next = node->next;
        if (node->next) node->next->previous = node->previous;
        node->next = freeHead;
        freeHead = node;
        --activeCount;
    }

    ListIterator<T> Insert(const T& value, ListIterator<T> before);

    ListIterator<T> At(unsigned int index)
    {
        if (index < capacity)
            return ListIterator<T>(&storage[index]);
        return ListIterator<T>(0);
    }
};

// Allocates a free node and links it before `before` (or appends). Kept out of line: callers
// in the original reach it through a call.

template <class T>
ListIterator<T> List<T>::Insert(const T& value, ListIterator<T> before)
{
    ListNode<T>* entry = freeHead;
    if (entry == 0)
        return ListIterator<T>(0);
    ++activeCount;
    freeHead = entry->next;
    entry->value = value;
    entry->active = 1;
    if (before.node == 0) {
        if (tail == 0) {
            head = entry;
            tail = entry;
            entry->next = 0;
            head->previous = 0;
            tail->previous = 0;
            tail->next = 0;
            return ListIterator<T>(entry);
        }
        entry->previous = tail;
        entry->next = 0;
        tail->next = entry;
        tail = entry;
        return ListIterator<T>(entry);
    }
    ListNode<T>* previous = before.node->previous;
    entry->next = before.node;
    before.node->previous = entry;
    entry->previous = previous;
    if (previous)
        previous->next = entry;
    else
        head = entry;
    return ListIterator<T>(entry);
}



struct ParameterTables {
    void Update(float step) __asm__("func_002E8920");
    int NextSlot() __asm__("func_002E90B8");
    void Snapshot() __asm__("func_002E9CB0");
};
ParameterTables* GetNameTables() __asm__("func_002E91C0");

struct Service : Object {
    virtual void Slot1();
    virtual void Slot2();
    virtual void Reset();
    virtual void Tick();
    virtual struct ClassInfo* GetClassInfo();
};

struct Entity;

// Sub-objects of an entity: handlers are told when the entity leaves its engine.
struct EntityHandler : Object {
    virtual void Slot1();
    virtual void Slot2();
    virtual void Detach(Entity* entity);         // slot 3
};

struct EntityAttachment : Object {
    unsigned char unknown04[0x14];
    EntityHandler* handler;
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual bool IsReady();                      // slot 5
};

// An entity is on the global list (node at 0x0c) and on its engine's list (node at 0x14).
struct Entity : Object {
    unsigned char unknown04[8];
    ListNode<Entity*>* globalNode;
    unsigned char unknown10[4];
    ListNode<Entity*>* node;
    EntityAttachment* attachment;
    unsigned char unknown1c[0xc];
    struct Engine* owner;
    List<EntityHandler*>* handlers;
    virtual void Slot1();
    virtual void Reset();
    virtual void Slot3();
    virtual void Tick();
    virtual struct ClassInfo* GetClassInfo();
};

typedef void (*EntityCallback)(Entity* entity, void* context);

bool Kaim_DestroyObject(Entity* object) __asm__("func_002E12B0");
void Kaim_ReleaseService() __asm__("func_002E9CC8");

extern List<Entity*>* gObjectList;

extern unsigned int gFirstCapacity;
extern unsigned int gFirstCount;
extern EntityCallback* gFirstFunctions;
extern void** gFirstContexts;
extern unsigned int gSecondCapacity;
extern unsigned int gSecondCount;
extern EntityCallback* gSecondFunctions;
extern void** gSecondContexts;

struct EngineBase : Object {
    Object* context;
    unsigned char unknown08[4];
    float scale;
    unsigned int limit;
    List<Entity*>* entities;
    unsigned char unknown18[4];
    List<Object*>* owned;
    Object** services;
    unsigned int serviceCount;
    unsigned int serviceCapacity;

    EngineBase() : limit(0), entities(0), owned(0), serviceCount(0), serviceCapacity(0) {}
};

struct Engine : EngineBase {
    Engine(Object* newContext);
    void AddService(Object* service) __asm__("func_002EB280");
    void Update(float step) __asm__("func_002EA898");
    int Register(Entity* entity) __asm__("func_002EABB0");
    int Unregister(Entity* entity) __asm__("func_002EAD58");
    virtual ~Engine();
    void Reset() __asm__("func_002EAAC8");
    Entity* Find(const char*) __asm__("func_002EB398");
    void RegisterFirst(EntityCallback,void*) __asm__("func_002EA388");
    void RegisterSecond(EntityCallback,void*) __asm__("func_002EA610");
    void RemoveFirst(EntityCallback,void*) __asm__("func_002EBE90");
    void RemoveSecond(EntityCallback,void*) __asm__("func_002EBF58");
    Service* FindService(ClassInfo*) __asm__("func_002EC058");
    Service* FindExactService(ClassInfo*) __asm__("func_002EC110");
};






// These offsets are exercised by the exact PS2 callback, traversal and service lookups.
typedef char WorldEntitiesAt14[(unsigned int)&((Engine*)0)->entities==0x14?1:-1];
typedef char WorldServicesAt20[(unsigned int)&((Engine*)0)->services==0x20?1:-1];
typedef char WorldServiceCountAt24[(unsigned int)&((Engine*)0)->serviceCount==0x24?1:-1];
typedef char IteratorNodeAt4[(unsigned int)&((ListIterator<Entity*>*)0)->node==4?1:-1];
typedef char NodeNextAtC[(unsigned int)&((ListNode<Entity*>*)0)->next==12?1:-1];
}

#endif
