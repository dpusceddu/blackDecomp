#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/behavior_methods.hpp"

namespace Kaim {
// /SLUS_213.76 0x2d51c0

void Behavior28441C::ResetState()
{
    position = gOrigin;
    limit = 0x7fffffff;
    flag35 = false;
    flag34 = false;
    field48 = 0;
    flag54 = false;
    flag55 = true;
    field58 = -1;
    low = 0.0f;
    high = 3.4028235e38f;
    flag68 = false;
    lowest = -3.4028235e38f;
}

}  // namespace Kaim
