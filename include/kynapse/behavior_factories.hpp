// Declarations of the Kynapse source module "behavior_factories" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_BEHAVIOR_FACTORIES_HPP
#define BLACK_KYNAPSE_MODULE_BEHAVIOR_FACTORIES_HPP
#include "kynapse/compat.hpp"

// Factories for behaviours: allocate through the Kynapse allocator service and construct.
#include "kynapse/alloc.hpp"

extern void (*memoryRelease)(void*);

namespace Kaim {

struct Context;

struct Behavior {
    Behavior(Context* context);
    virtual ~Behavior();
    static void* operator new(unsigned int size) { return KaimAllocate(size); }
    static void operator delete(void* block) { memoryRelease(block); }
};

struct Behavior28441C : Behavior {
    unsigned char data[0x7c];
    Behavior28441C(Context* context);
    virtual ~Behavior28441C();
};

struct Behavior2845BC : Behavior {
    unsigned char data[0x84];
    Behavior2845BC(Context* context);
    virtual ~Behavior2845BC();
};


Behavior* CreateBehavior28441C(Context* context);



Behavior* CreateBehavior2845BC(Context* context);


// Behaviour with an index and a range, constructed inline.
struct Behavior28428C : Behavior {
    unsigned char unknown04[8];
    int field0c;
    unsigned char unknown10[0x0c];
    int field1c;
    int field20;
    int field24;
    int field28;
    unsigned char unknown2c[4];

    Behavior28428C(Context* context)
        : Behavior(context), field0c(-1), field1c(0x7fffffff), field20(-1)
    {
        field28 = 0;
        field24 = 0;
    }
    virtual ~Behavior28428C();
};


Behavior* CreateBehavior28428C(Context* context);


// GENERATED BEHAVIOURS (from an unpublished companion project)
struct Behavior2844F4 : Behavior {
    unsigned char unknown04[8];
    int field0c;
    bool field10;
    unsigned char unknown11[3];
    int field14;
    unsigned char unknown18[12];

    Behavior2844F4(Context* context) : Behavior(context)
    {
        field10 = false;
        field14 = 0;
        field0c = 0;
    }
    virtual ~Behavior2844F4();
};


Behavior* CreateBehavior2844F4(Context* context);


struct Behavior284524 : Behavior {
    unsigned char unknown04[8];
    int field0c;
    int field10;
    unsigned char unknown14[40];
    int field3c;
    unsigned char unknown40[8];

    Behavior284524(Context* context) : Behavior(context)
    {
        field3c = 0;
        field0c = 0;
        field10 = 0;
    }
    virtual ~Behavior284524();
};


Behavior* CreateBehavior284524(Context* context);


struct Behavior284380 : Behavior {
    unsigned char unknown04[8];
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    unsigned char unknown20[8];
    int field28;
    int field2c;
    int field30;
    int field34;
    int field38;
    int field3c;
    unsigned char unknown40[24];

    Behavior284380(Context* context) : Behavior(context)
    {
        field18 = 0;
        field0c = 0;
        field1c = 0;
        field38 = 0;
        field28 = 0;
        field2c = 0;
        field14 = 0;
        field10 = 0;
        field30 = 0;
        field34 = 0;
        field3c = 0;
    }
    virtual ~Behavior284380();
};


Behavior* CreateBehavior284380(Context* context);


struct Behavior2842CC : Behavior {
    unsigned char unknown04[8];
    int field0c;
    int field10;
    int field14;
    int field18;
    int field1c;
    int field20;
    int field24;
    int field28;
    unsigned char unknown2c[32];
    int field4c;
    int field50;
    unsigned char unknown54[32];

    Behavior2842CC(Context* context) : Behavior(context)
    {
        field10 = 0;
        field14 = 0;
        field18 = 0;
        field1c = 0;
        field0c = 0;
        field50 = 0;
        field4c = 0;
        field24 = 0;
        field20 = 0;
        field28 = 0;
    }
    virtual ~Behavior2842CC();
};


Behavior* CreateBehavior2842CC(Context* context);


}  // namespace Kaim

#endif
