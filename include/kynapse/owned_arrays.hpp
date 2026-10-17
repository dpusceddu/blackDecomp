// Declarations of the Kynapse source module "owned_arrays" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_OWNED_ARRAYS_HPP
#define BLACK_KYNAPSE_MODULE_OWNED_ARRAYS_HPP
#include "kynapse/compat.hpp"

// Arrays of owned polymorphic objects (Kynapse containers) with their deleting destructors.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

namespace Kaim {

struct ObjectBase {
    virtual ~ObjectBase() {}
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

template <class T>
struct OwnedArray : ObjectBase {
    T** items;
    unsigned int count;
    unsigned int capacity;

    OwnedArray()
    {
        items = (T**)KaimAllocate(0x20);
        count = 0;
        capacity = 8;
    }
    virtual ~OwnedArray();
};



// Object owning one child.
struct Owner1 : ObjectBase {
    ObjectBase* child;
    virtual ~Owner1();
};

struct Owner2 : ObjectBase {
    ObjectBase* child;
    virtual ~Owner2();
};

struct OwnerD1 : Owner1 { virtual ~OwnerD1() {} };
struct OwnerD2 : Owner1 { virtual ~OwnerD2() {} };
// Bank of owned objects (signed count) that releases its storage only when it has entries.
struct PointerBankOwner : ObjectBase {
    int count;
    ObjectBase** items;
    PointerBankOwner();
    virtual ~PointerBankOwner();
};

// Number of item slots every bank allocates (set up on first use).
struct BankCount {
    int count;
    static bool resetPending;
    BankCount()
    {
        if (resetPending)
            count = 0;
        resetPending = false;
    }
    ~BankCount() {}
};
bool BankCount::resetPending = true;


// Unmatched: EBX zero is reproduced; vtable store placement and allocator scratch registers differ (47 bytes); named byte count did not change it.



// Owner of one child object plus an array of children.
struct TreeOwner : ObjectBase {
    unsigned char unknown04[4];
    ObjectBase* child;
    ObjectBase** items;
    unsigned int count;
    virtual ~TreeOwner();
};


// Bounded lists over a preallocated node array (Kaim::List<T> as seen by the container classes).
void* ArrayAllocate(unsigned int size);

struct SharedNode : ObjectBase {
    void* value;
    SharedNode* previous;
    SharedNode* next;
    unsigned char active;
    SharedNode()
    {
        previous = 0;
        next = 0;
        active = 0;
    }
    static void* operator new[](unsigned int size) { return ArrayAllocate(size); }
};

struct NodeValue : ObjectBase {
    unsigned char payload[0x14];
};
struct NodeD : ObjectBase {
    NodeValue value;
    NodeD* previous;
    NodeD* next;
    unsigned char active;
    NodeD()
    {
        previous = 0;
        next = 0;
        active = 0;
    }
    static void* operator new[](unsigned int size) { return ArrayAllocate(size); }
};

struct ArrayElementA {};
struct ArrayElementB {};
struct ArrayElementC {};
struct ArrayElementD {};
struct ArrayElementE {};
struct ArrayElementF {};

template <class Tag, class Node>
struct ArrayHolder : ObjectBase {
    Node* items;
    Node* head;
    Node* tail;
    Node* freeHead;
    unsigned int activeCount;
    unsigned int count;
    ArrayHolder(unsigned int capacity);
    virtual ~ArrayHolder();
};


template struct ArrayHolder<ArrayElementA, SharedNode>;
template struct ArrayHolder<ArrayElementB, SharedNode>;
template struct ArrayHolder<ArrayElementC, SharedNode>;
template struct ArrayHolder<ArrayElementD, NodeD>;
template struct ArrayHolder<ArrayElementE, SharedNode>;
template struct ArrayHolder<ArrayElementF, SharedNode>;


// ---------------------------------------------------------------------------
// Objects that release plain allocations in their destructors.
// ---------------------------------------------------------------------------

struct BufferTrio : ObjectBase {
    void* second;
    unsigned char unknown08[8];
    void* first;
    void* third;
    virtual ~BufferTrio();
};


struct BufferQuad : ObjectBase {
    int unknown04;
    int unknown08;
    void* first;
    void* second;
    void* third;
    void* fourth;
    int unknown1c;
    unsigned char unknown20;
    BufferQuad();
    virtual ~BufferQuad();
};




struct BufferPair : ObjectBase {
    unsigned char unknown04[0x10];
    void* first;
    void* second;
    virtual ~BufferPair();
};


// Table of plain blocks with a signed count; the table is only released when it exists.
struct BlockTable : ObjectBase {
    unsigned char unknown04[4];
    int count;
    void** blocks;
    virtual ~BlockTable();
};


// Short-count table of blocks plus a second allocation.
struct ShortBlockTable : ObjectBase {
    unsigned char unknown04[4];
    void** blocks;
    void* extra;
    short count;
    virtual ~ShortBlockTable();
};


BufferTrio* MakeTrio();

BufferQuad* MakeQuad();

BufferPair* MakePair();

BlockTable* MakeBlocks();

ShortBlockTable* MakeShortBlocks();



// Owner of child objects (items at 0x18, count at 0x20) plus three plain buffers and a capacity block.
struct ChildBuffers : ObjectBase {
    int unknown04;
    int unknown08;
    void* first;
    void* second;
    void* third;
    ObjectBase** items;
    unsigned int capacity;
    unsigned int count;

