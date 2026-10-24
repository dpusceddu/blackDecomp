#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/batch10.hpp"

// /SLUS_213.76 0x2f2380

void ProviderUser::Init(int argument)
{
    TypeRegistry* registry = gEngine->FindByClass(&gTypeRegistryClass);
    if (registry)
        provider = registry->Find(argument, &gProviderClass);
    else
        provider = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F23E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F23F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F2418);
