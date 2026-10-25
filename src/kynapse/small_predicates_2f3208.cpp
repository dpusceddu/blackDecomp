#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/small_predicates.hpp"

// /SLUS_213.76 0x2f3208

bool MemberList::Contains(int id)
{
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i]->id == id)
            return true;
    }
    return false;
}

