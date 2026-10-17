// Declarations of the Kynapse source module "misc6" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_MISC6_HPP
#define BLACK_KYNAPSE_MODULE_MISC6_HPP
#include "kynapse/compat.hpp"

// Small Kynapse helpers (sixth batch).

// A record with seven integer slots and two flags, assigned member by member.
struct SlotRecord {
    int slot0, slot1, slot2, slot3, slot4, slot5, slot6;
    char flagA;
    char flagB;

    SlotRecord& operator=(const SlotRecord& other);
};



// Tolerance record: two float limits with defaults.
struct Tolerance {
    virtual ~Tolerance();
    int unknown04;
    float epsilon;
    int unknown0c;
    float ratio;

    Tolerance();
};



struct Mover {
    unsigned char unknown00[0x1b5];
    bool dirty;

    void MarkDirty(int);
    void MarkDirtyNow();
};





struct Target {
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2(); virtual void Slot3();
    virtual void Slot4(); virtual void Slot5(); virtual void Slot6(); virtual void Slot7();
    virtual void Slot8(); virtual void Slot9(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Apply(int argument);   // slot 24
};


void Kaim_ApplyToTarget(int argument, Target* target);


#endif
