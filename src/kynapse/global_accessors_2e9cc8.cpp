#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/global_accessors.hpp"

// /SLUS_213.76 0x2e9cc8

void Kaim_ReleaseService()
{
    if (gService)
        delete gService;
    gService = 0;
}

