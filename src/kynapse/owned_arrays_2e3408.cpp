#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e3408

ChildBuffers::ChildBuffers()
{
    unknown04 = 0;
    capacity = 0;
    count = 0;
    unknown08 = 0;
    items = 0;
    first = 0;
    second = 0;
    third = 0;
}

}  // namespace Kaim
