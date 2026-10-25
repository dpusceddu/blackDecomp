// Declarations of the Kynapse source module "slot_forwarders" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_SLOT_FORWARDERS_HPP
#define BLACK_KYNAPSE_MODULE_SLOT_FORWARDERS_HPP
#include "kynapse/compat.hpp"

// Small Kynapse forwarders (eighth batch).

struct Forwardee {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Run();                 // slot 4
};

struct Forwarder {
    unsigned char unknown00[0x18];
    Forwardee* target;

    void RunTarget();
};



struct Describer {
    virtual void Slot0();
    virtual int GetKind();      // slot 1
};

struct Handler {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Dispatch(int kind);   // slot 6

    void Handle(Describer* source);
};



struct Vec3 {
    float x, y, z;
};

struct VecTable {
    unsigned char unknown00[8];
    unsigned int count;
    unsigned char unknown0c[8];
    Vec3* items;

    int Find(const Vec3* target);
};



#endif
