// Ported from an unpublished companion project.
#include "kynapse/host_2850c0.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f4b50
void Host2850C0::Notify(void* owner)
{
    if (listeners)
        listeners->Notify(this, owner);
}

}  // namespace Kaim
