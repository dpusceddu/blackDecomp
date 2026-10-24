// Ported from an unpublished companion project.
#include "kynapse/tiny3.hpp"

namespace Kaim {
// /SLUS_213.76 0x390758
bool Probe::NoValue(int, int, int, int* out)
{
    *out = 0;
    return true;
}

}  // namespace Kaim
