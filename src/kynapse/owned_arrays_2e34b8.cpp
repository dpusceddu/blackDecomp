// Ported from the companion project (an unpublished companion project).
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e34b8
ChildBuffers::~ChildBuffers()
{
    DeleteChildren();
    if (first)
        memoryRelease(first);
    if (third)
        memoryRelease(third);
    if (second)
        memoryRelease(second);
    if (capacity > 0)
        memoryRelease(items);
}

}  // namespace Kaim
