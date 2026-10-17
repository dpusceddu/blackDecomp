// Declarations of the Kynapse source module "ctors2" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_CTORS2_HPP
#define BLACK_KYNAPSE_MODULE_CTORS2_HPP
#include "kynapse/compat.hpp"

// Constructors of small objects whose vtables are defined elsewhere.
namespace Kaim {

struct ObjectRoot {
    virtual ~ObjectRoot() {}
};

// Eight zeroed words (vtable 0x284dc4).
struct ZeroBlock : ObjectRoot {
    int word[8];
    ZeroBlock();
    virtual ~ZeroBlock();
};



// Vtable-only object (vtable 0x285694).
struct EmptyObject : ObjectRoot {
    EmptyObject();
    virtual ~EmptyObject();
};


// An object with one cleared word at 0x10 (vtable 0x2857f0).
struct SingleWord : ObjectRoot {
    int unknown04[3];
    int word;
    SingleWord();
    virtual ~SingleWord();
};


struct Factory {
    unsigned char unknown00[8];
    ObjectRoot* (*create)();
};

struct FactoryProvider {
    virtual ~FactoryProvider();
    virtual void Slot1();
    virtual Factory* GetFactory();   // slot 2
};

struct FactorySource {
    unsigned char unknown00[0x18];
    FactoryProvider* provider;
};

// An owner that builds its child from its source's factory (vtable 0x284de8).
struct FactoryOwner : ObjectRoot {
    ObjectRoot* child;
    FactorySource* source;
    FactoryOwner(FactorySource* newSource);
    virtual ~FactoryOwner();
};



}  // namespace Kaim

#endif
