// Ported from the companion project (an unpublished companion project).
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x393288
BufferPair::~BufferPair()
{
    if (first) {
        memoryRelease(first);
        first = 0;
    }
    if (second) {
        memoryRelease(second);
        second = 0;
    }
}

}  // namespace Kaim
