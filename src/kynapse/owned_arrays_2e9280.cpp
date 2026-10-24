// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e9280
BufferTrio::~BufferTrio()
{
    if (first)
        memoryRelease(first);
    if (second)
        memoryRelease(second);
    if (third)
        memoryRelease(third);
}

}  // namespace Kaim
