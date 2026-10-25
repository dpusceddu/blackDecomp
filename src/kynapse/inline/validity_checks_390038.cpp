#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/validity_checks.hpp"

// /SLUS_213.76 0x390038

float Vec3_Component(void* unused, const Vec3* v, int index)
{
    if (index == 0)
        return v->x;
    if (index == 1)
        return v->y;
    return v->z;
}
