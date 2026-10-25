#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/engine_class.hpp"

namespace Kaim {
// /SLUS_213.76 0x2eb280

void Engine::AddService(Object* service)
{
    if (serviceCapacity == serviceCount) {
        if (serviceCapacity == 0)
            serviceCapacity = 8;
        else
            serviceCapacity = serviceCapacity + serviceCapacity;
        Object** grown = (Object**)KaimAllocate(serviceCapacity * 4);
        for (unsigned int i = 0; i < serviceCount; ++i)
            grown[i] = services[i];
        if (serviceCount)
            memoryRelease(services);
        services = grown;
    }
    services[serviceCount] = service;
    ++serviceCount;
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/engine_class_2eb280", func_002EB450);
