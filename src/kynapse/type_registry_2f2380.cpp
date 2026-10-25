#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/type_registry.hpp"

// /SLUS_213.76 0x2f2380

void ProviderUser::Init(int argument)
{
    TypeRegistry* registry = gEngine->FindByClass(&gTypeRegistryClass);
    if (registry)
        provider = registry->Find(argument, &gProviderClass);
    else
        provider = 0;
}

