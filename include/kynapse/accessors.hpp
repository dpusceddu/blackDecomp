// Declarations of the Kynapse source module "accessors" (ported from the companion project:
// an unpublished companion project). Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_ACCESSORS_HPP
#define BLACK_KYNAPSE_MODULE_ACCESSORS_HPP
#include "kynapse/compat.hpp"

// Small Kynapse table accessors and forwarding wrappers (x87).

extern const float kRadiansPerUnit;
extern int gGrowthCounter;

struct TableKey {
    int unknown0;
    int index;
    int (*resolver)();
};

// Entity with an indexed property table.
struct PropertyOwner {
    unsigned char unknown00[0x58];
    int propertyCount;
    int* properties;

    int GetProperty(const TableKey* key) const;
    int Resolve(const TableKey* key);
};





// Bank of pointers with a count.
struct PointerBank {
    int unknown0;
    int count;
    int* items;

    int GetItem(const TableKey* key) const;
    int Resolve(const TableKey* key);
};





// Action with an activation flag at 0x04.
struct Action {
    int unknown0;
    unsigned char active;
};
struct ActionBank {
    int unknown0;
    int count;
    Action** actions;

    void ClearActivation();
};




float Radians_Cosine(float units);



// Unmatched: identical operations; the original lays the negative exit out first (11 bytes).
// Doubles the growth counter unless it has gone negative.
int GrowthCounter_Double();


#endif
