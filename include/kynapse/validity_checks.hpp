// Declarations of the Kynapse source module "validity_checks" (ported from an unpublished companion project).
// Function definitions are in the units that provide them.
#ifndef BLACK_KYNAPSE_MODULE_VALIDITY_CHECKS_HPP
#define BLACK_KYNAPSE_MODULE_VALIDITY_CHECKS_HPP
#include "kynapse/compat.hpp"

// Small Kynapse leaf functions (second batch): validity checks, vector helpers, guarded setters.

extern void (*gHook)();


void Kaim_CallHook();


extern int gIdH;
extern int gIdI;


bool Kaim_PairIdsValid();


extern int gIdJ;
extern int gIdK;
extern int gIdL;


bool Kaim_TripleIdsValid();


struct Vec3 {
    float x, y, z;
};


void Vec3_Scale(Vec3* out, const Vec3* v, float scale);



float Vec3_Component(void* unused, const Vec3* v, int index);



float Vec3_DistanceSquaredXZ(const Vec3* a, const Vec3* b);


struct Dynamics {
    unsigned char unknown00[8];
    float field08;
    unsigned char unknown0c[0xe0];
    float minimum;
    float scaledHalf;
    float scaledField08;

    void SetMinimum(float value);
    void SetScaledHalf(float value);
    void SetScaledField08(float value);
};







#endif
