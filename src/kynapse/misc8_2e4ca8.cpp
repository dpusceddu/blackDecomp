// Ported from the companion project (an unpublished companion project).
#include "kynapse/misc8.hpp"

// /SLUS_213.76 0x2e4ca8
void Forwarder::RunTarget()
{
    if (target)
        target->Run();
}
