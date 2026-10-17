// Ported from the companion project (an unpublished companion project).
#include "kynapse/small_misc.hpp"

// /SLUS_213.76 0x2e9cc8
void Kaim_ReleaseService()
{
    if (gService)
        delete gService;
    gService = 0;
}