    ChildBuffers();
    void DeleteChildren();
    virtual ~ChildBuffers();
};




ChildBuffers* MakeChildBuffers();



// Owner of one child at 0x08.
struct ReleaseService {
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(); virtual void Slot3();
    virtual void Slot4(); virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Release(int value);                  // slot 8
};

struct ChildAt8 : ObjectBase {
    ReleaseService* service;
    ObjectBase* child;
    ChildAt8(unsigned int capacity);
    virtual ~ChildAt8();
};



// ChildAt8 with one more value.
struct ChildAt8Ext : ChildAt8 {
    int extra;
    ChildAt8Ext(int value, unsigned int capacity) : ChildAt8(capacity) { extra = value; }
};
ChildAt8Ext* MakeChildAt8Ext();


// Registration record owned by a parent: child list, a value and two cleared slots.
struct Registrar {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Register(ObjectBase* record);   // slot 3
    virtual void Unregister(ObjectBase* record); // slot 4
};
int ResolveName(int key);

struct RegistrationBase : ChildAt8 {
    Registrar* parent;
    RegistrationBase(Registrar* owner, unsigned int capacity) : ChildAt8(capacity), parent(owner) {}
};

struct Registration : RegistrationBase {
    virtual ~Registration();   // 0x4f480 (deleting destructor 0x4f5c0)
    int value;
    int resolved;
    int field18;
    int field1c;

    Registration(int first, int key, Registrar* owner, unsigned int capacity)
        : RegistrationBase(owner, capacity), value(first)
    {
        resolved = ResolveName(key);
        field18 = 0;
        field1c = 0;
        if (owner)
            owner->Register(this);
    }
};


Registration* MakeRegistration();


// Object with a single plain buffer at 0x08.
struct BufferAt8 : ObjectBase {
    unsigned char unknown04[4];
    void* buffer;
    virtual ~BufferAt8();
};


// One child plus two owned tables (signed counts).
struct DoubleTableOwner : ObjectBase {
    ObjectBase** firstItems;
    int firstCount;
    ObjectBase** secondItems;
    int secondCount;
    unsigned char unknown14[4];
    ObjectBase* child;
    virtual ~DoubleTableOwner();
};


// Owned array whose teardown also releases the shared pool.
void ReleaseSharedPool();
struct PoolArray : ObjectBase {
    ObjectBase** items;
    unsigned int count;
    unsigned int capacity;
    PoolArray()
    {
        items = (ObjectBase**)KaimAllocate(0x20);
        count = 0;
        capacity = 8;
    }
    virtual ~PoolArray();
};


// Inline slots of owned objects plus a head object.
struct SlotOwner : ObjectBase {
    unsigned char unknown04[0x80];
    ObjectBase* head;
    unsigned char unknown88[4];
    ObjectBase* slots[0x20];
    unsigned int slotCount;
    virtual ~SlotOwner();
};


ChildAt8* MakeChildAt8();

BufferAt8* MakeBufferAt8();

DoubleTableOwner* MakeDoubleTable();

PoolArray* MakePoolArray();

SlotOwner* MakeSlotOwner();



// Named wrapper that owns one child at 0x84 (the deleting destructor carries the inlined body).
struct NamedHolder1 : ObjectBase {
    char name[0x80];
    ObjectBase* child;
    NamedHolder1(const char* source, ObjectBase* owned) : child(owned)
    {
        const char* from = source;
        char* to = name;
        char c;
        do {
            c = *from;
            *to++ = c;
            ++from;
        } while (c);
    }
    virtual ~NamedHolder1();
};

struct NamedHolder2 : ObjectBase {
    char name[0x80];
    ObjectBase* child;
    NamedHolder2(const char* source, ObjectBase* owned) : child(owned)
    {
        const char* from = source;
        char* to = name;
        char c;
        do {
            c = *from;
            *to++ = c;
            ++from;
        } while (c);
    }
    virtual ~NamedHolder2();
};


// Object holding one plain buffer at 0x04.
struct BufferAt4 : ObjectBase {
    void* buffer;
    int unknown08;
    BufferAt4();
    virtual ~BufferAt4();
};



// Owner1 as seen from other units: its destructor (0x54bd0) is an external call.
struct Owner1External : ObjectBase {
    ObjectBase* child;
    virtual ~Owner1External();
};

// Owner1 with two extra buffers at 0x40 and 0x44.
struct OwnerD3 : Owner1External { virtual ~OwnerD3() {} };
struct OwnerD4 : Owner1External { virtual ~OwnerD4() {} };
struct OwnerD5 : Owner1External { virtual ~OwnerD5() {} };
OwnerD3* MakeOwnerD3();

OwnerD4* MakeOwnerD4();

OwnerD5* MakeOwnerD5();


struct OwnerWithBuffers : Owner1External {
    unsigned char unknown08[0x38];
    void* first;
    void* second;
    virtual ~OwnerWithBuffers();
};


NamedHolder1* MakeNamedHolder1();

NamedHolder2* MakeNamedHolder2();

BufferAt4* MakeBufferAt4();

OwnerWithBuffers* MakeOwnerWithBuffers();


struct ElementA : ObjectBase {};
struct ElementB : ObjectBase {};

template struct OwnedArray<ElementA>;
template struct OwnedArray<ElementB>;
OwnedArray<ElementA>* MakeOwnedA();

OwnedArray<ElementB>* MakeOwnedB();


PointerBankOwner* MakeBank();

TreeOwner* MakeTree();


// Force the vtables (and with them the deleting destructors) into this unit.
OwnerD1* MakeOwnerD1();

OwnerD2* MakeOwnerD2();

Owner2* MakeOwner2();


}  // namespace Kaim

#endif
